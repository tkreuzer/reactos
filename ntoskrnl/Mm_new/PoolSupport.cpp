
#include "ntosbase.h"

#define UNIMPLEMENTED __debugbreak()

extern "C" {

POOL_TYPE
NTAPI
MmDeterminePoolType (
    IN PVOID VirtualAddress)
{
    UNIMPLEMENTED;
    return PagedPool;
}

PVOID
NTAPI
MiAllocatePoolPages (
    IN POOL_TYPE PoolType,
    IN SIZE_T SizeInBytes)
{
    UNIMPLEMENTED;
    return NULL;
}

ULONG
NTAPI
MiFreePoolPages (
    IN PVOID StartingAddress)
{
    UNIMPLEMENTED;
    return 0;
}

BOOLEAN
NTAPI
MmUseSpecialPool (
    IN SIZE_T NumberOfBytes,
    IN ULONG Tag)
{
    UNIMPLEMENTED;
    return 0;
}

BOOLEAN
NTAPI
MmIsSpecialPoolAddress (
    IN PVOID P)
{
    UNIMPLEMENTED;
    return 0;
}

PVOID
NTAPI
MmAllocateSpecialPool (
    IN SIZE_T NumberOfBytes,
    IN ULONG Tag,
    IN POOL_TYPE PoolType,
    IN ULONG SpecialType)
{
    UNIMPLEMENTED;
    return NULL;
}

VOID
NTAPI
MmFreeSpecialPool (
    IN PVOID P)
{
    UNIMPLEMENTED;
}



}; // extern "C"
