          typedef struct _ACCESS_REASONS // 1 elements, 0x80 bytes (sizeof)
          {
/*0x000*/     ULONG32      Data[32];
          }ACCESS_REASONS, *PACCESS_REASONS;

          typedef struct _ACCESS_STATE                                 // 16 elements, 0xA0 bytes (sizeof)
          {
/*0x000*/     struct _LUID OperationID;                                // 2 elements, 0x8 bytes (sizeof)
/*0x008*/     UINT8        SecurityEvaluated;
/*0x009*/     UINT8        GenerateAudit;
/*0x00A*/     UINT8        GenerateOnClose;
/*0x00B*/     UINT8        PrivilegesAllocated;
/*0x00C*/     ULONG32      Flags;
/*0x010*/     ULONG32      RemainingDesiredAccess;
/*0x014*/     ULONG32      PreviouslyGrantedAccess;
/*0x018*/     ULONG32      OriginalDesiredAccess;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     struct _SECURITY_SUBJECT_CONTEXT SubjectSecurityContext; // 4 elements, 0x20 bytes (sizeof)
/*0x040*/     VOID*        SecurityDescriptor;
/*0x048*/     VOID*        AuxData;
              union                                                    // 2 elements, 0x2C bytes (sizeof)
              {
/*0x050*/         struct _INITIAL_PRIVILEGE_SET InitialPrivilegeSet;   // 3 elements, 0x2C bytes (sizeof)
/*0x050*/         struct _PRIVILEGE_SET PrivilegeSet;                  // 3 elements, 0x14 bytes (sizeof)
              }Privileges;
/*0x07C*/     UINT8        AuditPrivileges;
/*0x07D*/     UINT8        _PADDING1_[0x3];
/*0x080*/     struct _UNICODE_STRING ObjectName;                       // 3 elements, 0x10 bytes (sizeof)
/*0x090*/     struct _UNICODE_STRING ObjectTypeName;                   // 3 elements, 0x10 bytes (sizeof)
          }ACCESS_STATE, *PACCESS_STATE;

          typedef struct _ACL           // 5 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT8        AclRevision;
/*0x001*/     UINT8        Sbz1;
/*0x002*/     UINT16       AclSize;
/*0x004*/     UINT16       AceCount;
/*0x006*/     UINT16       Sbz2;
          }ACL, *PACL;

          typedef struct _SE_AUDIT_PROCESS_CREATION_INFO      // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     struct _OBJECT_NAME_INFORMATION* ImageFileName;
          }SE_AUDIT_PROCESS_CREATION_INFO, *PSE_AUDIT_PROCESS_CREATION_INFO;

          typedef struct _SECURITY_CLIENT_CONTEXT              // 6 elements, 0x48 bytes (sizeof)
          {
/*0x000*/     struct _SECURITY_QUALITY_OF_SERVICE SecurityQos; // 4 elements, 0xC bytes (sizeof)
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     VOID*        ClientToken;
/*0x018*/     UINT8        DirectlyAccessClientToken;
/*0x019*/     UINT8        DirectAccessEffectiveOnly;
/*0x01A*/     UINT8        ServerIsRemote;
/*0x01B*/     UINT8        _PADDING1_[0x1];
/*0x01C*/     struct _TOKEN_CONTROL ClientTokenControl;        // 4 elements, 0x28 bytes (sizeof)
/*0x044*/     UINT8        _PADDING2_[0x4];
          }SECURITY_CLIENT_CONTEXT, *PSECURITY_CLIENT_CONTEXT;

          typedef struct _SECURITY_DESCRIPTOR // 7 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT8        Revision;
/*0x001*/     UINT8        Sbz1;
/*0x002*/     UINT16       Control;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     VOID*        Owner;
/*0x010*/     VOID*        Group;
/*0x018*/     struct _ACL* Sacl;
/*0x020*/     struct _ACL* Dacl;
          }SECURITY_DESCRIPTOR, *PSECURITY_DESCRIPTOR;

          typedef struct _SECURITY_DESCRIPTOR_RELATIVE // 7 elements, 0x14 bytes (sizeof)
          {
/*0x000*/     UINT8        Revision;
/*0x001*/     UINT8        Sbz1;
/*0x002*/     UINT16       Control;
/*0x004*/     ULONG32      Owner;
/*0x008*/     ULONG32      Group;
/*0x00C*/     ULONG32      Sacl;
/*0x010*/     ULONG32      Dacl;
          }SECURITY_DESCRIPTOR_RELATIVE, *PSECURITY_DESCRIPTOR_RELATIVE;

          typedef struct _SECURITY_QUALITY_OF_SERVICE                // 4 elements, 0xC bytes (sizeof)
          {
/*0x000*/     ULONG32      Length;
/*0x004*/     enum _SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
/*0x008*/     UINT8        ContextTrackingMode;
/*0x009*/     UINT8        EffectiveOnly;
/*0x00A*/     UINT8        _PADDING0_[0x2];
          }SECURITY_QUALITY_OF_SERVICE, *PSECURITY_QUALITY_OF_SERVICE;

          typedef struct _SECURITY_SUBJECT_CONTEXT                   // 4 elements, 0x20 bytes (sizeof)
          {
/*0x000*/     VOID*        ClientToken;
/*0x008*/     enum _SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     VOID*        PrimaryToken;
/*0x018*/     VOID*        ProcessAuditId;
          }SECURITY_SUBJECT_CONTEXT, *PSECURITY_SUBJECT_CONTEXT;

          typedef struct _SEP_AUDIT_POLICY               // 2 elements, 0x1E bytes (sizeof)
          {
/*0x000*/     struct _TOKEN_AUDIT_POLICY AdtTokenPolicy; // 1 elements, 0x1D bytes (sizeof)
/*0x01D*/     UINT8        PolicySetStatus;
          }SEP_AUDIT_POLICY, *PSEP_AUDIT_POLICY;

          typedef struct _SEP_LOGON_SESSION_REFERENCES             // 10 elements, 0x60 bytes (sizeof)
          {
/*0x000*/     struct _SEP_LOGON_SESSION_REFERENCES* Next;
/*0x008*/     struct _LUID LogonId;                                // 2 elements, 0x8 bytes (sizeof)
/*0x010*/     struct _LUID BuddyLogonId;                           // 2 elements, 0x8 bytes (sizeof)
/*0x018*/     ULONG32      ReferenceCount;
/*0x01C*/     ULONG32      Flags;
/*0x020*/     struct _DEVICE_MAP* pDeviceMap;
/*0x028*/     VOID*        Token;
/*0x030*/     struct _UNICODE_STRING AccountName;                  // 3 elements, 0x10 bytes (sizeof)
/*0x040*/     struct _UNICODE_STRING AuthorityName;                // 3 elements, 0x10 bytes (sizeof)
/*0x050*/     struct _SEP_LOWBOX_HANDLES_TABLE LowBoxHandlesTable; // 2 elements, 0x10 bytes (sizeof)
          }SEP_LOGON_SESSION_REFERENCES, *PSEP_LOGON_SESSION_REFERENCES;

          typedef struct _SEP_LOWBOX_HANDLES_ENTRY            // 5 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _RTL_DYNAMIC_HASH_TABLE_ENTRY HashEntry; // 2 elements, 0x18 bytes (sizeof)
/*0x018*/     ULONG32      ReferenceCount;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     VOID*        PackageSid;
/*0x028*/     ULONG32      HandleCount;
/*0x02C*/     UINT8        _PADDING1_[0x4];
/*0x030*/     VOID**       Handles;
          }SEP_LOWBOX_HANDLES_ENTRY, *PSEP_LOWBOX_HANDLES_ENTRY;

          typedef struct _SEP_LOWBOX_HANDLES_TABLE       // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _EX_PUSH_LOCK Lock;                 // 7 elements, 0x8 bytes (sizeof)
/*0x008*/     struct _RTL_DYNAMIC_HASH_TABLE* HashTable;
          }SEP_LOWBOX_HANDLES_TABLE, *PSEP_LOWBOX_HANDLES_TABLE;

          typedef struct _SEP_LOWBOX_NUMBER_ENTRY             // 5 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     struct _RTL_DYNAMIC_HASH_TABLE_ENTRY HashEntry; // 2 elements, 0x18 bytes (sizeof)
/*0x018*/     ULONG32      ReferenceCount;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     VOID*        PackageSid;
/*0x028*/     ULONG32      LowboxNumber;
/*0x02C*/     UINT8        _PADDING1_[0x4];
/*0x030*/     VOID*        AtomTable;
          }SEP_LOWBOX_NUMBER_ENTRY, *PSEP_LOWBOX_NUMBER_ENTRY;

          typedef struct _SEP_LOWBOX_NUMBER_MAPPING      // 4 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _EX_PUSH_LOCK Lock;                 // 7 elements, 0x8 bytes (sizeof)
/*0x008*/     struct _RTL_BITMAP Bitmap;                 // 2 elements, 0x10 bytes (sizeof)
/*0x018*/     struct _RTL_DYNAMIC_HASH_TABLE* HashTable;
/*0x020*/     UINT8        Active;
/*0x021*/     UINT8        _PADDING0_[0x7];
          }SEP_LOWBOX_NUMBER_MAPPING, *PSEP_LOWBOX_NUMBER_MAPPING;

          typedef struct _SEP_TOKEN_PRIVILEGES // 3 elements, 0x18 bytes (sizeof)
          {
/*0x000*/     UINT64       Present;
/*0x008*/     UINT64       Enabled;
/*0x010*/     UINT64       EnabledByDefault;
          }SEP_TOKEN_PRIVILEGES, *PSEP_TOKEN_PRIVILEGES;

          typedef struct _SID                                       // 4 elements, 0xC bytes (sizeof)
          {
/*0x000*/     UINT8        Revision;
/*0x001*/     UINT8        SubAuthorityCount;
/*0x002*/     struct _SID_IDENTIFIER_AUTHORITY IdentifierAuthority; // 1 elements, 0x6 bytes (sizeof)
/*0x008*/     ULONG32      SubAuthority[1];
          }SID, *PSID;

          typedef struct _SID_AND_ATTRIBUTES // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     VOID*        Sid;
/*0x008*/     ULONG32      Attributes;
/*0x00C*/     UINT8        _PADDING0_[0x4];
          }SID_AND_ATTRIBUTES, *PSID_AND_ATTRIBUTES;

          typedef struct _SID_AND_ATTRIBUTES_HASH  // 3 elements, 0x110 bytes (sizeof)
          {
/*0x000*/     ULONG32      SidCount;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _SID_AND_ATTRIBUTES* SidAttr;
/*0x010*/     UINT64       Hash[32];
          }SID_AND_ATTRIBUTES_HASH, *PSID_AND_ATTRIBUTES_HASH;

          typedef struct _SID_IDENTIFIER_AUTHORITY // 1 elements, 0x6 bytes (sizeof)
          {
/*0x000*/     UINT8        Value[6];
          }SID_IDENTIFIER_AUTHORITY, *PSID_IDENTIFIER_AUTHORITY;

          typedef struct _TOKEN                                                        // 40 elements, 0x458 bytes (sizeof)
          {
/*0x000*/     struct _TOKEN_SOURCE TokenSource;                                        // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     struct _LUID TokenId;                                                    // 2 elements, 0x8 bytes (sizeof)
/*0x018*/     struct _LUID AuthenticationId;                                           // 2 elements, 0x8 bytes (sizeof)
/*0x020*/     struct _LUID ParentTokenId;                                              // 2 elements, 0x8 bytes (sizeof)
/*0x028*/     union _LARGE_INTEGER ExpirationTime;                                     // 4 elements, 0x8 bytes (sizeof)
/*0x030*/     struct _ERESOURCE* TokenLock;
/*0x038*/     struct _LUID ModifiedId;                                                 // 2 elements, 0x8 bytes (sizeof)
/*0x040*/     struct _SEP_TOKEN_PRIVILEGES Privileges;                                 // 3 elements, 0x18 bytes (sizeof)
/*0x058*/     struct _SEP_AUDIT_POLICY AuditPolicy;                                    // 2 elements, 0x1E bytes (sizeof)
/*0x076*/     UINT8        _PADDING0_[0x2];
/*0x078*/     ULONG32      SessionId;
/*0x07C*/     ULONG32      UserAndGroupCount;
/*0x080*/     ULONG32      RestrictedSidCount;
/*0x084*/     ULONG32      VariableLength;
/*0x088*/     ULONG32      DynamicCharged;
/*0x08C*/     ULONG32      DynamicAvailable;
/*0x090*/     ULONG32      DefaultOwnerIndex;
/*0x094*/     UINT8        _PADDING1_[0x4];
/*0x098*/     struct _SID_AND_ATTRIBUTES* UserAndGroups;
/*0x0A0*/     struct _SID_AND_ATTRIBUTES* RestrictedSids;
/*0x0A8*/     VOID*        PrimaryGroup;
/*0x0B0*/     ULONG32*     DynamicPart;
/*0x0B8*/     struct _ACL* DefaultDacl;
/*0x0C0*/     enum _TOKEN_TYPE TokenType;
/*0x0C4*/     enum _SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
/*0x0C8*/     ULONG32      TokenFlags;
/*0x0CC*/     UINT8        TokenInUse;
/*0x0CD*/     UINT8        _PADDING2_[0x3];
/*0x0D0*/     ULONG32      IntegrityLevelIndex;
/*0x0D4*/     ULONG32      MandatoryPolicy;
/*0x0D8*/     struct _SEP_LOGON_SESSION_REFERENCES* LogonSession;
/*0x0E0*/     struct _LUID OriginatingLogonSession;                                    // 2 elements, 0x8 bytes (sizeof)
/*0x0E8*/     struct _SID_AND_ATTRIBUTES_HASH SidHash;                                 // 3 elements, 0x110 bytes (sizeof)
/*0x1F8*/     struct _SID_AND_ATTRIBUTES_HASH RestrictedSidHash;                       // 3 elements, 0x110 bytes (sizeof)
/*0x308*/     struct _AUTHZBASEP_SECURITY_ATTRIBUTES_INFORMATION* pSecurityAttributes;
/*0x310*/     VOID*        Package;
/*0x318*/     struct _SID_AND_ATTRIBUTES* Capabilities;
/*0x320*/     ULONG32      CapabilityCount;
/*0x324*/     UINT8        _PADDING3_[0x4];
/*0x328*/     struct _SID_AND_ATTRIBUTES_HASH CapabilitiesHash;                        // 3 elements, 0x110 bytes (sizeof)
/*0x438*/     struct _SEP_LOWBOX_NUMBER_ENTRY* LowboxNumberEntry;
/*0x440*/     struct _SEP_LOWBOX_HANDLES_ENTRY* LowboxHandlesEntry;
/*0x448*/     struct _AUTHZBASEP_CLAIM_ATTRIBUTES_COLLECTION* pClaimAttributes;
/*0x450*/     UINT64       VariablePart;
          }TOKEN, *PTOKEN;

          typedef struct _TOKEN_AUDIT_POLICY  // 1 elements, 0x1D bytes (sizeof)
          {
/*0x000*/     UINT8        PerUserPolicy[29];
          }TOKEN_AUDIT_POLICY, *PTOKEN_AUDIT_POLICY;

          typedef struct _TOKEN_CONTROL         // 4 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     struct _LUID TokenId;             // 2 elements, 0x8 bytes (sizeof)
/*0x008*/     struct _LUID AuthenticationId;    // 2 elements, 0x8 bytes (sizeof)
/*0x010*/     struct _LUID ModifiedId;          // 2 elements, 0x8 bytes (sizeof)
/*0x018*/     struct _TOKEN_SOURCE TokenSource; // 2 elements, 0x10 bytes (sizeof)
          }TOKEN_CONTROL, *PTOKEN_CONTROL;

          typedef struct _TOKEN_SOURCE       // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     CHAR         SourceName[8];
/*0x008*/     struct _LUID SourceIdentifier; // 2 elements, 0x8 bytes (sizeof)
          }TOKEN_SOURCE, *PTOKEN_SOURCE;

typedef enum _POLICY_AUDIT_EVENT_TYPE  // 9 elements, 0x4 bytes
{
    AuditCategorySystem                 = 0 /*0x0*/,
    AuditCategoryLogon                  = 1 /*0x1*/,
    AuditCategoryObjectAccess           = 2 /*0x2*/,
    AuditCategoryPrivilegeUse           = 3 /*0x3*/,
    AuditCategoryDetailedTracking       = 4 /*0x4*/,
    AuditCategoryPolicyChange           = 5 /*0x5*/,
    AuditCategoryAccountManagement      = 6 /*0x6*/,
    AuditCategoryDirectoryServiceAccess = 7 /*0x7*/,
    AuditCategoryAccountLogon           = 8 /*0x8*/
}POLICY_AUDIT_EVENT_TYPE, *PPOLICY_AUDIT_EVENT_TYPE;

typedef enum _SE_SIGNING_LEVEL  // 7 elements, 0x4 bytes
{
    SE_SIGNING_LEVEL_UNCHECKED         = 0 /*0x0*/,
    SE_SIGNING_LEVEL_PROTECTED_PROCESS = 1 /*0x1*/,
    SE_SIGNING_LEVEL_UNSIGNED          = 2 /*0x2*/,
    SE_SIGNING_LEVEL_AUTHENTICODE      = 4 /*0x4*/,
    SE_SIGNING_LEVEL_DRM_PROTECTED     = 5 /*0x5*/,
    SE_SIGNING_LEVEL_WINDOWS           = 6 /*0x6*/,
    SE_SIGNING_LEVEL_WINDOWS_PROTECTED = 7 /*0x7*/
}SE_SIGNING_LEVEL, *PSE_SIGNING_LEVEL;

typedef enum _SECURITY_IMPERSONATION_LEVEL  // 4 elements, 0x4 bytes
{
    SecurityAnonymous      = 0 /*0x0*/,
    SecurityIdentification = 1 /*0x1*/,
    SecurityImpersonation  = 2 /*0x2*/,
    SecurityDelegation     = 3 /*0x3*/
}SECURITY_IMPERSONATION_LEVEL, *PSECURITY_IMPERSONATION_LEVEL;

typedef enum _SECURITY_OPERATION_CODE  // 4 elements, 0x4 bytes
{
    SetSecurityDescriptor    = 0 /*0x0*/,
    QuerySecurityDescriptor  = 1 /*0x1*/,
    DeleteSecurityDescriptor = 2 /*0x2*/,
    AssignSecurityDescriptor = 3 /*0x3*/
}SECURITY_OPERATION_CODE, *PSECURITY_OPERATION_CODE;

typedef enum _TOKEN_INFORMATION_CLASS  // 41 elements, 0x4 bytes
{
    TokenUser                            = 1 /*0x1*/,
    TokenGroups                          = 2 /*0x2*/,
    TokenPrivileges                      = 3 /*0x3*/,
    TokenOwner                           = 4 /*0x4*/,
    TokenPrimaryGroup                    = 5 /*0x5*/,
    TokenDefaultDacl                     = 6 /*0x6*/,
    TokenSource                          = 7 /*0x7*/,
    TokenType                            = 8 /*0x8*/,
    TokenImpersonationLevel              = 9 /*0x9*/,
    TokenStatistics                      = 10 /*0xA*/,
    TokenRestrictedSids                  = 11 /*0xB*/,
    TokenSessionId                       = 12 /*0xC*/,
    TokenGroupsAndPrivileges             = 13 /*0xD*/,
    TokenSessionReference                = 14 /*0xE*/,
    TokenSandBoxInert                    = 15 /*0xF*/,
    TokenAuditPolicy                     = 16 /*0x10*/,
    TokenOrigin                          = 17 /*0x11*/,
    TokenElevationType                   = 18 /*0x12*/,
    TokenLinkedToken                     = 19 /*0x13*/,
    TokenElevation                       = 20 /*0x14*/,
    TokenHasRestrictions                 = 21 /*0x15*/,
    TokenAccessInformation               = 22 /*0x16*/,
    TokenVirtualizationAllowed           = 23 /*0x17*/,
    TokenVirtualizationEnabled           = 24 /*0x18*/,
    TokenIntegrityLevel                  = 25 /*0x19*/,
    TokenUIAccess                        = 26 /*0x1A*/,
    TokenMandatoryPolicy                 = 27 /*0x1B*/,
    TokenLogonSid                        = 28 /*0x1C*/,
    TokenIsAppContainer                  = 29 /*0x1D*/,
    TokenCapabilities                    = 30 /*0x1E*/,
    TokenAppContainerSid                 = 31 /*0x1F*/,
    TokenAppContainerNumber              = 32 /*0x20*/,
    TokenUserClaimAttributes             = 33 /*0x21*/,
    TokenDeviceClaimAttributes           = 34 /*0x22*/,
    TokenRestrictedUserClaimAttributes   = 35 /*0x23*/,
    TokenRestrictedDeviceClaimAttributes = 36 /*0x24*/,
    TokenDeviceGroups                    = 37 /*0x25*/,
    TokenRestrictedDeviceGroups          = 38 /*0x26*/,
    TokenSecurityAttributes              = 39 /*0x27*/,
    TokenIsRestricted                    = 40 /*0x28*/,
    MaxTokenInfoClass                    = 41 /*0x29*/
}TOKEN_INFORMATION_CLASS, *PTOKEN_INFORMATION_CLASS;

typedef enum _TOKEN_TYPE  // 2 elements, 0x4 bytes
{
    TokenPrimary       = 1 /*0x1*/,
    TokenImpersonation = 2 /*0x2*/
}TOKEN_TYPE, *PTOKEN_TYPE;

          typedef struct _AUTHZBASEP_CLAIM_ATTRIBUTES_COLLECTION                                       // 10 elements, 0x260 bytes (sizeof)
          {
/*0x000*/     ULONG32      DeviceGroupsCount;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _SID_AND_ATTRIBUTES* pDeviceGroups;
/*0x010*/     ULONG32      RestrictedDeviceGroupsCount;
/*0x014*/     UINT8        _PADDING1_[0x4];
/*0x018*/     struct _SID_AND_ATTRIBUTES* pRestrictedDeviceGroups;
/*0x020*/     struct _SID_AND_ATTRIBUTES_HASH DeviceGroupsHash;                                        // 3 elements, 0x110 bytes (sizeof)
/*0x130*/     struct _SID_AND_ATTRIBUTES_HASH RestrictedDeviceGroupsHash;                              // 3 elements, 0x110 bytes (sizeof)
/*0x240*/     struct _AUTHZBASEP_SECURITY_ATTRIBUTES_INFORMATION* pUserSecurityAttributes;
/*0x248*/     struct _AUTHZBASEP_SECURITY_ATTRIBUTES_INFORMATION* pDeviceSecurityAttributes;
/*0x250*/     struct _AUTHZBASEP_SECURITY_ATTRIBUTES_INFORMATION* pRestrictedUserSecurityAttributes;
/*0x258*/     struct _AUTHZBASEP_SECURITY_ATTRIBUTES_INFORMATION* pRestrictedDeviceSecurityAttributes;
          }AUTHZBASEP_CLAIM_ATTRIBUTES_COLLECTION, *PAUTHZBASEP_CLAIM_ATTRIBUTES_COLLECTION;

          typedef struct _AUTHZBASEP_SECURITY_ATTRIBUTES_INFORMATION // 4 elements, 0x30 bytes (sizeof)
          {
/*0x000*/     ULONG32      SecurityAttributeCount;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     struct _LIST_ENTRY SecurityAttributesList;             // 2 elements, 0x10 bytes (sizeof)
/*0x018*/     ULONG32      WorkingSecurityAttributeCount;
/*0x01C*/     UINT8        _PADDING1_[0x4];
/*0x020*/     struct _LIST_ENTRY WorkingSecurityAttributesList;      // 2 elements, 0x10 bytes (sizeof)
          }AUTHZBASEP_SECURITY_ATTRIBUTES_INFORMATION, *PAUTHZBASEP_SECURITY_ATTRIBUTES_INFORMATION;

          typedef struct _INITIAL_PRIVILEGE_SET         // 3 elements, 0x2C bytes (sizeof)
          {
/*0x000*/     ULONG32      PrivilegeCount;
/*0x004*/     ULONG32      Control;
/*0x008*/     struct _LUID_AND_ATTRIBUTES Privilege[3];
          }INITIAL_PRIVILEGE_SET, *PINITIAL_PRIVILEGE_SET;

          typedef struct _LUID       // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      LowPart;
/*0x004*/     LONG32       HighPart;
          }LUID, *PLUID;

          typedef struct _PRIVILEGE_SET                 // 3 elements, 0x14 bytes (sizeof)
          {
/*0x000*/     ULONG32      PrivilegeCount;
/*0x004*/     ULONG32      Control;
/*0x008*/     struct _LUID_AND_ATTRIBUTES Privilege[1];
          }PRIVILEGE_SET, *PPRIVILEGE_SET;

         typedef struct _AUX_ACCESS_DATA                                                                              // 12 elements, 0xE0 bytes (sizeof)
          {
/*0x000*/     struct _PRIVILEGE_SET* PrivilegesUsed;
/*0x008*/     struct _GENERIC_MAPPING GenericMapping;                                                                  // 4 elements, 0x10 bytes (sizeof)
/*0x018*/     ULONG32      AccessesToAudit;
/*0x01C*/     ULONG32      MaximumAuditMask;
/*0x020*/     struct _GUID TransactionId;                                                                              // 4 elements, 0x10 bytes (sizeof)
/*0x030*/     VOID*        NewSecurityDescriptor;
/*0x038*/     VOID*        ExistingSecurityDescriptor;
/*0x040*/     VOID*        ParentSecurityDescriptor;
/*0x048*/     FUNCT_00AE_00AD_CleanupGroupCancelCallback_DeRefSecurityDescriptor_PostRoutine* DeRefSecurityDescriptor;
/*0x050*/     VOID*        SDLock;
/*0x058*/     struct _ACCESS_REASONS AccessReasons;                                                                    // 1 elements, 0x80 bytes (sizeof)
/*0x0D8*/     UINT8        GenerateStagingEvents;
/*0x0D9*/     UINT8        _PADDING0_[0x7];
          }AUX_ACCESS_DATA, *PAUX_ACCESS_DATA;

