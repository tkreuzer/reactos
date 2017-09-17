#define _USE_DECLSPECS_FOR_SAL 0
#define _USE_ATTRIBUTES_FOR_SAL 1

#include <SpecStrings.h>

#define NULL ((void*)0)
typedef long NTSTATUS;
typedef unsigned char BOOLEAN;
typedef enum _POOL_TYPE POOL_TYPE;
typedef struct _SECURITY_DESCRIPTOR *PSECURITY_DESCRIPTOR;
typedef struct _SECURITY_SUBJECT_CONTEXT *PSECURITY_SUBJECT_CONTEXT;
typedef struct _GENERIC_MAPPING *PGENERIC_MAPPING;

NTSTATUS SeAssignSecurity(
  __in_opt  PSECURITY_DESCRIPTOR ParentDescriptor,
  __in_opt  PSECURITY_DESCRIPTOR ExplicitDescriptor,
  __out     PSECURITY_DESCRIPTOR *NewDescriptor,
  __in      BOOLEAN IsDirectoryObject,
  __in      PSECURITY_SUBJECT_CONTEXT SubjectContext,
  __in      PGENERIC_MAPPING GenericMapping,
  __in      POOL_TYPE PoolType
);

PSECURITY_DESCRIPTOR
Test_SeAssignSecurity(
    PSECURITY_SUBJECT_CONTEXT SubjectContext,
    PGENERIC_MAPPING GenericMapping)
{
    NTSTATUS Status;
    PSECURITY_DESCRIPTOR NewDescriptor;

    Status = SeAssignSecurity(NULL,
                              NULL,
                              &NewDescriptor,
                              0,
                              SubjectContext,
                              GenericMapping,
                              0);

    return NewDescriptor;
}

