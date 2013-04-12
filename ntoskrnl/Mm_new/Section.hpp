

#pragma once

#include "ntosbase.h"
#include "ntimage.h"

/// \todo HACK
#define IMAGE_FILE_MACHINE_NATIVE IMAGE_FILE_MACHINE_AMD64

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

class SECTION
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
    CreateImageFileSection (
        _In_ PFILE_OBJECT FileObject);

    VOID
    SetPageContent (
        _In_ ULONG RelativeStartingVpn,
        _In_ ULONG NumberOfPages,
        _In_ PVOID Buffer);

    NTSTATUS
    PrefetchPages (
        _In_ ULONG RelativeStartingVpn,
        _In_ ULONG NumberOfPages);

    NTSTATUS
    GetMapping (
        _Out_ PVOID* BaseAddress,
        _In_ ULONG RelativeStartingVpn,
        _In_ ULONG NumberOfPages);

    VOID
    Release (
        VOID);

};




}; // namespace Mm
