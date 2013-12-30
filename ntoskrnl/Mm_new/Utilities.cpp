/*!

    \file Utilities.cpp

    \brief Implements misc utility functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "Utilities.hpp"

static const
USHORT ProtectToWin32Protect[32] =
{
    PAGE_NOACCESS, // MM_INVALID
    PAGE_READONLY, // MM_READONLY
    PAGE_EXECUTE_READ, // MM_EXECUTE
    PAGE_EXECUTE_READ, // MM_EXECUTE_READ
    PAGE_READWRITE, // MM_READWRITE
    PAGE_WRITECOPY, // MM_WRITECOPY
    PAGE_EXECUTE_READWRITE, // MM_EXECUTE_READWRITE
    PAGE_EXECUTE_WRITECOPY, // MM_EXECUTE_WRITECOPY

    PAGE_NOACCESS, // MM_UNCACHED | MM_INVALID
    PAGE_NOCACHE | PAGE_READONLY, // MM_UNCACHED | MM_READONLY
    PAGE_NOCACHE | PAGE_EXECUTE_READ, // MM_UNCACHED | MM_EXECUTE
    PAGE_NOCACHE | PAGE_EXECUTE_READ, // MM_UNCACHED | MM_EXECUTE_READ
    PAGE_NOCACHE | PAGE_READWRITE, // MM_UNCACHED | MM_READWRITE
    PAGE_NOCACHE | PAGE_WRITECOPY, // MM_UNCACHED | MM_WRITECOPY
    PAGE_NOCACHE | PAGE_EXECUTE_READWRITE, // MM_UNCACHED | MM_EXECUTE_READWRITE
    PAGE_NOCACHE | PAGE_EXECUTE_WRITECOPY, // MM_UNCACHED | MM_EXECUTE_WRITECOPY

    PAGE_NOACCESS, // MM_GUARDPAGE | MM_INVALID
    PAGE_GUARD | PAGE_READONLY, // MM_GUARDPAGE | MM_READONLY
    PAGE_GUARD | PAGE_EXECUTE_READ, // MM_GUARDPAGE | MM_EXECUTE
    PAGE_GUARD | PAGE_EXECUTE_READ, // MM_GUARDPAGE | MM_EXECUTE_READ
    PAGE_GUARD | PAGE_READWRITE, // MM_GUARDPAGE | MM_READWRITE
    PAGE_GUARD | PAGE_WRITECOPY, // MM_GUARDPAGE | MM_WRITECOPY
    PAGE_GUARD | PAGE_EXECUTE_READWRITE, // MM_GUARDPAGE | MM_EXECUTE_READWRITE
    PAGE_GUARD | PAGE_EXECUTE_WRITECOPY, // MM_GUARDPAGE | MM_EXECUTE_WRITECOPY

    PAGE_NOACCESS, // MM_WRITECOMBINE | MM_INVALID
    PAGE_WRITECOMBINE | PAGE_READONLY, // MM_WRITECOMBINE | MM_READONLY
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READ, // MM_WRITECOMBINE | MM_EXECUTE
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READ, // MM_WRITECOMBINE | MM_EXECUTE_READ
    PAGE_WRITECOMBINE | PAGE_READWRITE, // MM_WRITECOMBINE | MM_READWRITE
    PAGE_WRITECOMBINE | PAGE_WRITECOPY, // MM_WRITECOMBINE | MM_WRITECOPY
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READWRITE, // MM_WRITECOMBINE | MM_EXECUTE_READWRITE
    PAGE_WRITECOMBINE | PAGE_EXECUTE_WRITECOPY, // MM_WRITECOMBINE | MM_EXECUTE_WRITECOPY
};

/// HACK HACK HACK HACK
VOID
KeFlushMultipleTb (
    _In_ PVOID* AddressArray,
    _In_ ULONG AddressCount)
{
    while (AddressCount--)
    {
        __invlpg(AddressArray[AddressCount]);
    }
}

VOID
KeFlushRangeTb (
    _In_ PVOID BaseAddress,
    _In_ ULONG_PTR NumberOfPages)
{
    while (NumberOfPages--)
    {
        __invlpg(BaseAddress);
        BaseAddress = AddToPointer(BaseAddress, PAGE_SIZE);
    }
}

VOID
KeFlushProcessTb ()
{
    __writecr3(__readcr3());
}


namespace Mm {

/*! \fn ConvertProtect
 *
 *  \brief ...
 *
 *  \param [in] Win32Protect -
 *
 *  \return ...
 */
ULONG
ConvertProtect (
    _In_ ULONG Win32Protect)
{
    ULONG Protect = MM_INVALID;

    if (Win32Protect & PAGE_IS_WRITECOPY)
        Protect = MM_WRITECOPY;
    else if (Win32Protect & PAGE_IS_WRITABLE)
        Protect = MM_READWRITE;
    else if (Win32Protect & PAGE_IS_READABLE)
        Protect = MM_READONLY;

    if (Win32Protect & PAGE_IS_EXECUTABLE)
        Protect |= MM_EXECUTE;

    if (Win32Protect & PAGE_WRITECOMBINE)
        Protect |= MM_WRITECOMBINE;
    else if (Win32Protect & PAGE_NOCACHE)
        Protect |= MM_UNCACHED;

    return Protect;
}

/*! \fn ConvertProtectAndCaching
 *
 *  \brief ...
 *
 *  \param [in] Win32Protect -
 *
 *  \param [in] CachingType -
 *
 *  \return ...
 */
ULONG
ConvertProtectAndCaching (
    _In_ ULONG Win32Protect,
    _In_ MEMORY_CACHING_TYPE CachingType)
{
    /* Set caching type */
    Win32Protect &= ~(PAGE_NOCACHE | PAGE_WRITECOMBINE);
    if ((CachingType == MmNonCached) || (CachingType == MmNonCachedUnordered))
        Win32Protect |= PAGE_NOCACHE;
    else if (CachingType == MmWriteCombined)
        Win32Protect |= PAGE_WRITECOMBINE;

    return ConvertProtect(Win32Protect);
}

/*! \fn ConvertProtectToWin32
 *
 *  \brief ...
 *
 *  \param [in] Protect -
 *
 *  \return ...
 */
ULONG
ConvertProtectToWin32 (
    _In_ ULONG Protect)
{
    /* Convert it to the win32 format */
    return ProtectToWin32Protect[Protect & MM_PROTECTION_MASK];
}

}; // namespaceMm

