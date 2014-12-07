
#pragma once

#include <ntoskrnl.h>

typedef PVOID PTOKEN_SECURITY_ATTRIBUTES_INFORMATION;
typedef struct _ACL *PACL;

typedef enum _TOKEN_INFORMATION_CLASS
{
    TokenUser = 1,
    TokenGroups,
    TokenPrivileges,
    TokenOwner,
    TokenPrimaryGroup,
    TokenDefaultDacl,
    TokenSource,
    TokenType,
    TokenImpersonationLevel,
    TokenStatistics,
    TokenRestrictedSids,
    TokenSessionId,
    TokenGroupsAndPrivileges,
    TokenSessionReference,
    TokenSandBoxInert,
    TokenAuditPolicy,
    TokenOrigin,
    TokenElevationType,
    TokenLinkedToken,
    TokenElevation,
    TokenHasRestrictions,
    TokenAccessInformation,
    TokenVirtualizationAllowed,
    TokenVirtualizationEnabled,
    TokenIntegrityLevel,
    TokenUIAccess,
    TokenMandatoryPolicy,
    TokenLogonSid,
    TokenIsAppContainer,
    TokenCapabilities,
    TokenAppContainerSid,
    TokenAppContainerNumber,
    TokenUserClaimAttributes,
    TokenDeviceClaimAttributes,
    TokenRestrictedUserClaimAttributes,
    TokenRestrictedDeviceClaimAttributes,
    TokenDeviceGroups,
    TokenRestrictedDeviceGroups,
    TokenSecurityAttributes,
    TokenIsRestricted,
    TokenProcessTrustLevel,
    TokenPrivateNameSpace,
    MaxTokenInfoClass
} TOKEN_INFORMATION_CLASS, *PTOKEN_INFORMATION_CLASS;

// ntifs.h
typedef enum _TOKEN_TYPE
{
    TokenPrimary = 1,
    TokenImpersonation
} TOKEN_TYPE, *PTOKEN_TYPE;

typedef struct _TOKEN_GROUPS
{
    ULONG GroupCount;
#ifdef MIDL_PASS
    [size_is(GroupCount)] SID_AND_ATTRIBUTES Groups[*];
#else // MIDL_PASS
    SID_AND_ATTRIBUTES Groups[ANYSIZE_ARRAY];
#endif // MIDL_PASS
} TOKEN_GROUPS, *PTOKEN_GROUPS;

#define TOKEN_SOURCE_LENGTH 8
typedef struct _TOKEN_SOURCE
{
    CHAR SourceName[TOKEN_SOURCE_LENGTH];
    LUID SourceIdentifier;
} TOKEN_SOURCE, *PTOKEN_SOURCE;

// ntifs.h
typedef struct _TOKEN_USER
{
    SID_AND_ATTRIBUTES User;
} TOKEN_USER, *PTOKEN_USER;

// ntifs.h
typedef struct _TOKEN_OWNER
{
    PSID Owner;
} TOKEN_OWNER, *PTOKEN_OWNER;

// ntifs.h
typedef struct _TOKEN_PRIVILEGES
{
    ULONG PrivilegeCount;
    LUID_AND_ATTRIBUTES Privileges[ANYSIZE_ARRAY];
} TOKEN_PRIVILEGES, *PTOKEN_PRIVILEGES;

// ntifs.h
typedef struct _TOKEN_PRIMARY_GROUP
{
    PSID PrimaryGroup;
} TOKEN_PRIMARY_GROUP, *PTOKEN_PRIMARY_GROUP;

// ntifs.h
typedef struct _TOKEN_DEFAULT_DACL
{
    PACL DefaultDacl;
} TOKEN_DEFAULT_DACL, *PTOKEN_DEFAULT_DACL;

// ntifs.h
typedef struct _TOKEN_MANDATORY_POLICY
{
    ULONG Policy;
} TOKEN_MANDATORY_POLICY, *PTOKEN_MANDATORY_POLICY;

