#pragma once

#include "ntosbase.h"
#include <ndk/obtypes.h>

namespace Ob {

class OBJECT
{

public:

    static inline
    NTSTATUS
    CreateObjectEx (
        _Out_ PVOID* OutObject,
		_In_ POBJECT_TYPE Type,
		_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
		_In_ KPROCESSOR_MODE AccessMode,
		_Inout_opt_ PVOID ParseContext,
		_In_ ULONG ObjectSize,
		_In_opt_ ULONG PagedPoolCharge,
		_In_opt_ ULONG NonPagedPoolCharge)
    {
        return ObCreateObject(KernelMode,
                              Type,
                              ObjectAttributes,
                              AccessMode,
                              ParseContext,
                              ObjectSize,
                              PagedPoolCharge,
                              NonPagedPoolCharge,
                              OutObject);
    }

    static inline
    NTSTATUS
    CreateObject (
        _Out_ PVOID* OutObject,
        _In_ POBJECT_TYPE Type,
		_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes)
    {
        ULONG ObjectSize;

        if ((Type->TypeInfo.PoolType & 1) == PagedPool)
            ObjectSize = Type->TypeInfo.DefaultPagedPoolCharge;
        else
            ObjectSize = Type->TypeInfo.DefaultNonPagedPoolCharge;

        return ObCreateObject(KernelMode,
                              Type,
                              ObjectAttributes,
                              ExGetPreviousMode(),
                              NULL,
                              ObjectSize,
                              Type->TypeInfo.DefaultPagedPoolCharge,
                              Type->TypeInfo.DefaultNonPagedPoolCharge,
                              OutObject);
    }

    static inline
    NTSTATUS
    ReferenceObjectByHandle (
        _Out_ PVOID* Object,
        _In_ HANDLE Handle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_opt_ POBJECT_TYPE ObjectType,
        _In_ KPROCESSOR_MODE AccessMode,
        _Out_opt_ POBJECT_HANDLE_INFORMATION HandleInformation)
    {
        return ObReferenceObjectByHandle(Handle,
                                         DesiredAccess,
                                         ObjectType,
                                         AccessMode,
                                         Object,
                                         HandleInformation);
    }

    inline
    VOID
    ReferenceObject (
        VOID)
    {
        ObReferenceObject(this);
    }

    inline
    NTSTATUS
    ReferenceObjectByPointer (
        _In_ ACCESS_MASK DesiredAccess,
        _In_opt_ POBJECT_TYPE ObjectType,
        _In_ KPROCESSOR_MODE AccessMode)
    {
        ObReferenceObjectByPointer(this,
                                   DesiredAccess,
                                   ObjectType,
                                   AccessMode);
    }

    VOID
    DereferenceObject (
        VOID)
    {
        ObDereferenceObject(this);
    }

};

}; // namespace Ob


