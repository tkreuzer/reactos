
#include "Obp.hpp"

extern "C" {

typedef struct _OBJECT_TYPE_INITIALIZER *POBJECT_TYPE_INITIALIZER;
POBJECT_TYPE ObpTypeObjectType;

} // extern "C"

// ntosifs.h
extern "C"
NTSTATUS
NTAPI
ObCreateObjectTypeEx (
    _In_ PUNICODE_STRING TypeName,
    _In_ POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    _In_opt_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ LONG_PTR WaitObjectInfo,
    _Outptr_ POBJECT_TYPE *ObjectType);

// ntosifs.h
extern "C"
NTSTATUS
NTAPI
ObCreateObjectType (
    _In_ PUNICODE_STRING TypeName,
    _In_ POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    _In_opt_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Outptr_ POBJECT_TYPE *ObjectType)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

extern "C"
POBJECT_TYPE
NTAPI
ObGetObjectType (
    _In_ PVOID Object)
{
    __debugbreak();
    return NULL;
}
