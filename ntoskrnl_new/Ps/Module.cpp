
#include "Ps.hpp"
#include <Ex/Resource.hpp>

extern "C" {

LIST_ENTRY PsLoadedModuleList;
ERESOURCE PsLoadedModuleResource;

// ntosp.h
typedef struct _IMAGE_INFO
{
    union
    {
        ULONG Properties;
        struct
        {
            ULONG ImageAddressingMode  : 8;
            ULONG SystemModeImage      : 1;
            ULONG ImageMappedToAllPids : 1;
            ULONG ExtendedInfoPresent  : 1;
            ULONG MachineTypeMismatch  : 1;
            ULONG ImageSignatureLevel  : 4;
            ULONG ImageSignatureType   : 3;
            ULONG ImagePartialMap      : 1;
            ULONG Reserved             : 12;
        };
    };
    PVOID       ImageBase;
    ULONG       ImageSelector;
    SIZE_T      ImageSize;
    ULONG       ImageSectionNumber;
} IMAGE_INFO, *PIMAGE_INFO;

// ntosp.h
typedef struct _IMAGE_INFO_EX
{
    SIZE_T              Size;
    IMAGE_INFO          ImageInfo;
    struct _FILE_OBJECT *FileObject;
} IMAGE_INFO_EX, *PIMAGE_INFO_EX;

// ntosp.h
typedef
VOID
(NTAPI *PLOAD_IMAGE_NOTIFY_ROUTINE) (
    _In_opt_ PUNICODE_STRING FullImageName,
    _In_ HANDLE ProcessId,
    _In_ PIMAGE_INFO ImageInfo);

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PsSetLoadImageNotifyRoutine (
    _In_ PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
PsRemoveLoadImageNotifyRoutine (
    _In_ PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"
