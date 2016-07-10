

NTSTATUS
NTAPI
LdrAccessResource(
    IN PVOID BaseAddress,
    IN PIMAGE_RESOURCE_DATA_ENTRY ResourceDataEntry,
    OUT PVOID *Resource OPTIONAL,
    OUT PULONG Size OPTIONAL);

NTSTATUS
NTAPI
LdrFindResource_U(
    IN PVOID BaseAddress,
    IN PLDR_RESOURCE_INFO ResourceInfo,
    IN ULONG Level,
    OUT PIMAGE_RESOURCE_DATA_ENTRY *ResourceDataEntry);

