/*
* PROJECT:         ReactOS Kernel
* LICENSE:         GPL - See COPYING in the top level directory
* FILE:            ntoskrnl/ob/reference.c
* PURPOSE:         Ob functions for referencing and dereferencing
* PROGRAMMERS:     Timo Kreuzer (timo.kreuzer@reactos.org)
*/

/* INCLUDES ******************************************************************/

#include "Obp.hpp"

/*! \name ObfReferenceObject
*
*  \see ObfReferenceObjectWithTag
*
*  \ref
*  - http://msdn.microsoft.com/en-us/library/ff558678.aspx
*  - http://msdn.microsoft.com/en-us/library/ff558690.aspx
*/
extern "C"
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG_PTR
FASTCALL
ObfReferenceObject (
    _In_ PVOID Object)
{
    /* Use the extended routine and pass the default tag */
    return ObfReferenceObjectWithTag(Object, 'tlfD');
}

extern "C"
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG_PTR
FASTCALL
ObfDereferenceObject (
    _In_ PVOID Object)
{
    __debugbreak();
    return 0;
}

#undef ObDereferenceObject
extern "C"
_IRQL_requires_max_(DISPATCH_LEVEL)
LONG_PTR
NTAPI
ObDereferenceObject (
    _In_ PVOID Object)
{
    return ObfDereferenceObject(Object);
}

extern "C"
LONG
FASTCALL
ObReferenceObjectEx (
    _In_ PVOID Object,
    _In_ LONG Count)
{
    __debugbreak();
    return 0;
}

extern "C"
LONG
FASTCALL
ObDereferenceObjectEx (
    _In_ PVOID Object,
    _In_ LONG Count)
{
    __debugbreak();
    return 0;
}

/*! \name ObfReferenceObjectWithTag
*
*  \see ObfReferenceObject
*
*  \ref
*  - http://msdn.microsoft.com/en-us/library/ff558690.aspx
*/
extern "C"
LONG_PTR
FASTCALL
ObfReferenceObjectWithTag (
    _In_ PVOID Object,
    _In_ ULONG Tag)
{
    __debugbreak();
    return 0;
}

extern "C"
LONG_PTR
FASTCALL
ObfDereferenceObjectWithTag (
    _In_ PVOID Object,
    _In_ ULONG Tag)
{
    __debugbreak();
    return 0;
}

extern "C"
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
NTAPI
ObReferenceObjectByPointer (
    _In_ PVOID Object,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
NTSTATUS
NTAPI
ObReferenceObjectByPointerWithTag (
    _In_ PVOID Object,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ ULONG Tag)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosifs.h
extern "C"
NTSTATUS
NTAPI
ObReferenceObjectByName (
    _In_ PUNICODE_STRING ObjectName,
    _In_ ULONG Attributes,
    _In_opt_ PACCESS_STATE AccessState,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _Inout_opt_ PVOID ParseContext,
    _Out_ PVOID *Object)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
BOOLEAN
FASTCALL
ObReferenceObjectSafe (
    _In_ PVOID Object)
{
    __debugbreak();
    return FALSE;
}

extern "C"
BOOLEAN
FASTCALL
ObReferenceObjectSafeWithTag (
    _In_ PVOID Object,
    _In_ ULONG Tag)
{
    __debugbreak();
    return FALSE;
}

extern "C"
VOID
NTAPI
ObDereferenceObjectDeferDelete (
    _In_ PVOID Object)
{
    __debugbreak();
}

extern "C"
VOID
NTAPI
ObDereferenceObjectDeferDeleteWithTag (
    _In_ PVOID Object,
    _In_ ULONG Tag)
{
    __debugbreak();
}


