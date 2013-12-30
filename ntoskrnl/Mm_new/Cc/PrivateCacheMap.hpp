
#pragma once

#include "..\ntosbase.h"
#include <ndk/rtlfuncs.h>
#include <ndk/mmfuncs.h>

namespace Cc {

typedef class PRIVATE_CACHE_MAP
{
private:
    USHORT m_NodeTypeCode;
    union
    {
        struct
        {
            USHORT ReadAheadActive  : 1;
            USHORT ReadAheadEnabled : 1;
            USHORT PagePriority : 3;
            USHORT PipelineReadAheads : 1;
        };
        USHORT Short;
    } m_Flags;
    ULONG m_ReadAheadMask;
    PFILE_OBJECT m_FileObject;
    LARGE_INTEGER m_FileOffset1;
    LARGE_INTEGER m_BeyondLastByte1;
    LARGE_INTEGER m_FileOffset2;
    LARGE_INTEGER m_BeyondLastByte2;
    ULONG m_SequentialReadCount;
    ULONG m_ReadAheadLength;
    LARGE_INTEGER m_ReadAheadOffset;
    LARGE_INTEGER m_ReadAheadBeyondLastByte;
    UINT64 m_PrevReadAheadBeyondLastByte;
    ULONG m_ReadAheadSpinLock;
    ULONG m_PipelinedReadAheadRequestSize;
    ULONG m_ReadAheadGrowth;
    LIST_ENTRY m_PrivateLinks;
    PVOID m_ReadAheadWorkItem;

    static const USHORT CcNodeTypePrivateCacheMap = 0x1234;

    friend class SHARED_CACHE_MAP;

    inline
    void*
    operator new(size_t Size)
    {
        return ExAllocatePoolWithTag(NonPagedPool, Size, 'cPcC');
    }

    PRIVATE_CACHE_MAP();

    VOID
    UnInitialize (
        VOID);

public:

    VOID
    Initialize (
        _In_ PFILE_OBJECT FileObject);

    static
    NTSTATUS
    CreateInstance (
        _Out_ class PRIVATE_CACHE_MAP** OutPrivateCacheMap,
        _In_ PFILE_OBJECT FileObject);

    inline
    PFILE_OBJECT
    GetFileObject (
        VOID)
    {
        return m_FileObject;
    }

} *PPRIVATE_CACHE_MAP;


}; // namespace Cc

