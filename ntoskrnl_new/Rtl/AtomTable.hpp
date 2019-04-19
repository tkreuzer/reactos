
#pragma once

#include "Rtl.hpp"

#define EX_PUSH_LOCK ULONG_PTR

typedef struct _RTL_ATOM_TABLE_REFERENCE
{
    LIST_ENTRY LowBoxList;
    ULONG LowBoxID;
    USHORT ReferenceCount;
    USHORT Flags;
} RTL_ATOM_TABLE_REFERENCE, *PRTL_ATOM_TABLE_REFERENCE;

typedef struct _RTL_ATOM_TABLE_ENTRY
{
    struct _RTL_ATOM_TABLE_ENTRY* HashLink;
    USHORT HandleIndex;
    USHORT Atom;
    RTL_ATOM_TABLE_REFERENCE Reference;
    UCHAR NameLength;
    WCHAR Name[1];
} RTL_ATOM_TABLE_ENTRY, *PRTL_ATOM_TABLE_ENTRY;

struct _HANDLE_TABLE;

typedef struct _RTL_ATOM_TABLE
{
    ULONG Signature;
    LONG ReferenceCount;
    EX_PUSH_LOCK PushLock;
    struct _HANDLE_TABLE* ExHandleTable;
    ULONG Flags;
    ULONG NumberOfBuckets;
    PRTL_ATOM_TABLE_ENTRY Buckets[1];
} RTL_ATOM_TABLE, *PRTL_ATOM_TABLE;
