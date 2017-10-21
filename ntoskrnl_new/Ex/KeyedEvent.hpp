
#pragma once


namespace Ex {

#define NUM_KEY_HASH_BUCKETS 23

class KEYED_EVENT : public OBJECT
{

private:

    struct KEYED_EVENT_HASHBUCKET
    {
        PUSH_LOCK Lock;
        LIST_HEAD WaitListHead;
        LIST_HEAD WakeListHead;
    };

    KEYED_EVENT_HASHBUCKET _HashTable[NUM_KEY_HASH_BUCKETS];

    _IRQL_requires_max_(APC_LEVEL)
    NTSTATUS
    WaitOrWake (
        _In_ PVOID KeyedWaitValue,
        _In_ BOOLEAN Alertable,
        _In_ PLARGE_INTEGER Timeout,
        _In_ BOOLEAN Release):

public:

    _IRQL_requires_max_(APC_LEVEL)
    NTSTATUS
    Wait (
        _Inout_ PEX_KEYED_EVENT KeyedEvent,
        _In_ PVOID KeyedWaitValue,
        _In_ BOOLEAN Alertable,
        _In_ PLARGE_INTEGER Timeout);

    _IRQL_requires_max_(APC_LEVEL)
    NTSTATUS
    Wake (
        _Inout_ PEX_KEYED_EVENT KeyedEvent,
        _In_ PVOID KeyedWaitValue,
        _In_ BOOLEAN Alertable,
        _In_ PLARGE_INTEGER Timeout);


};

}; // namespace Ex
