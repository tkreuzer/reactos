

#pragma once

#include "ntosbase.h"
#include "Ob/RefObject.hpp"
#include "ntimage.h"

/// \todo HACK
#define IMAGE_FILE_MACHINE_NATIVE IMAGE_FILE_MACHINE_AMD64

static const ULONG TAG_TEMP = 'xxmM';
static const ULONG TAG_SECTION = 'tSmM';

//#define TAG_SECTION 'cSmM'

namespace Mm {

/* Forward declarations */
typedef class SECTION *PSECTION;

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

typedef struct _CONTROL_AREA
{
    struct _SEGMENT* Segment;
    LIST_ENTRY DereferenceList;
    ULONG_PTR NumberOfSectionReferences;
    ULONG_PTR NumberOfPfnReferences;
    ULONG_PTR NumberOfMappedViews;
    ULONG_PTR NumberOfSystemCacheViews;
    ULONG_PTR NumberOfUserReferences;
    ULONG NumberOfSubsections;
    union
    {
        ULONG LongFlags;
        //MMSECTION_FLAGS Flags;
    };
    PFILE_OBJECT FilePointer;
    struct _EVENT_COUNTER* WaitingForDeletion;
    USHORT ModifiedWriteCount;
    USHORT FlushInProgressCount;
    ULONG WritableUserReferences;
    ULONG QuadwordPad;
    PIMAGE_SECTION_HEADER SectionHeaders;
} CONTROL_AREA, *PCONTROL_AREA;

typedef struct _SUBSECTION
{
    //PCONTROL_AREA ControlArea;
    union
    {
        ULONG LongFlags;
        //MMSUBSECTION_FLAGS Flags;
    };
    ULONG StartingSector;
    ULONG NumberOfFullSectors;
    //struct PTE* SubsectionBase;
    //ULONG UnusedPtes;
    ULONG RelativeStartingVpn;
    ULONG NumberOfPages;
    //struct _SUBSECTION* NextSubsection;
    struct _IMAGE_SECTION_HEADER* SectionHeader;
} SUBSECTION, *PSUBSECTION;

typedef struct _SEGMENT
{
    PSECTION_IMAGE_INFORMATION_EX ImageInformation;
} SEGMENT, *PSEGMENT;

class SECTION : public REF_OBJECT<SECTION, NonPagedPool, TAG_SECTION>
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
        _In_ ULONG RelativeVpn);

    SECTION (
        VOID);

    ~SECTION (
        VOID);

    friend class super;
    friend class MEMORY_MANAGER;

public:


    static
    NTSTATUS
    CreateInstance (
        _Out_ PSECTION* OutSection,
        _In_ ULONG NumberOfSubsections,
        _In_ ULONG NumberOfPtes);

    static
    NTSTATUS
    CreatePageFileSection (
        _Out_ PSECTION* OutSection,
        _In_ ULONG64 MaximumSize,
        _In_ ULONG SectionPageProtection,
        _In_ ULONG AllocationAttributes);

    static
    NTSTATUS
    CreateImageFileSection (
        _In_ PFILE_OBJECT FileObject);

    VOID
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

};


}; // namespace Mm
