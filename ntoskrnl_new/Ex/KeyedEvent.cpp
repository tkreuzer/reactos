
/* INCLUDES *****************************************************************/

#include <ntoskrnl.h>

#define ExSystemExceptionFilter() 1


/* Internal types *************************************************************/


VOID
NTAPI
ExpInitializeKeyedEvent(
    _Out_ PEX_KEYED_EVENT KeyedEvent);


/* Globals  *******************************************************************/

PEX_KEYED_EVENT ExpCritSecOutOfMemoryEvent;
POBJECT_TYPE ExKeyedEventObjectType;

static
GENERIC_MAPPING ExpKeyedEventMapping =
{
    STANDARD_RIGHTS_READ | KEYEDEVENT_WAIT,
    STANDARD_RIGHTS_WRITE | KEYEDEVENT_WAKE,
    STANDARD_RIGHTS_EXECUTE,
    KEYEDEVENT_ALL_ACCESS
};

/* Functions  *****************************************************************/

NTSTATUS
NTAPI
INIT_FUNCTION
KEYED_EVENT::InitializeClass (
    VOID)
{
    OBJECT_TYPE_INITIALIZER ObjectTypeInitializer = {0};
    UNICODE_STRING TypeName = RTL_CONSTANT_STRING(L"KeyedEvent");
    NTSTATUS Status;

    /* Set up the object type initializer */
    ObjectTypeInitializer.Length = sizeof(ObjectTypeInitializer);
    ObjectTypeInitializer.GenericMapping = ExpKeyedEventMapping;
    ObjectTypeInitializer.PoolType = PagedPool;
    ObjectTypeInitializer.ValidAccessMask = KEYEDEVENT_ALL_ACCESS;
    ObjectTypeInitializer.UseDefaultObject = TRUE;

    /* Create the keyed event object type */
    Status = ObCreateObjectType(&TypeName,
                                &ObjectTypeInitializer,
                                NULL,
                                &ExKeyedEventObjectType);

    if (!NT_SUCCESS(Status)) return Status;

    /* Create the global keyed event for critical sections on low memory */
    Status = ObCreateObject(KernelMode,
                            ExKeyedEventObjectType,
                            NULL,
                            UserMode,
                            NULL,
                            sizeof(EX_KEYED_EVENT),
                            0,
                            0,
                            (PVOID*)&ExpCritSecOutOfMemoryEvent);

    /* Check for success */
    if (!NT_SUCCESS(Status))
    {
        // FIXME
        KeBugCheck(0);
    }

    /* Initalize the keyed event */
    ExpCritSecOutOfMemoryEvent->Initialize();

    return STATUS_SUCCESS;
}

VOID
KEYED_EVENT::KEYED_EVENT ()
{
    ULONG i;

    /* Loop all hash buckets */
    for (i = 0; i < NUM_KEY_HASH_BUCKETS; i++)
    {
        /* Initialize the mutex and the wait lists */
        ExInitializePushLock(&KeyedEvent->HashTable[i].Lock);
        InitializeListHead(&KeyedEvent->HashTable[i].WaitListHead);
        InitializeListHead(&KeyedEvent->HashTable[i].ReleaseListHead);
    }
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
KEYED_EVENT::WaitOrWake (
    _In_ PVOID KeyedWaitValue,
    _In_ BOOLEAN Alertable,
    _In_ PLARGE_INTEGER Timeout,
    _In_ BOOLEAN Release)
{
    PETHREAD thread, currentThread;
    PEPROCESS currentProcess;
    PLIST_ENTRY listEntry, listHead1, listHead2;
    NTSTATUS status;
    ULONG_PTR hashIndex;
    PVOID previousKeyedWaitValue;

    /* Get the current process */
    currentProcess = PsGetCurrentProcess();

    /* Calculate the hash index */
    hashIndex = (ULONG_PTR)KeyedWaitValue >> 5;
    hashIndex ^= (ULONG_PTR)CurrentProcess >> 6;
    hashIndex %= NUM_KEY_HASH_BUCKETS;

    /* Lock the lists */
    for (auto lock : _HashTable[HashIndex].Lock)
    {
        /* Get the lists for search and wait, depending on whether
           we want to wait for the event or signal it */
        if (Release)
        {
            listHead1 = &_HashTable[hashIndex].WaitListHead;
            listHead2 = &_HashTable[hashIndex].WakeListHead;
        }
        else
        {
            listHead1 = &_HashTable[hashIndex].WakeListHead;
            listHead2 = &_HashTable[hashIndex].WaitListHead;
        }

        /* loop the first wait list */
        listEntry = listHead1->Flink;
        while (listEntry != listHead1)
        {
            /* Get the waiting thread. Note that this thread cannot be terminated
               as long as we hold the list lock, since it either needs to wait to
               be signaled by this thread or, when the wait is aborted due to thread
               termination, then it first needs to acquire the list lock. */
            thread = CONTAINING_RECORD(listEntry, ETHREAD, KeyedWaitChain);
            listEntry = listEntry->Flink;

            /* Check if this thread is a correct waiter */
            if ((thread->Tcb.Process == &CurrentProcess->Pcb) &&
                (thread->KeyedWaitValue == KeyedWaitValue))
            {
                /* Remove the thread from the list */
                RemoveEntryList(&thread->KeyedWaitChain);

                /* Initialize the list entry to show that it was removed */
                InitializeListHead(&thread->KeyedWaitChain);

                /* Wake the thread */
                thread->KeyedWaitSemaphore.Release(IO_NO_INCREMENT,
                                                   1,
                                                   FALSE);
                thread = NULL;

                return STATUS_SUCCESS;
            }
        }

        /* Get the current thread */
        currentThread = PsGetCurrentThread();

        /* Set the wait key and remember the old value */
        previousKeyedWaitValue = currentThread->KeyedWaitValue;
        currentThread->KeyedWaitValue = KeyedWaitValue;

        /* Initialize the wait semaphore */
        KeInitializeSemaphore(&currentThread->KeyedWaitSemaphore, 0, 1);

        /* Insert the current thread into the secondary wait list */
        InsertTailList(listHead2, &currentThread->KeyedWaitChain);
    }

    /* Wait for the keyed wait semaphore */
    status = currentThread->KeyedWaitSemaphore.Wait(WrKeyedEvent,
                                                    KernelMode,
                                                    Alertable,
                                                    Timeout);

    /* Check if the wait was aborted or timed out */
    if (status != STATUS_WAIT0)
    {
        /* Lock the lists to make sure no one else messes with the entry */
        for (auto lock : _HashTable[hashIndex].Lock)
        {
            /* Check if the wait list entry is still in the list */
            if (!IsListEmpty(&currentThread->KeyedWaitChain))
            {
                /* Remove the thread from the list */
                currentThread->KeyedWaitChain.RemoveEntryList();
                InitializeListHead(&currentThread->KeyedWaitChain);
            }
        }
    }

    /* Restore the previous KeyedWaitValue, since this is a union member */
    currentThread->KeyedWaitValue = previousKeyedWaitValue;

    return status;
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
KEYED_EVENT::Wait (
    _Inout_ PEX_KEYED_EVENT KeyedEvent,
    _In_ PVOID KeyedWaitValue,
    _In_ BOOLEAN Alertable,
    _In_ PLARGE_INTEGER Timeout)
{
    /* Call the generic internal function */
    return KeyedEvent->WaitOrWake(KeyedWaitValue,
                                  Alertable,
                                  Timeout,
                                  FALSE);
}

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
KEYED_EVENT::Wake (
    _Inout_ PEX_KEYED_EVENT KeyedEvent,
    _In_ PVOID KeyedWaitValue,
    _In_ BOOLEAN Alertable,
    _In_ PLARGE_INTEGER Timeout)
{
    /* Call the generic internal function */
    return KeyedEvent->WaitOrWake(KeyedWaitValue,
                                  Alertable,
                                  Timeout,
                                  TRUE);
}


/* EOF */
