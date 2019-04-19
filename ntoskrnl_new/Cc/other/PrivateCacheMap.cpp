
#include "PrivateCacheMap.hpp"

namespace Cc {

PRIVATE_CACHE_MAP::PRIVATE_CACHE_MAP()
{
    /* Zero out the structure */
    RtlZeroMemory(this, sizeof(*this));
}

VOID
PRIVATE_CACHE_MAP::Initialize (
    _In_ PFILE_OBJECT FileObject)
{

    m_NodeTypeCode = CcNodeTypePrivateCacheMap;
    m_ReadAheadMask = 4095;
    KeInitializeSpinLock(&m_ReadAheadSpinLock);
    //m_Flags.PagePriority = PsGetCurrentThread()->CrossThreadFlags.ThreadPagePriority;

    /* Reference the file object */
    ObReferenceObject(FileObject);
    m_FileObject = FileObject;
}

VOID
PRIVATE_CACHE_MAP::UnInitialize (
    VOID)
{
    ObDereferenceObject(m_FileObject);
    m_FileObject = NULL;
}

NTSTATUS
PRIVATE_CACHE_MAP::CreateInstance (
    _Out_ PPRIVATE_CACHE_MAP* OutPrivateCacheMap,
    _In_ PFILE_OBJECT FileObject)
{
    PPRIVATE_CACHE_MAP PrivateCacheMap;

    /* Allocate a new private cache map from non-paged pool */
    PrivateCacheMap = new PRIVATE_CACHE_MAP;
    if (PrivateCacheMap == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    PrivateCacheMap->Initialize(FileObject);

    *OutPrivateCacheMap = PrivateCacheMap;
    return STATUS_SUCCESS;
}

}; // namespace Cc
