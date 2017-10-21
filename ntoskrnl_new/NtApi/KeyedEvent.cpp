
#include <Ex/Ex.hpp>

extern "C"
__kernel_entry
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtCreateKeyedEvent (
    _Out_ PHANDLE KeyedEventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG Flags)
{
    KPROCESSOR_MODE previousMode = KeGetPreviousMode();
    PEX_KEYED_EVENT keyedEvent;
    HANDLE handle;
    NTSTATUS status;

    /* Check flags */
    if (Flags != 0)
    {
        /* We don't support any flags yet */
        return STATUS_INVALID_PARAMETER;
    }

    /* Create the object */
    status = ObCreateObject(previousMode,
                            ExKeyedEventObjectType,
                            ObjectAttributes,
                            previousMode,
                            NULL,
                            sizeof(EX_KEYED_EVENT),
                            0,
                            0,
                            (PVOID*)&keyedEvent);

    /* Check for success */
    if (!NT_SUCCESS(status)) return status;

    /* Initialize the keyed event */
    ExpInitializeKeyedEvent(keyedEvent);

    /* Insert it */
    status = ObInsertObject(keyedEvent,
                            NULL,
                            DesiredAccess,
                            0,
                            NULL,
                            &handle);

    /* Check for success (ObInsertObject dereferences!) */
    if (!NT_SUCCESS(status)) return status;

    if (previousMode != KernelMode)
    {
        /* Enter SEH for return */
        _SEH2_TRY
        {
            /* Return the handle to the caller */
            ProbeForWrite(KeyedEventHandle, sizeof(HANDLE), sizeof(HANDLE));
            *KeyedEventHandle = handle;
        }
        _SEH2_EXCEPT(ExSystemExceptionFilter())
        {
            /* Get the exception code */
            status = _SEH2_GetExceptionCode();

            /* Cleanup */
            ObCloseHandle(handle, previousMode);
        }
        _SEH2_END;
    }
    else
    {
        *KeyedEventHandle = handle;
    }

    /* Return status */
    return status;
}

extern "C"
__kernel_entry
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtOpenKeyedEvent (
    _Out_ PHANDLE KeyedEventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    KPROCESSOR_MODE previousMode = KeGetPreviousMode();
    HANDLE handle;
    NTSTATUS status;

    /* Open the object */
    status = ObOpenObjectByName(ObjectAttributes,
                                ExKeyedEventObjectType,
                                previousMode,
                                NULL,
                                DesiredAccess,
                                NULL,
                                &handle);

    /* Check for success */
    if (!NT_SUCCESS(status)) return status;

    /* Enter SEH for return */
    if (previousMode != KernelMode)
    {
        _SEH2_TRY
        {
            /* Return the handle to the caller */
            ProbeForWrite(KeyedEventHandle, sizeof(HANDLE), sizeof(HANDLE));
            *KeyedEventHandle = handle;
        }
        _SEH2_EXCEPT(ExSystemExceptionFilter())
        {
            /* Get the exception code */
            status = _SEH2_GetExceptionCode();

            /* Cleanup */
            ObCloseHandle(KeyedEventHandle, previousMode);
        }
        _SEH2_END;
    }
    else
    {
        *KeyedEventHandle = handle;
    }

    /* Return status */
    return status;
}

extern "C"
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtWaitForKeyedEvent (
    _In_opt_ HANDLE KeyedEventHandle,
    _In_ PVOID Key,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout)
{
    KPROCESSOR_MODE previousMode = KeGetPreviousMode();
    PEX_KEYED_EVENT keyedEvent;
    NTSTATUS status;
    LARGE_INTEGER timeoutCopy;

    /* Key must always be two-byte aligned */
    if ((ULONG_PTR)Key & 1)
    {
        return STATUS_INVALID_PARAMETER_1;
    }

    /* Check if the caller passed a timeout value and this is from user mode */
    if ((Timeout != NULL) && (previousMode != KernelMode))
    {
        _SEH2_TRY
        {
            ProbeForRead(Timeout, sizeof(*Timeout), 1);
            timeoutCopy = *Timeout;
            Timeout = &timeoutCopy;
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            _SEH2_YIELD(return _SEH2_GetExceptionCode());
        }
        _SEH2_END;
    }

    /* Check if the caller provided a handle */
    if (KeyedEventHandle != NULL)
    {
        /* Get the keyed event object */
        status = ObReferenceObjectByHandle(KeyedEventHandle,
                                           KEYEDEVENT_WAIT,
                                           ExKeyedEventObjectType,
                                           previousMode,
                                           (PVOID*)&keyedEvent,
                                           NULL);

        /* Check for success */
        if (!NT_SUCCESS(status)) return status;
    }
    else
    {
        /* Use the default keyed event for low memory critical sections */
        keyedEvent = ExpCritSecOutOfMemoryEvent;
    }

    /* Do the wait */
    status = ExpWaitForKeyedEvent(keyedEvent, Key, Alertable, Timeout);

    if (KeyedEventHandle != NULL)
    {
        /* Dereference the keyed event */
        ObDereferenceObject(keyedEvent);
    }

    /* Return the status */
    return status;
}

extern "C"
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
NtReleaseKeyedEvent (
    _In_opt_ HANDLE KeyedEventHandle,
    _In_ PVOID Key,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout)
{
    KPROCESSOR_MODE previousMode = KeGetPreviousMode();
    PEX_KEYED_EVENT keyedEvent;
    NTSTATUS status;
    LARGE_INTEGER timeoutCopy;

    /* Key must always be two-byte aligned */
    if ((ULONG_PTR)Key & 1)
    {
        return STATUS_INVALID_PARAMETER_1;
    }

    /* Check if the caller passed a timeout value and this is from user mode */
    if ((Timeout != NULL) && (previousMode != KernelMode))
    {
        _SEH2_TRY
        {
            ProbeForRead(Timeout, sizeof(*Timeout), 1);
            timeoutCopy = *Timeout;
            Timeout = &timeoutCopy;
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            _SEH2_YIELD(return _SEH2_GetExceptionCode());
        }
        _SEH2_END;
    }

    /* Check if the caller provided a handle */
    if (KeyedEventHandle != NULL)
    {
        /* Get the keyed event object */
        status = ObReferenceObjectByHandle(KeyedEventHandle,
                                           KEYEDEVENT_WAKE,
                                           ExKeyedEventObjectType,
                                           previousMode,
                                           (PVOID*)&keyedEvent,
                                           NULL);

        /* Check for success */
        if (!NT_SUCCESS(status)) return status;
    }
    else
    {
        /* Use the default keyed event for low memory critical sections */
        keyedEvent = ExpCritSecOutOfMemoryEvent;
    }

    /* Do the wait */
    status = ExpReleaseKeyedEvent(keyedEvent, Key, Alertable, Timeout);

    if (KeyedEventHandle != NULL)
    {
        /* Dereference the keyed event */
        ObDereferenceObject(keyedEvent);
    }

    /* Return the status */
    return status;
}
