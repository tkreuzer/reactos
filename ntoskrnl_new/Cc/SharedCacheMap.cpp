
#include "Ccp.hpp"
#include "SharedCacheMap.hpp"

namespace Cc {

extern "C" {

/*! \name CcInitializeCacheMap
 *
 *  \param FileObject -
 *
 *  \param FileSizes -
 *
 *  \param PinAccess -
 *
 *  \param Callbacks -
 *
 *  \param LazyWriteContext -
 *
 *  \remarks
 *      This routine requires that the FCB for the file be acquired either
 *      shared or exclusive prior to invoking the routine.
 */
VOID
NTAPI
CcInitializeCacheMap (
    _In_ PFILE_OBJECT FileObject,
    _In_ PCC_FILE_SIZES FileSizes,
    _In_ BOOLEAN PinAccess,
    _In_ PCACHE_MANAGER_CALLBACKS Callbacks,
    _In_ PVOID LazyWriteContext)
{
    __debugbreak();
}

/*! \fn CcUninitializeCacheMap
 *
 *  \param FileObject -
 *
 *  \param TruncateSize -
 *
 *  \param UninitializeCompleteEvent -
 *
 *  \remarks
 *      The FCB for the file stream must be acquired exclusively before
 *      invoking this routine.
 */
BOOLEAN
NTAPI
CcUninitializeCacheMap (
    _In_ PFILE_OBJECT FileObject,
    _In_opt_ PLARGE_INTEGER TruncateSize,
    _In_opt_ PCACHE_UNINITIALIZE_EVENT UninitializeCompleteEvent)
{
    // call CcPurgeCacheSection to purge any cached data that is no longer part of the file.
    // Enqueue the Event in the SharedCacheMap
    __debugbreak();
    return FALSE;
}

}; // extern "C"
}; // namespace Cc
