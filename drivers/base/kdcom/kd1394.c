/*
 * COPYRIGHT:       GPL, see COPYING in the top level directory
 * PROJECT:         ReactOS kernel
 * FILE:            drivers/base/kddll/kdcom.c
 * PURPOSE:         COM port functions for the kernel debugger.
 * PROGRAMMER:      Timo Kreuzer (timo.kreuzer@ewactos.org)
 */

#include "kddll.h"

#include <arc/arc.h>
#include <stdlib.h>
#include <ndk/halfuncs.h>

#define NDEBUG
#include <debug.h>


/* GLOBALS ********************************************************************/

ULONG Kdp1394Channel;
ULONG Kdp1394BusParams;
DEBUG_DEVICE_DESCRIPTOR Kdp1394DeviceDescriptor;

/* FUNCTIONS ******************************************************************/

NTSTATUS
NTAPI
KdD0Transition(VOID)
{
    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
KdD3Transition(VOID)
{
    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
KdSave(IN BOOLEAN SleepTransition)
{
    /* Nothing to do on 1394 ports */
    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
KdRestore(IN BOOLEAN SleepTransition)
{
    /* Nothing to do on 1394 ports */
    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
Kdp1394PortInitialize(VOID)
{
    NTSTATUS Status;

    KDDBGPRINT("Kdp1394PortInitialize\n");

    Kdp1394DeviceDescriptor.VendorID = -1;
    Kdp1394DeviceDescriptor.DeviceID = -1;
    Kdp1394DeviceDescriptor.Bus = -1;
    Kdp1394DeviceDescriptor.Slot = -1;
    Kdp1394DeviceDescriptor.BaseClass = PCI_CLASS_SERIAL_BUS_CTLR;
    Kdp1394DeviceDescriptor.SubClass = PCI_SUBCLASS_SB_IEEE1394;
    Kdp1394DeviceDescriptor.ProgIf = 0x10;
    Kdp1394DeviceDescriptor.Memory.Length = 0x2088;

    Status = KdSetupPciDeviceForDebugging(LoaderBlock,
                                          &Kdp1394DeviceDescriptor);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    Kdp1394Data = Kdp1394DeviceDescriptor.Memory.VirtualAddress;
    memset(Kdp1394Data, 0, 0x2088);
    Result = Dbg1394_InitializeController(Kdp1394Data, &Kdp1394DeviceDescriptor);

    return STATUS_SUCCESS;
}


/******************************************************************************
 * \name KdDebuggerInitialize0
 * \brief Phase 0 initialization.
 * \param [opt] LoaderBlock Pointer to the Loader parameter block. Can be NULL.
 * \return Status
 */
NTSTATUS
NTAPI
KdDebuggerInitialize0(IN PLOADER_PARAMETER_BLOCK LoaderBlock OPTIONAL)
{
    PCHAR CommandLine, PortString, ChannelString, BusParamsString;
    ULONG Value;

    /* Check if e have a LoaderBlock */
    if (LoaderBlock == NULL)
    {
        return STATUS_UNSUCCESSFUL;
    }

    /* HACK */
    KdpDbgPrint = LoaderBlock->u.I386.CommonDataArea;
    KDDBGPRINT("KdDebuggerInitialize0\n");

    /* Get the Command Line */
    CommandLine = LoaderBlock->LoadOptions;
    if (CommandLine == NULL)
    {
        return STATUS_UNSUCCESSFUL;
    }

    /* Upcase it */
    _strupr(CommandLine);

    /* Get the port and baud rate */
    PortString = strstr(CommandLine, "DEBUGPORT");
    ChannelString = strstr(CommandLine, "CHANNEL");
    BusParamsString = strstr(CommandLine, "BUSPARAMS");

    /* Check if we got the /DEBUGPORT parameter */
    if (PortString)
    {
        /* Move past the actual string, to reach the port*/
        PortString += strlen("DEBUGPORT");

        /* Now get past any spaces and skip the equal sign */
        while (*PortString == ' ') PortString++;
        PortString++;

        /* Do we have a serial port? */
        if (strncmp(PortString, "1394", 4) != 0)
        {
            return STATUS_INVALID_PARAMETER;
        }
   }

    /* Check if we got a baud rate */
    if (ChannelString)
    {
        /* Move past the actual string, to reach the rate */
        ChannelString += strlen("CHANNEL");

        /* Now get past any spaces */
        while (*ChannelString == ' ') ChannelString++;

        /* And make sure we have a rate */
        if (*ChannelString)
        {
            /* Read and set it */
            Value = atol(ChannelString + 1);
            if (Value) Kdp1394Channel = Value;
        }
    }

    /* Check Serial Port Settings [IRQ] */
    if (BusParamsString)
    {
        /* Move past the actual string, to reach the rate */
        BusParamsString += strlen("BUSPARAMS");

        /* Now get past any spaces */
        while (*BusParamsString == ' ') BusParamsString++;

        /* And make sure we have an IRQ */
        if (*BusParamsString)
        {
            /* Read and set it */
            Value = atol(BusParamsString + 1);
            if (Value) Kdp1394BusParams = Value;
        }
    }

    /* Initialize the port */
    return Kdp1394PortInitialize();
}

/******************************************************************************
 * \name KdDebuggerInitialize1
 * \brief Phase 1 initialization.
 * \param [opt] LoaderBlock Pointer to the Loader parameter block. Can be NULL.
 * \return Status
 */
NTSTATUS
NTAPI
KdDebuggerInitialize1(IN PLOADER_PARAMETER_BLOCK LoaderBlock OPTIONAL)
{
    return STATUS_SUCCESS;
}


VOID
NTAPI
KdpSendByte(IN UCHAR Byte)
{
    /* Send the byte */
    ASSERT(FALSE);
}

KDP_STATUS
NTAPI
KdpPollByte(OUT PUCHAR OutByte)
{
    /* Poll the byte */
    ASSERT(FALSE);
    return KDP_PACKET_TIMEOUT;
}

KDP_STATUS
NTAPI
KdpReceiveByte(OUT PUCHAR OutByte)
{
    /* Get the byte */
    ASSERT(FALSE);
    return KDP_PACKET_TIMEOUT;
}

KDP_STATUS
NTAPI
KdpPollBreakIn(VOID)
{
    KDP_STATUS KdStatus;
    UCHAR Byte;

    KdStatus = KdpPollByte(&Byte);
    if ((KdStatus == KDP_PACKET_RECEIVED) && (Byte == BREAKIN_PACKET_BYTE))
    {
        return KDP_PACKET_RECEIVED;
    }
    return KDP_PACKET_TIMEOUT;
}

/* EOF */

typedef struct _HALP_PCI_DEBUGGING_DEVICE
{
    ULONG State : 2;
    ULONG ??? : 6;
    ULONG FunctionNumber : 3; // bits 8 - 10
    ULONG DeviceNumber : 5;   // bits 11 - 15
    ULONG Bus : 8;

} HALP_PCI_DEBUGGING_DEVICE, *PHALP_PCI_DEBUGGING_DEVICE;



NTSTATUS
NTAPI
HalpSetupPciDeviceForDebugging(
    PLOADER_PARAMETER_BLOCK LoaderBlock,
    PDEBUG_DEVICE_DESCRIPTOR DebugDeviceDescriptor)
{
    PCI_SLOT_NUMBER PciSlotNumber;
    ULONG i;
    NTSTATUS Status;

    Status = HalpSearchForPciDebuggingDevice(DebugDeviceDescriptor,
                                             0,
                                             255,
                                             0x10000000,
                                             0xFC000000,
                                             4096,
                                             -1,
                                             0);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    Status = HalpSearchForPciDebuggingDevice(DebugDeviceDescriptor,
                                             0,
                                             255,
                                             0x10000000,
                                             0xFC000000,
                                             4096,
                                             -1,
                                             1),
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    if (DebugDeviceDescriptor->Initialized)
    {
        return STATUS_SUCCESS;
    }

    PciSlotNumber.AsULONG = DebugDeviceDescriptor->Slot;

    for (i = 0; i < 2; i++)
    {
        if ((HalpPciDebuggingDevice[i].DeviceNumber == PciSlotNumber.DeviceNumber) &&
            (HalpPciDebuggingDevice[i].FunctionNumber == PciSlotNumber.FunctionNumber) &&
            (HalpPciDebuggingDevice[i].Bus == DebugDeviceDescriptor->Bus) &&
            (HalpPciDebuggingDevice[i].State == 1))
        {
            return STATUS_UNSUCCESSFUL;
        }
    }

    for (i = 0; i < 2; i++)
    {
        if (HalpPciDebuggingDevice[i].State != 0)
        {
            HalpPciDebuggingDevice[i].DeviceNumber = PciSlotNumber.DeviceNumber;
            HalpPciDebuggingDevice[i].FunctionNumber = PciSlotNumber.FunctionNumber;
            HalpPciDebuggingDevice[i].Bus = DebugDeviceDescriptor->Bus;
            HalpPciDebuggingDevice[i].State == 1;
            DebugDeviceDescriptor->Initialized = 1;
            break;
        }
    }

    if (i == 2)
    {
        return STATUS_UNSUCCESSFUL;
    }

    Length = DebugDeviceDescriptor->Memory.Length;
    if (Length != 0)
    {
        if (LoaderBlock == NULL)
        {
            return STATUS_INVALID_PARAMETER_1;
        }

        if (DebugDeviceDescriptor->Memory.MaxEnd.QuadPart == 0)
        {
            DebugDeviceDescriptor->Memory.MaxEnd.QuadPart = MAXULONGLONG;
        }

        //if (DebugDeviceDescriptor->Memory.MaxEnd.QuadPart <= MAXULONG)
        //    MaxEnd = DebugDeviceDescriptor->Memory.MaxEnd.LowPart;
        //else
        //    MaxEnd = MAXULONG;

        MaxEnd = MIN(DebugDeviceDescriptor->Memory.MaxEnd.QuadPart, MAXULONG);
        MaxStart = MaxEnd - Length;

        DebugDeviceDescriptor->Memory.Start.HighPart = 0;

        MaxAddress = ROUND_TO_PAGES(Length) +
              (MaxStart & 0xFFFFF000);


        ByteOffset = MaxAddress & 0xFFF;

        PageCount = ROUND_TO_PAGES(Length + ByteOffset);

        PhysicalAddress.QuadPart = HalpAllocPhysicalMemory(LoaderBlock,
                                                           MaxAddress,
                                                           PageCount,
                                                           FALSE);
        DebugDeviceDescriptor->Memory.Start = PhysicalAddress;
        if (PhysicalAddress.QuadPart == 0)
        {
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        /* Map the allocated physical pages */
        VirtualAddress = HalpMapPhysicalMemory64(PhysicalAddress, PageCount);
        DebugDeviceDescriptor->Memory.VirtualAddress = VirtualAddress;
    }

    return Status;
}
