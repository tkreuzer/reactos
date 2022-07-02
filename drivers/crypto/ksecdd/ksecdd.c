/*
 * PROJECT:         ReactOS Drivers
 * COPYRIGHT:       See COPYING in the top level directory
 * PURPOSE:         Kernel Security Support Provider Interface Driver
 *
 * PROGRAMMERS:     Timo Kreuzer (timo.kreuzer@reactos.org)
 */

/* INCLUDES *******************************************************************/

#include "ksecdd.h"
#include "entropy.h"

#define NDEBUG
#include <debug.h>

/* GLOBALS ********************************************************************/

PDEVICE_OBJECT KsecDeviceObject;
PEPROCESS KsecLsaProcess;
PEPROCESS KsecSystemProcess;
HANDLE KsecLsaProcessHandle;
SecurityFunctionTableW SecTable;
FAST_MUTEX KsecConnectionMutex;
BOOLEAN KsecConnected;
PCSTR LogonProcessString = "KSecDD";


/* FUNCTIONS ******************************************************************/

NTSTATUS
NTAPI
KsecInitLsaMemory (
    VOID)
{
    UNIMPLEMENTED;
    return 0;
}

static
NTSTATUS
LocateClient(VOID)
{
    PVOID SecurityPort;

    /* Acquire the connection mutex */
    ExAcquireFastMutex(&KsecConnectionMutex);

    /* Get the security port */
    SecurityPort = PsGetProcessSecurityPort(PsGetCurrentProcess());

    /* Release the connection mutex */
    ExReleaseFastMutex(&KsecConnectionMutex);

    /* Check if we have a valid security port */
    if ((SecurityPort == NULL) || (SecurityPort == (PVOID)1))
    {
        return STATUS_OBJECT_NAME_NOT_FOUND;
    }

    return STATUS_SUCCESS;
}

static
NTSTATUS
OpenSyncEvent(
    _Out_ PHANDLE EventHandle)
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING EventName = RTL_CONSTANT_STRING(L"\\SECURITY\\LSA_AUTHENTICATION_INITIALIZED");
    PAGED_CODE();

    InitializeObjectAttributes(&ObjectAttributes,
                               &EventName,
                               OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    return ZwOpenEvent(EventHandle, EVENT_ALL_ACCESS, &ObjectAttributes);
}

NTSTATUS
NTAPI
CreateConnection(
    PCSTR ConnectionString,
    PULONG ResultInformation,
    PNTSTATUS ResultStatus)
{
    UNICODE_STRING PortName = RTL_CONSTANT_STRING(L"\\LsaAuthenticationPort");
    PEPROCESS CurrentProcess;
    KAPC_STATE SavedApcState;
    BOOLEAN Attached = FALSE;
    SECURITY_QUALITY_OF_SERVICE SecurityQos;
    ULONG MaxMessageSize;
    KSEC_CONNECTION_INFO ConnectData;
    ULONG ConnectDataLength;
    HANDLE PortHandle;
    PVOID SecurityPort, OldSecurityPort;
    NTSTATUS Status;

    ConnectDataLength = 0x8C;
    PAGED_CODE();
    DPRINT("KSec: CreateConnection\n");

    RtlZeroMemory(&ConnectData, sizeof(ConnectData));

    if (ConnectionString)
    {
        RtlStringCbCopyA(ConnectData.ConnectionString,
                         sizeof(ConnectData.ConnectionString),
                         ConnectionString);
        ConnectData.Information = strlen(ConnectData.ConnectionString);
        ConnectData.Flags = 1;
        ConnectDataLength = 0x90;
    }

    /* Check if we are the lsass process */
    CurrentProcess = PsGetCurrentProcess();
    if (CurrentProcess != KsecLsaProcess)
    {
        /* We are not, attach to the system process */
        KeStackAttachProcess(&KsecSystemProcess->Pcb, &SavedApcState);
        Attached = 1;
    }

    /* Initialize Security QOS */
    SecurityQos.Length = sizeof(SecurityQos);
    SecurityQos.ImpersonationLevel = SecurityImpersonation;
    SecurityQos.ContextTrackingMode = SECURITY_DYNAMIC_TRACKING;
    SecurityQos.EffectiveOnly = FALSE;

    /* Connect to the LSA authentication port */
    Status = ZwConnectPort(&PortHandle,
                           &PortName,
                           &SecurityQos,
                           0,
                           0,
                           &MaxMessageSize,
                           &ConnectData,
                           &ConnectDataLength);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Connection failed: %x \n", Status);
        if (Attached)
            KeUnstackDetachProcess(&SavedApcState);
        return STATUS_KSEC_INTERNAL_ERROR;
    }

    if (ResultInformation != NULL)
        *ResultInformation = ConnectData.Information;

    if (ResultStatus != NULL)
        *ResultStatus = ConnectData.Status;

    DPRINT("Connected\n");

    /* Reference the port handle */
    Status = ObReferenceObjectByHandle(PortHandle,
                                       0x1F0001,
                                       NULL,
                                       KernelMode,
                                       &SecurityPort,
                                       NULL);

    /* Close the port handle */
    ObCloseHandle(PortHandle, KernelMode);

    /* If we attached, detach now */
    if (Attached)
        KeUnstackDetachProcess(&SavedApcState);

    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Acquire the connection mutex */
    ExAcquireFastMutex(&KsecConnectionMutex);

    /* Get the old security port and check if we had one */
    OldSecurityPort = PsGetProcessSecurityPort(CurrentProcess);
    if (OldSecurityPort == (PVOID)1)
    {
        Status = STATUS_PROCESS_IS_TERMINATING;
    }
    else if (OldSecurityPort != NULL)
    {
        Status = STATUS_OBJECT_NAME_EXISTS;
    }
    else
    {
        /* There is no security port yet, so set the new one */
        Status = PsSetProcessSecurityPort(CurrentProcess, SecurityPort);
    }

    /* Release the connection mutex */
    ExReleaseFastMutex(&KsecConnectionMutex);

    /* Check if setting the new security descriptor failed */
    if (!NT_SUCCESS(Status))
    {
        ObfDereferenceObject(SecurityPort);
        if ( Status == STATUS_OBJECT_NAME_COLLISION )
            Status = STATUS_OBJECT_NAME_EXISTS;
    }

    return Status;
}

NTSTATUS
NTAPI
InitializePackages(ULONG NumberOfPackages)
{
    PAGED_CODE();

    UNIMPLEMENTED;
    return 0;
}

static
NTSTATUS
CreateClient(BOOLEAN UseLogonProcessString)
{
    HANDLE SyncEvent;
    ULONG NumberOfPackages;
    NTSTATUS Status;

    /* Check if we are attached */
    if (PsGetCurrentProcessId() != PsGetCurrentThreadProcessId())
    {
        return STATUS_ACCESS_DENIED;
    }

    /* Check if we have a valid security port */
    if (PsGetProcessSecurityPort(PsGetCurrentProcess()) == (PVOID)1)
    {
        return STATUS_PROCESS_IS_TERMINATING;
    }

    /* Open the synchronization event */
    Status = OpenSyncEvent(&SyncEvent);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("KSec: Failed to open event, %x\n", Status);
        return STATUS_KSEC_INTERNAL_ERROR;
    }

    /* Wait for the synchronization event */
    Status = ZwWaitForSingleObject(SyncEvent, FALSE, NULL);

    /* Close the synchronization event */
    ObCloseHandle(SyncEvent, KernelMode);

    if (!NT_SUCCESS(Status))
    {
        return STATUS_KSEC_INTERNAL_ERROR;
    }

    Status = CreateConnection(UseLogonProcessString ? LogonProcessString : NULL,
                              &NumberOfPackages,
                              NULL);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("KSec: Connection failed, postponing\n");
        return STATUS_KSEC_INTERNAL_ERROR;
    }

    KsecConnected = TRUE;
    InitializePackages(NumberOfPackages);

    return STATUS_SUCCESS;
}

static
NTSTATUS
IsOkayToExec(VOID)
{
    NTSTATUS Status;

    /* Check if we have a client already */
    Status = LocateClient();
    if (!NT_SUCCESS(Status))
    {
        /* Create the client */
        Status = CreateClient(1);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }
    }

    return STATUS_SUCCESS;
}

PSecurityFunctionTableW
SEC_ENTRY
InitSecurityInterfaceW(VOID)
{
    NTSTATUS Status;

    Status = IsOkayToExec();
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Failed to init security interface: 0x%x\n", Status);
        return NULL;
    }

    //SecpSetSession(2, 0, 0, 0);

    return &SecTable;
}

NTSTATUS
NTAPI
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath)
{
    UNICODE_STRING DeviceName = RTL_CONSTANT_STRING(L"\\Device\\KsecDD");
    NTSTATUS Status;

    /* Create the KsecDD device */
    Status = IoCreateDevice(DriverObject,
                            0,
                            &DeviceName,
                            FILE_DEVICE_KSEC,
                            0x100u,
                            FALSE,
                            &KsecDeviceObject);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Failed to create KsecDD device: 0x%lx\n", Status);
        return Status;
    }

    /* Set up dispatch table */
    DriverObject->MajorFunction[IRP_MJ_CREATE] = KsecDdDispatch;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = KsecDdDispatch;
    DriverObject->MajorFunction[IRP_MJ_READ] = KsecDdDispatch;
    DriverObject->MajorFunction[IRP_MJ_WRITE] = KsecDdDispatch;
    DriverObject->MajorFunction[IRP_MJ_QUERY_INFORMATION] = KsecDdDispatch;
    DriverObject->MajorFunction[IRP_MJ_QUERY_VOLUME_INFORMATION] = KsecDdDispatch;
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = KsecDdDispatch;

    /* Initialize */
    KsecInitializeEncryptionSupport();

    /* Remember the system process */
    KsecSystemProcess = PsGetCurrentProcess();

    /* Initialize the connection mutex */
    ExInitializeFastMutex(&KsecConnectionMutex);

    return STATUS_SUCCESS;
}
