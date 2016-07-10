

/* Resource Type Levels */
#define RESOURCE_TYPE_LEVEL      0
#define RESOURCE_NAME_LEVEL      1
#define RESOURCE_LANGUAGE_LEVEL  2
#define RESOURCE_DATA_LEVEL      3


typedef struct _LDR_DATA_TABLE_ENTRY
{
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    ULONG Flags;
    USHORT LoadCount;
    USHORT TlsIndex;
    union
    {
        LIST_ENTRY HashLinks;
        struct
        {
            PVOID SectionPointer;
            ULONG CheckSum;
        };
    };
    union
    {
        ULONG TimeDateStamp;
        PVOID LoadedImports;
    };
    PVOID EntryPointActivationContext;
    PVOID PatchInformation;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _LDR_RESOURCE_INFO
{
    ULONG_PTR Type;
    ULONG_PTR Name;
    ULONG Language;
} LDR_RESOURCE_INFO, *PLDR_RESOURCE_INFO;
