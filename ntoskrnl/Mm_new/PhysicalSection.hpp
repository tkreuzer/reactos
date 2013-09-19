
#include "linux/PhysicalSection.hpp"

#if 0
#pragma once

#include "ntosbase.h"
#include "Ob/RefObject.hpp"
#include "ntimage.h"

/// \todo HACK
//#define IMAGE_FILE_MACHINE_NATIVE IMAGE_FILE_MACHINE_AMD64

static const ULONG TAG_TEMP = 'xxmM';
static const ULONG TAG_SECTION = 'tSmM';

//#define TAG_SECTION 'cSmM'

namespace Mm {

/* Forward declarations */
typedef class PHYSICAL_SECTION *PPHYSICAL_SECTION;

typedef struct _SECTION_IMAGE_INFORMATION
{
    PVOID TransferAddress;
    ULONG ZeroBits;
    SIZE_T MaximumStackSize;
    SIZE_T CommittedStackSize;
    ULONG SubSystemType;
    union
    {
        struct
        {
            USHORT SubSystemMinorVersion;
            USHORT SubSystemMajorVersion;
        };
        ULONG SubSystemVersion;
    };
    ULONG GpValue;
    USHORT ImageCharacteristics;
    USHORT DllCharacteristics;
    USHORT Machine;
    BOOLEAN ImageContainsCode;
    UCHAR ImageFlags;
    ULONG LoaderFlags;
    ULONG ImageFileSize;
    ULONG CheckSum;
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

typedef struct _SECTION_IMAGE_INFORMATION_EX : _SECTION_IMAGE_INFORMATION
{
    ULONG SizeOfHeaders;
    ULONG SizeOfImage;
} SECTION_IMAGE_INFORMATION_EX, *PSECTION_IMAGE_INFORMATION_EX;

typedef struct _SECTION_WAIT_BLOCK
{
    struct _SECTION_WAIT_BLOCK* Next;
    KGATE Gate;
} SECTION_WAIT_BLOCK, *PSECTION_WAIT_BLOCK;

typedef struct _SECTION_FLAGS
{
    ULONG Image : 1;
    ULONG Commit : 1;
} SECTION_FLAGS;

typedef struct _CONTROL_AREA
{
    class SEGMENT* Segment;
    PFILE_OBJECT FileObject;
    struct _IMAGE_SECTION_HEADER* SectionHeaders;
    ULONG_PTR SizeInPages;
    ULONG_PTR NumberOfSectionReferences;
    ULONG_PTR NumberOfPfnReferences;
    ULONG_PTR NumberOfMappedViews;
    ULONG_PTR NumberOfSystemCacheViews;
    ULONG_PTR NumberOfUserReferences;
    ULONG NumberOfSubsections;
    union
    {
        ULONG LongFlags;
        SECTION_FLAGS Flags;
    };
    struct _EVENT_COUNTER* WaitingForDeletion;
    USHORT ModifiedWriteCount;
    USHORT FlushInProgressCount;
    ULONG WritableUserReferences;
    PVOID BaseAddress;
} CONTROL_AREA, *PCONTROL_AREA;

typedef struct _SUBSECTION_FLAGS
{
    ULONG FooBar : 1;
} SUBSECTION_FLAGS;

typedef struct _SUBSECTION
{
    //PCONTROL_AREA ControlArea;
    union
    {
        ULONG LongFlags;
        SUBSECTION_FLAGS Flags;
    };
    ULONG StartingSector;
    ULONG NumberOfFullSectors;
    //struct PROTOTYPE* SubsectionBase;
    ULONG BaseSegmentIndex;
    //ULONG UnusedPtes;
    ULONG RelativeStartingVpn;
    ULONG NumberOfPages;
    //struct _SUBSECTION* NextSubsection;
    struct _IMAGE_SECTION_HEADER* SectionHeader;
    ULONG Protect;
} SUBSECTION, *PSUBSECTION;

class PHYSICAL_SECTION : public REF_OBJECT<PHYSICAL_SECTION, NonPagedPool, TAG_SECTION>
{
private:
    static UCHAR DllImageBias;
    static const RTL_BITMAP ImageLoadBitMap;

    CONTROL_AREA m_ControlArea;
    SUBSECTION m_Subsections[1];

    static
    VOID
    InitializeClass (
        VOID);

    ULONG
    RelativeVpnToSubsectionIndex (
        _In_ ULONG_PTR RelativeVpn);

    PHYSICAL_SECTION (
        VOID);

    ~PHYSICAL_SECTION (
        VOID);

    //friend super;
    friend class REF_OBJECT<PHYSICAL_SECTION, NonPagedPool, TAG_SECTION>;
    friend class MEMORY_MANAGER;

public:

    static
    NTSTATUS
    CreateInstance (
        _Out_ PPHYSICAL_SECTION* OutSection,
        _In_ ULONG NumberOfSubsections,
        _In_ ULONG_PTR NumberOfPtes);

    static
    NTSTATUS
    CreatePageFileSection (
        _Out_ PPHYSICAL_SECTION* OutSection,
        _In_ ULONG64 MaximumSize,
        _In_ ULONG SectionPageProtection,
        _In_ ULONG AllocationAttributes);

    static
    NTSTATUS
    ReferenceOrCreateFileSection (
        _Out_ PPHYSICAL_SECTION* OutPhysicalSection,
        _Inout_ PFILE_OBJECT FileObject,
        _In_ ULONG AllocationAttributes);

    static
    NTSTATUS
    CreateImageFileSection (
        _Out_ PPHYSICAL_SECTION* OutPhysicalSection,
        _In_ PFILE_OBJECT FileObject);

    inline
    PVOID
    GetBaseAddress (
        VOID)
    {
        return m_ControlArea.BaseAddress;
    }

    inline
    SIZE_T
    GetSizeInPages (
        VOID)
    {
        return m_ControlArea.SizeInPages;
    }

    NTSTATUS
    CommitPages (
        _In_ ULONG_PTR RelativeStartingVpn,
        _In_ ULONG_PTR NumberOfPages,
        _In_ ULONG Protect);

    NTSTATUS
    SetPageContent (
        _In_ ULONG_PTR RelativeStartingVpn,
        _In_ ULONG_PTR NumberOfPages,
        _In_ PVOID Buffer);

    NTSTATUS
    PrefetchPages (
        _In_ ULONG_PTR RelativeStartingVpn,
        _In_ ULONG_PTR NumberOfPages);

    NTSTATUS
    CreateMapping (
        _In_ PVOID BaseAddress,
        _In_ ULONG_PTR RelativeStartingVpn,
        _In_ ULONG_PTR NumberOfPages,
        _In_ ULONG Protect);

    NTSTATUS
    GetMapping (
        _Out_ PVOID* BaseAddress,
        _In_ ULONG_PTR RelativeStartingVpn,
        _In_ ULONG_PTR NumberOfPages);

    VOID
    RemoveMapping (
        _In_ PVOID BaseAddress,
        _In_ SIZE_T Size);

};


}; // namespace Mm

#endif
