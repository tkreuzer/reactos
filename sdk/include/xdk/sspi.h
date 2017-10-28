

#pragma once
#define __SSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ISSP_LEVEL 32

#if defined(SECURITY_KERNEL)
#undef ISSP_MODE
#define ISSP_MODE 0
#elif defined(SECURITY_WIN32) || defined(SECURITY_MAC)
#define ISSP_MODE 1
#else
#error Need to define SECURITY_KERNEL, SECURITY_WIN32 or SECURITY_MAC!
#endif

#ifdef MIDL_PASS
#define MIDL_PROP(x) x
#else
#define MIDL_PROP(x)
#endif

#define SEC_TEXT TEXT
#define SEC_FAR
#define __SEC_FAR SEC_FAR
#define SEC_ENTRY __stdcall

#if defined(_NO_KSECDD_IMPORT_)
#define KSECDDDECLSPEC
#else
#define KSECDDDECLSPEC __declspec(dllimport)
#endif

#define SECQOP_WRAP_NO_ENCRYPT 0x80000001
#define SECQOP_WRAP_OOB_DATA   0x40000000

#define SECURITY_ENTRYPOINTA SEC_TEXT("InitSecurityInterfaceA")
#define SECURITY_ENTRYPOINTW SEC_TEXT("InitSecurityInterfaceW")
#define SECURITY_ENTRYPOINT_ANSIA "InitSecurityInterfaceA"
#define SECURITY_ENTRYPOINT_ANSIW "InitSecurityInterfaceW"
#define SECURITY_ENTRYPOINT16 "INITSECURITYINTERFACEA"

#ifdef SECURITY_WIN32
#ifdef UNICODE
#define SECURITY_ENTRYPOINT SECURITY_ENTRYPOINTW
#define SECURITY_ENTRYPOINT_ANSI SECURITY_ENTRYPOINT_ANSIW
#else // UNICODE
#define SECURITY_ENTRYPOINT SECURITY_ENTRYPOINTA
#define SECURITY_ENTRYPOINT_ANSI SECURITY_ENTRYPOINT_ANSIA
#endif // UNICODE
#else // SECURITY_WIN32
#define SECURITY_ENTRYPOINT SECURITY_ENTRYPOINT16
#define SECURITY_ENTRYPOINT_ANSI SECURITY_ENTRYPOINT16
#endif // SECURITY_WIN32

#define SECURITY_SUPPORT_PROVIDER_INTERFACE_VERSION   1
#define SECURITY_SUPPORT_PROVIDER_INTERFACE_VERSION_2 2
#define SECURITY_SUPPORT_PROVIDER_INTERFACE_VERSION_3 3
#define SECURITY_SUPPORT_PROVIDER_INTERFACE_VERSION_4 4
#define SECURITY_SUPPORT_PROVIDER_INTERFACE_VERSION_5 5

#define SECURITY_NATIVE_DREP  0x00000010
#define SECURITY_NETWORK_DREP 0x00000000

#define SECPKG_ID_NONE 0xFFFF

#define SECPKG_CRED_ATTR_NAMES                1
#define SECPKG_CRED_ATTR_SSI_PROVIDER         2
#define SECPKG_CRED_ATTR_KDC_PROXY_SETTINGS   3
#define SECPKG_CRED_ATTR_CERT                 4
#define SECPKG_CRED_ATTR_PAC_BYPASS           5

#define SECPKG_ATTR_SIZES                     0
#define SECPKG_ATTR_NAMES                     1
#define SECPKG_ATTR_LIFESPAN                  2
#define SECPKG_ATTR_DCE_INFO                  3
#define SECPKG_ATTR_STREAM_SIZES              4
#define SECPKG_ATTR_KEY_INFO                  5
#define SECPKG_ATTR_AUTHORITY                 6
#define SECPKG_ATTR_PROTO_INFO                7
#define SECPKG_ATTR_PASSWORD_EXPIRY           8
#define SECPKG_ATTR_SESSION_KEY               9
#define SECPKG_ATTR_PACKAGE_INFO             10
#define SECPKG_ATTR_USER_FLAGS               11
#define SECPKG_ATTR_NEGOTIATION_INFO         12
#define SECPKG_ATTR_NATIVE_NAMES             13
#define SECPKG_ATTR_FLAGS                    14
// These attributes exist only in Win XP and greater
#define SECPKG_ATTR_USE_VALIDATED            15
#define SECPKG_ATTR_CREDENTIAL_NAME          16
#define SECPKG_ATTR_TARGET_INFORMATION       17
#define SECPKG_ATTR_ACCESS_TOKEN             18
// These attributes exist only in Win2K3 and greater
#define SECPKG_ATTR_TARGET                   19
#define SECPKG_ATTR_AUTHENTICATION_ID        20
// These attributes exist only in Win2K3SP1 and greater
#define SECPKG_ATTR_LOGOFF_TIME              21
#define SECPKG_ATTR_NEGO_KEYS                22
#define SECPKG_ATTR_PROMPTING_NEEDED         24
#define SECPKG_ATTR_UNIQUE_BINDINGS          25
#define SECPKG_ATTR_ENDPOINT_BINDINGS        26
#define SECPKG_ATTR_CLIENT_SPECIFIED_TARGET  27
#define SECPKG_ATTR_LAST_CLIENT_TOKEN_STATUS 30
#define SECPKG_ATTR_NEGO_PKG_INFO            31
#define SECPKG_ATTR_NEGO_STATUS              32
#define SECPKG_ATTR_CONTEXT_DELETED          33

#define SECPKG_FLAG_INTEGRITY                    0x00000001
#define SECPKG_FLAG_PRIVACY                      0x00000002
#define SECPKG_FLAG_TOKEN_ONLY                   0x00000004
#define SECPKG_FLAG_DATAGRAM                     0x00000008
#define SECPKG_FLAG_CONNECTION                   0x00000010
#define SECPKG_FLAG_MULTI_REQUIRED               0x00000020
#define SECPKG_FLAG_CLIENT_ONLY                  0x00000040
#define SECPKG_FLAG_EXTENDED_ERROR               0x00000080
#define SECPKG_FLAG_IMPERSONATION                0x00000100
#define SECPKG_FLAG_ACCEPT_WIN32_NAME            0x00000200
#define SECPKG_FLAG_STREAM                       0x00000400
#define SECPKG_FLAG_NEGOTIABLE                   0x00000800
#define SECPKG_FLAG_GSS_COMPATIBLE               0x00001000
#define SECPKG_FLAG_LOGON                        0x00002000
#define SECPKG_FLAG_ASCII_BUFFERS                0x00004000
#define SECPKG_FLAG_FRAGMENT                     0x00008000
#define SECPKG_FLAG_MUTUAL_AUTH                  0x00010000
#define SECPKG_FLAG_DELEGATION                   0x00020000
#define SECPKG_FLAG_READONLY_WITH_CHECKSUM       0x00040000
#define SECPKG_FLAG_RESTRICTED_TOKENS            0x00080000
#define SECPKG_FLAG_NEGO_EXTENDER                0x00100000
#define SECPKG_FLAG_NEGOTIABLE2                  0x00200000
#define SECPKG_FLAG_APPCONTAINER_PASSTHROUGH     0x00400000
#define SECPKG_FLAG_APPCONTAINER_CHECKS          0x00800000
#define SECPKG_FLAG_CREDENTIAL_ISOLATION_ENABLED 0x01000000

#define SECPKG_CRED_INBOUND                 0x00000001
#define SECPKG_CRED_OUTBOUND                0x00000002
#define SECPKG_CRED_BOTH                    0x00000003
#define SECPKG_CRED_DEFAULT                 0x00000004
#define SECPKG_CRED_RESERVED                0xF0000000
#define SECPKG_CRED_AUTOLOGON_RESTRICTED    0x00000010
#define SECPKG_CRED_PROCESS_POLICY_ONLY     0x00000020

#define SECPKG_CONTEXT_EXPORT_RESET_NEW     0x00000001
#define SECPKG_CONTEXT_EXPORT_DELETE_OLD    0x00000002
#define SECPKG_CONTEXT_EXPORT_TO_KERNEL     0x00000004

#define SECPKG_ATTR_SUBJECT_SECURITY_ATTRIBUTES 128

#define SECPKG_ATTR_NEGO_INFO_FLAG_NO_KERBEROS 0x1
#define SECPKG_ATTR_NEGO_INFO_FLAG_NO_NTLM     0x2

#define SECPKG_CALLFLAGS_APPCONTAINER                   0x00000001
#define SECPKG_CALLFLAGS_APPCONTAINER_AUTHCAPABLE       0x00000002
#define SECPKG_CALLFLAGS_FORCE_SUPPLIED                 0x00000004
#define SECPKG_CALLFLAGS_APPCONTAINER_UPNCAPABLE        0x00000008

#define SECPKG_ATTR_APPLICATION_PROTOCOL 35
#define SECPKG_ATTR_NEGOTIATED_TLS_EXTENSIONS 36
#define SECPKG_ATTR_IS_LOOPBACK 37

#define SECPKG_ATTR_DTLS_MTU        34
#define SECPKG_ATTR_DATAGRAM_SIZES SECPKG_ATTR_STREAM_SIZES

#define SECPKG_NEGOTIATION_COMPLETE             0
#define SECPKG_NEGOTIATION_OPTIMISTIC           1
#define SECPKG_NEGOTIATION_IN_PROGRESS          2
#define SECPKG_NEGOTIATION_DIRECT               3
#define SECPKG_NEGOTIATION_TRY_MULTICRED        4

typedef struct _SecPkgContext_NativeNamesA
{
    SEC_CHAR *sClientName;
    SEC_CHAR *sServerName;
} SecPkgContext_NativeNamesA, * PSecPkgContext_NativeNamesA;

typedef struct _SecPkgContext_NativeNamesW
{
    SEC_WCHAR *sClientName;
    SEC_WCHAR *sServerName;
} SecPkgContext_NativeNamesW, * PSecPkgContext_NativeNamesW;

#ifdef UNICODE
#define SecPkgContext_NativeNames SecPkgContext_NativeNamesW
#define PSecPkgContext_NativeNames PSecPkgContext_NativeNamesW
#else
#define SecPkgContext_NativeNames SecPkgContext_NativeNamesA
#define PSecPkgContext_NativeNames PSecPkgContext_NativeNamesA
#endif // !UNICODE

#define SECBUFFER_VERSION 0

#define SECBUFFER_EMPTY                 0
#define SECBUFFER_DATA                  1
#define SECBUFFER_TOKEN                 2
#define SECBUFFER_PKG_PARAMS            3
#define SECBUFFER_MISSING               4
#define SECBUFFER_EXTRA                 5
#define SECBUFFER_STREAM_TRAILER        6
#define SECBUFFER_STREAM_HEADER         7
#define SECBUFFER_NEGOTIATION_INFO      8
#define SECBUFFER_PADDING               9
#define SECBUFFER_STREAM               10
#define SECBUFFER_MECHLIST             11
#define SECBUFFER_MECHLIST_SIGNATURE   12
#define SECBUFFER_TARGET               13
#define SECBUFFER_CHANNEL_BINDINGS     14
#define SECBUFFER_CHANGE_PASS_RESPONSE 15
#define SECBUFFER_TARGET_HOST          16
#define SECBUFFER_ALERT                17
#define SECBUFFER_APPLICATION_PROTOCOLS 18
#define SECBUFFER_SRTP_PROTECTION_PROFILES 19
#define SECBUFFER_SRTP_MASTER_KEY_IDENTIFIER 20
#define SECBUFFER_TOKEN_BINDING 21
#define SECBUFFER_PRESHARED_KEY 22
#define SECBUFFER_PRESHARED_KEY_IDENTITY 23
#define SECBUFFER_DTLS_MTU 24

#define SECBUFFER_ATTRMASK                0xF0000000
#define SECBUFFER_READONLY                0x80000000
#define SECBUFFER_READONLY_WITH_CHECKSUM  0x10000000
#define SECBUFFER_RESERVED                0x60000000

#define ISC_REQ_DELEGATE                 0x00000001
#define ISC_REQ_MUTUAL_AUTH              0x00000002
#define ISC_REQ_REPLAY_DETECT            0x00000004
#define ISC_REQ_SEQUENCE_DETECT          0x00000008
#define ISC_REQ_CONFIDENTIALITY          0x00000010
#define ISC_REQ_USE_SESSION_KEY          0x00000020
#define ISC_REQ_PROMPT_FOR_CREDS         0x00000040
#define ISC_REQ_USE_SUPPLIED_CREDS       0x00000080
#define ISC_REQ_ALLOCATE_MEMORY          0x00000100
#define ISC_REQ_USE_DCE_STYLE            0x00000200
#define ISC_REQ_DATAGRAM                 0x00000400
#define ISC_REQ_CONNECTION               0x00000800
#define ISC_REQ_CALL_LEVEL               0x00001000
#define ISC_REQ_FRAGMENT_SUPPLIED        0x00002000
#define ISC_REQ_EXTENDED_ERROR           0x00004000
#define ISC_REQ_STREAM                   0x00008000
#define ISC_REQ_INTEGRITY                0x00010000
#define ISC_REQ_IDENTIFY                 0x00020000
#define ISC_REQ_NULL_SESSION             0x00040000
#define ISC_REQ_MANUAL_CRED_VALIDATION   0x00080000
#define ISC_REQ_RESERVED1                0x00100000
#define ISC_REQ_FRAGMENT_TO_FIT          0x00200000
#define ISC_REQ_FORWARD_CREDENTIALS      0x00400000
#define ISC_REQ_NO_INTEGRITY             0x00800000
#define ISC_REQ_USE_HTTP_STYLE           0x01000000
#define ISC_REQ_UNVERIFIED_TARGET_NAME   0x20000000
#define ISC_REQ_CONFIDENTIALITY_ONLY     0x40000000

#define ISC_RET_DELEGATE                 0x00000001
#define ISC_RET_MUTUAL_AUTH              0x00000002
#define ISC_RET_REPLAY_DETECT            0x00000004
#define ISC_RET_SEQUENCE_DETECT          0x00000008
#define ISC_RET_CONFIDENTIALITY          0x00000010
#define ISC_RET_USE_SESSION_KEY          0x00000020
#define ISC_RET_USED_COLLECTED_CREDS     0x00000040
#define ISC_RET_USED_SUPPLIED_CREDS      0x00000080
#define ISC_RET_ALLOCATED_MEMORY         0x00000100
#define ISC_RET_USED_DCE_STYLE           0x00000200
#define ISC_RET_DATAGRAM                 0x00000400
#define ISC_RET_CONNECTION               0x00000800
#define ISC_RET_INTERMEDIATE_RETURN      0x00001000
#define ISC_RET_CALL_LEVEL               0x00002000
#define ISC_RET_EXTENDED_ERROR           0x00004000
#define ISC_RET_STREAM                   0x00008000
#define ISC_RET_INTEGRITY                0x00010000
#define ISC_RET_IDENTIFY                 0x00020000
#define ISC_RET_NULL_SESSION             0x00040000
#define ISC_RET_MANUAL_CRED_VALIDATION   0x00080000
#define ISC_RET_RESERVED1                0x00100000
#define ISC_RET_FRAGMENT_ONLY            0x00200000
#define ISC_RET_FORWARD_CREDENTIALS      0x00400000
#define ISC_RET_USED_HTTP_STYLE          0x01000000
#define ISC_RET_NO_ADDITIONAL_TOKEN      0x02000000
#define ISC_RET_REAUTHENTICATION         0x08000000
#define ISC_RET_CONFIDENTIALITY_ONLY     0x40000000

#define ASC_REQ_DELEGATE                 0x00000001
#define ASC_REQ_MUTUAL_AUTH              0x00000002
#define ASC_REQ_REPLAY_DETECT            0x00000004
#define ASC_REQ_SEQUENCE_DETECT          0x00000008
#define ASC_REQ_CONFIDENTIALITY          0x00000010
#define ASC_REQ_USE_SESSION_KEY          0x00000020
#define ASC_REQ_SESSION_TICKET           0x00000040
#define ASC_REQ_ALLOCATE_MEMORY          0x00000100
#define ASC_REQ_USE_DCE_STYLE            0x00000200
#define ASC_REQ_DATAGRAM                 0x00000400
#define ASC_REQ_CONNECTION               0x00000800
#define ASC_REQ_CALL_LEVEL               0x00001000
#define ASC_REQ_FRAGMENT_SUPPLIED        0x00002000
#define ASC_REQ_EXTENDED_ERROR           0x00008000
#define ASC_REQ_STREAM                   0x00010000
#define ASC_REQ_INTEGRITY                0x00020000
#define ASC_REQ_LICENSING                0x00040000
#define ASC_REQ_IDENTIFY                 0x00080000
#define ASC_REQ_ALLOW_NULL_SESSION       0x00100000
#define ASC_REQ_ALLOW_NON_USER_LOGONS    0x00200000
#define ASC_REQ_ALLOW_CONTEXT_REPLAY     0x00400000
#define ASC_REQ_FRAGMENT_TO_FIT          0x00800000
#define ASC_REQ_NO_TOKEN                 0x01000000
#define ASC_REQ_PROXY_BINDINGS           0x04000000
//#define SSP_RET_REAUTHENTICATION         0x08000000 // internal
#define ASC_REQ_ALLOW_MISSING_BINDINGS   0x10000000

#define ASC_RET_DELEGATE                 0x00000001
#define ASC_RET_MUTUAL_AUTH              0x00000002
#define ASC_RET_REPLAY_DETECT            0x00000004
#define ASC_RET_SEQUENCE_DETECT          0x00000008
#define ASC_RET_CONFIDENTIALITY          0x00000010
#define ASC_RET_USE_SESSION_KEY          0x00000020
#define ASC_RET_SESSION_TICKET           0x00000040
#define ASC_RET_ALLOCATED_MEMORY         0x00000100
#define ASC_RET_USED_DCE_STYLE           0x00000200
#define ASC_RET_DATAGRAM                 0x00000400
#define ASC_RET_CONNECTION               0x00000800
#define ASC_RET_CALL_LEVEL               0x00002000
#define ASC_RET_THIRD_LEG_FAILED         0x00004000
#define ASC_RET_EXTENDED_ERROR           0x00008000
#define ASC_RET_STREAM                   0x00010000
#define ASC_RET_INTEGRITY                0x00020000
#define ASC_RET_LICENSING                0x00040000
#define ASC_RET_IDENTIFY                 0x00080000
#define ASC_RET_NULL_SESSION             0x00100000
#define ASC_RET_ALLOW_NON_USER_LOGONS    0x00200000
#define ASC_RET_ALLOW_CONTEXT_REPLAY     0x00400000 // deprecated
#define ASC_RET_FRAGMENT_ONLY            0x00800000
#define ASC_RET_NO_TOKEN                 0x01000000
#define ASC_RET_NO_ADDITIONAL_TOKEN      0x02000000 // internal
#define ASC_RET_NO_PROXY_BINDINGS        0x04000000
//#define SSP_RET_REAUTHENTICATION         0x08000000 // internal
#define ASC_RET_MISSING_BINDINGS         0x10000000

#define SEC_DELETED_HANDLE ((ULONG_PTR)(-2))

#define SecInvalidateHandle(x) \
    ((PSecHandle)(x))->dwLower = ((PSecHandle)(x))->dwUpper = ((ULONG_PTR)((INT_PTR)-1));

#define SecIsValidHandle(x) \
    ( ( ((PSecHandle)(x))->dwLower != ((ULONG_PTR)((INT_PTR)-1 ))) && \
      ( ((PSecHandle)(x))->dwUpper != ((ULONG_PTR)((INT_PTR)-1 ))) )

typedef WCHAR SEC_WCHAR;
typedef CHAR SEC_CHAR;

#ifdef WIN32_CHICAGO
typedef unsigned __int64 QWORD, SECURITY_INTEGER, *PSECURITY_INTEGER;
#define SEC_SUCCESS(Status) ((Status) >= 0)
#elif defined(_NTDEF_) || defined(_WINNT_)
typedef LARGE_INTEGER _SECURITY_INTEGER, SECURITY_INTEGER, *PSECURITY_INTEGER;
#else // _NTDEF_ || _WINNT_
typedef struct _SECURITY_INTEGER
{
    unsigned long LowPart;
    long HighPart;
} SECURITY_INTEGER, *PSECURITY_INTEGER;
#endif // _NTDEF_ || _WINNT_


#ifdef SECURITY_MAC
typedef unsigned long TimeStamp,*PTimeStamp;
#else
typedef SECURITY_INTEGER TimeStamp, *PTimeStamp;
#endif

#ifdef _NTDEF_
typedef UNICODE_STRING SECURITY_STRING, *PSECURITY_STRING;
#else
typedef struct _SECURITY_STRING
{
    unsigned short Length;
    unsigned short MaximumLength;
    MIDL_PROP([size_is(MaximumLength / 2), length_is(Length / 2)]) unsigned short * Buffer;
} SECURITY_STRING, * PSECURITY_STRING;
#endif // _NTDEF_

#if ISSP_MODE == 0
#define PSSPI_SEC_STRING PSECURITY_STRING
#else
#define PSSPI_SEC_STRING SEC_WCHAR*
#endif

#ifndef _SSPIPFC_NONE_
typedef PVOID PSEC_WINNT_AUTH_IDENTITY_OPAQUE;
#else
typedef PSEC_WINNT_AUTH_IDENTITY_INFO PSEC_WINNT_AUTH_IDENTITY_OPAQUE;
#endif

#ifndef __SECSTATUS_DEFINED__
typedef LONG SECURITY_STATUS;
#define __SECSTATUS_DEFINED__
#endif

typedef enum _SECPKG_CRED_CLASS
{
    SecPkgCredClass_None = 0,
    SecPkgCredClass_Ephemeral = 10,
    SecPkgCredClass_PersistedGeneric = 20,
    SecPkgCredClass_PersistedSpecific = 30,
    SecPkgCredClass_Explicit = 40,
} SECPKG_CRED_CLASS, *PSECPKG_CRED_CLASS;

typedef struct _SEC_NEGOTIATION_INFO
{
    ULONG Size;
    ULONG NameLength;
    SEC_WCHAR *Name;
    PVOID Reserved;
} SEC_NEGOTIATION_INFO, *PSEC_NEGOTIATION_INFO;

typedef struct _SEC_CHANNEL_BINDINGS
{
    ULONG dwInitiatorAddrType;
    ULONG cbInitiatorLength;
    ULONG dwInitiatorOffset;
    ULONG dwAcceptorAddrType;
    ULONG cbAcceptorLength;
    ULONG dwAcceptorOffset;
    ULONG cbApplicationDataLength;
    ULONG dwApplicationDataOffset;
} SEC_CHANNEL_BINDINGS, *PSEC_CHANNEL_BINDINGS;

typedef enum _SEC_APPLICATION_PROTOCOL_NEGOTIATION_EXT
{
    SecApplicationProtocolNegotiationExt_None,
    SecApplicationProtocolNegotiationExt_NPN,
    SecApplicationProtocolNegotiationExt_ALPN
} SEC_APPLICATION_PROTOCOL_NEGOTIATION_EXT, *PSEC_APPLICATION_PROTOCOL_NEGOTIATION_EXT;

typedef struct _SEC_APPLICATION_PROTOCOL_LIST
{
    SEC_APPLICATION_PROTOCOL_NEGOTIATION_EXT ProtoNegoExt;
    USHORT ProtocolListSize;
    UCHAR ProtocolList[ANYSIZE_ARRAY];
} SEC_APPLICATION_PROTOCOL_LIST, *PSEC_APPLICATION_PROTOCOL_LIST;

typedef struct _SEC_APPLICATION_PROTOCOLS
{
    ULONG ProtocolListsSize;
    SEC_APPLICATION_PROTOCOL_LIST ProtocolLists[ANYSIZE_ARRAY];
} SEC_APPLICATION_PROTOCOLS, *PSEC_APPLICATION_PROTOCOLS;

typedef struct _SEC_SRTP_PROTECTION_PROFILES
{
    USHORT ProfilesSize;
    USHORT ProfilesList[ANYSIZE_ARRAY];
} SEC_SRTP_PROTECTION_PROFILES, *PSEC_SRTP_PROTECTION_PROFILES;

typedef struct _SEC_SRTP_MASTER_KEY_IDENTIFIER
{
    UCHAR MasterKeyIdentifierSize;
    UCHAR MasterKeyIdentifier[ANYSIZE_ARRAY];
} SEC_SRTP_MASTER_KEY_IDENTIFIER, *PSEC_SRTP_MASTER_KEY_IDENTIFIER;

typedef struct _SEC_TOKEN_BINDING
{
    unsigned char MajorVersion;
    unsigned char MinorVersion;
    unsigned short KeyParametersSize;
    unsigned char KeyParameters[ANYSIZE_ARRAY];
} SEC_TOKEN_BINDING, *PSEC_TOKEN_BINDING;

typedef struct _SEC_PRESHAREDKEY
{
    unsigned short KeySize;
    unsigned char  Key[ANYSIZE_ARRAY];
} SEC_PRESHAREDKEY, *PSEC_PRESHAREDKEY;

typedef struct _SEC_PRESHAREDKEY_IDENTITY
{
    unsigned short KeyIdentitySize;
    unsigned char  KeyIdentity[ANYSIZE_ARRAY];
} SEC_PRESHAREDKEY_IDENTITY, *PSEC_PRESHAREDKEY_IDENTITY;

typedef struct _SEC_DTLS_MTU
{
    unsigned short PathMTU;
} SEC_DTLS_MTU, *PSEC_DTLS_MTU;

#ifndef _AUTH_IDENTITY_EX2_DEFINED
#define _AUTH_IDENTITY_EX2_DEFINED
typedef struct _SEC_WINNT_AUTH_IDENTITY_EX2
{
    ULONG Version;
    USHORT cbHeaderLength;
    ULONG cbStructureLength;
    ULONG UserOffset;
    USHORT UserLength;
    ULONG DomainOffset;
    USHORT DomainLength;
    ULONG PackedCredentialsOffset;
    USHORT PackedCredentialsLength;
    ULONG Flags;
    ULONG PackageListOffset;
    USHORT PackageListLength;
} SEC_WINNT_AUTH_IDENTITY_EX2, *PSEC_WINNT_AUTH_IDENTITY_EX2;
#define SEC_WINNT_AUTH_IDENTITY_VERSION_2 0x201
#endif

#ifndef _AUTH_IDENTITY_DEFINED
#define _AUTH_IDENTITY_DEFINED
typedef struct _SEC_WINNT_AUTH_IDENTITY_W
{
    PUSHORT User;
    ULONG UserLength;
    PUSHORT Domain;
    ULONG DomainLength;
    PUSHORT Password;
    ULONG PasswordLength;
    ULONG Flags;
} SEC_WINNT_AUTH_IDENTITY_W, *PSEC_WINNT_AUTH_IDENTITY_W;
#define SEC_WINNT_AUTH_IDENTITY_ANSI    0x1
#define SEC_WINNT_AUTH_IDENTITY_UNICODE 0x2
#define _AUTH_IDENTITY_A_DEFINED
typedef struct _SEC_WINNT_AUTH_IDENTITY_A
{
    PUCHAR User;
    ULONG UserLength;
    PUCHAR Domain;
    ULONG DomainLength;
    PUCHAR Password;
    ULONG PasswordLength;
    ULONG Flags;
} SEC_WINNT_AUTH_IDENTITY_A, *PSEC_WINNT_AUTH_IDENTITY_A;
#ifdef UNICODE
#define SEC_WINNT_AUTH_IDENTITY SEC_WINNT_AUTH_IDENTITY_W
#define PSEC_WINNT_AUTH_IDENTITY PSEC_WINNT_AUTH_IDENTITY_W
#define _SEC_WINNT_AUTH_IDENTITY _SEC_WINNT_AUTH_IDENTITY_W
#else
#define SEC_WINNT_AUTH_IDENTITY SEC_WINNT_AUTH_IDENTITY_A
#define PSEC_WINNT_AUTH_IDENTITY PSEC_WINNT_AUTH_IDENTITY_A
#define _SEC_WINNT_AUTH_IDENTITY _SEC_WINNT_AUTH_IDENTITY_A
#endif
#endif

#ifndef SEC_WINNT_AUTH_IDENTITY_VERSION
#define SEC_WINNT_AUTH_IDENTITY_VERSION 0x200
typedef struct _SEC_WINNT_AUTH_IDENTITY_EXA
{
    ULONG Version;
    ULONG Length;
    PUCHAR User;
    ULONG UserLength;
    PUCHAR Domain;
    ULONG DomainLength;
    PUCHAR Password;
    ULONG PasswordLength;
    ULONG Flags;
    PUCHAR PackageList;
    ULONG PackageListLength;
} SEC_WINNT_AUTH_IDENTITY_EXA, *PSEC_WINNT_AUTH_IDENTITY_EXA;
typedef struct _SEC_WINNT_AUTH_IDENTITY_EXW
{
    ULONG Version;
    ULONG Length;
    PUSHORT User;
    ULONG UserLength;
    PUSHORT Domain;
    ULONG DomainLength;
    PUSHORT Password;
    ULONG PasswordLength;
    ULONG Flags;
    PUSHORT PackageList;
    ULONG PackageListLength;
} SEC_WINNT_AUTH_IDENTITY_EXW, *PSEC_WINNT_AUTH_IDENTITY_EXW;
#ifdef UNICODE
#define SEC_WINNT_AUTH_IDENTITY_EX  SEC_WINNT_AUTH_IDENTITY_EXW
#define PSEC_WINNT_AUTH_IDENTITY_EX PSEC_WINNT_AUTH_IDENTITY_EXW
#else
#define SEC_WINNT_AUTH_IDENTITY_EX  SEC_WINNT_AUTH_IDENTITY_EXA
#endif
#endif

#ifndef __SECHANDLE_DEFINED__
typedef struct _SecHandle
{
    ULONG_PTR dwLower;
    ULONG_PTR dwUpper;
} SecHandle, *PSecHandle;
#define __SECHANDLE_DEFINED__
#endif

typedef SecHandle CredHandle, *PCredHandle, CtxtHandle, *PCtxtHandle;

typedef struct _SecBuffer
{
    ULONG cbBuffer;
    ULONG BufferType;
#ifdef MIDL_PASS
    MIDL_PROP([size_is(cbBuffer)]) PCHAR pvBuffer;
#else
    _Field_size_bytes_(cbBuffer) void SEC_FAR *pvBuffer;
#endif
} SecBuffer, *PSecBuffer;

typedef struct _SecBufferDesc
{
    ULONG ulVersion;
    ULONG cBuffers;
    MIDL_PROP([size_is(cBuffers)]) _Field_size_(cBuffers) PSecBuffer pBuffers;
} SecBufferDesc, SEC_FAR *PSecBufferDesc;

typedef struct _SecPkgInfoA
{
    ULONG fCapabilities;
    USHORT wVersion;
    USHORT wRPCID;
    ULONG cbMaxToken;
    MIDL_PROP([string]) SEC_CHAR *Name;
    MIDL_PROP([string]) SEC_CHAR *Comment;
} SecPkgInfoA, *PSecPkgInfoA;

typedef struct _SecPkgInfoW
{
    ULONG fCapabilities;
    USHORT wVersion;
    USHORT wRPCID;
    ULONG cbMaxToken;
    MIDL_PROP([string]) SEC_WCHAR *Name;
    MIDL_PROP([string]) SEC_WCHAR *Comment;
} SecPkgInfoW, *PSecPkgInfoW;

#ifdef UNICODE
#define SecPkgInfo SecPkgInfoW
#define PSecPkgInfo PSecPkgInfoW
#else
#define SecPkgInfo SecPkgInfoA
#define PSecPkgInfo PSecPkgInfoA
#endif

typedef struct _SecPkgCredentials_NamesA
{
    MIDL_PROP([string]) SEC_CHAR *sUserName;
} SecPkgCredentials_NamesA, *PSecPkgCredentials_NamesA;

typedef struct _SecPkgCredentials_NamesW
{
    MIDL_PROP([string]) SEC_WCHAR *sUserName;
} SecPkgCredentials_NamesW, * PSecPkgCredentials_NamesW;

#ifdef UNICODE
#define SecPkgCredentials_Names SecPkgCredentials_NamesW
#define PSecPkgCredentials_Names PSecPkgCredentials_NamesW
#else
#define SecPkgCredentials_Names SecPkgCredentials_NamesA
#define PSecPkgCredentials_Names PSecPkgCredentials_NamesA
#endif

typedef struct _SecPkgContext_NamesA
{
    SEC_CHAR *sUserName;
} SecPkgContext_NamesA, * PSecPkgContext_NamesA;
typedef struct _SecPkgContext_NamesW
{
    SEC_WCHAR *sUserName;
} SecPkgContext_NamesW, *PSecPkgContext_NamesW;
#ifdef UNICODE
#define SecPkgContext_Names SecPkgContext_NamesW
#define PSecPkgContext_Names PSecPkgContext_NamesW
#else
#define SecPkgContext_Names SecPkgContext_NamesA
#define PSecPkgContext_Names PSecPkgContext_NamesA
#endif

typedef struct _SecPkgContext_CredentialNameA
{
    ULONG CredentialType;
    SEC_CHAR *sCredentialName;
} SecPkgContext_CredentialNameA, * PSecPkgContext_CredentialNameA;
typedef struct _SecPkgContext_CredentialNameW
{
    ULONG CredentialType;
    SEC_WCHAR *sCredentialName;
} SecPkgContext_CredentialNameW, *PSecPkgContext_CredentialNameW;
#ifdef UNICODE
#define SecPkgContext_CredentialName SecPkgContext_CredentialNameW
#define PSecPkgContext_CredentialName PSecPkgContext_CredentialNameW
#else
#define SecPkgContext_CredentialName SecPkgContext_CredentialNameA
#define PSecPkgContext_CredentialName PSecPkgContext_CredentialNameA
#endif

typedef struct _SecPkgContext_SubjectAttributes
{
    PVOID AttributeInfo;
} SecPkgContext_SubjectAttributes, *PSecPkgContext_SubjectAttributes;

typedef struct _SecPkgContext_CredInfo
{
    SECPKG_CRED_CLASS CredClass;
    ULONG IsPromptingNeeded;
} SecPkgContext_CredInfo, *PSecPkgContext_CredInfo;

typedef struct _SecPkgContext_NegoPackageInfo
{
    ULONG PackageMask;
} SecPkgContext_NegoPackageInfo, *PSecPkgContext_NegoPackageInfo;

typedef struct _SecPkgContext_NegoStatus
{
    ULONG LastStatus;
} SecPkgContext_NegoStatus, *PSecPkgContext_NegoStatus;

typedef struct _SecPkgContext_Sizes
{
    ULONG cbMaxToken;
    ULONG cbMaxSignature;
    ULONG cbBlockSize;
    ULONG cbSecurityTrailer;
} SecPkgContext_Sizes, *PSecPkgContext_Sizes;

typedef struct _SecPkgContext_StreamSizes
{
    ULONG cbHeader;
    ULONG cbTrailer;
    ULONG cbMaximumMessage;
    ULONG cBuffers;
    ULONG cbBlockSize;
} SecPkgContext_StreamSizes, *PSecPkgContext_StreamSizes;

typedef struct _SecPkgContext_Lifespan
{
    TimeStamp tsStart;
    TimeStamp tsExpiry;
} SecPkgContext_Lifespan, *PSecPkgContext_Lifespan;

typedef struct _SecPkgContext_PasswordExpiry
{
    TimeStamp tsPasswordExpires;
} SecPkgContext_PasswordExpiry, *PSecPkgContext_PasswordExpiry;

typedef struct _SecPkgContext_ProtoInfoA
{
    SEC_CHAR *sProtocolName;
    ULONG majorVersion;
    ULONG minorVersion;
} SecPkgContext_ProtoInfoA, *PSecPkgContext_ProtoInfoA;
typedef struct _SecPkgContext_ProtoInfoW
{
    SEC_WCHAR *sProtocolName;
    ULONG majorVersion;
    ULONG minorVersion;
} SecPkgContext_ProtoInfoW, *PSecPkgContext_ProtoInfoW;
#ifdef UNICODE
#define SecPkgContext_ProtoInfo SecPkgContext_ProtoInfoW
#define PSecPkgContext_ProtoInfo PSecPkgContext_ProtoInfoW
#else
#define SecPkgContext_ProtoInfo SecPkgContext_ProtoInfoA
#define PSecPkgContext_ProtoInfo PSecPkgContext_ProtoInfoA
#endif

typedef struct _SecPkgContext_KeyInfoA
{
    SEC_CHAR *sSignatureAlgorithmName;
    SEC_CHAR *sEncryptAlgorithmName;
    ULONG KeySize;
    ULONG SignatureAlgorithm;
    ULONG EncryptAlgorithm;
} SecPkgContext_KeyInfoA, *PSecPkgContext_KeyInfoA;
typedef struct _SecPkgContext_KeyInfoW
{
    SEC_WCHAR *sSignatureAlgorithmName;
    SEC_WCHAR *sEncryptAlgorithmName;
    ULONG KeySize;
    ULONG SignatureAlgorithm;
    ULONG EncryptAlgorithm;
} SecPkgContext_KeyInfoW, *PSecPkgContext_KeyInfoW;
#ifdef UNICODE
#define SecPkgContext_KeyInfo SecPkgContext_KeyInfoW
#define PSecPkgContext_KeyInfo PSecPkgContext_KeyInfoW
#else
#define SecPkgContext_KeyInfo SecPkgContext_KeyInfoA
#define PSecPkgContext_KeyInfo PSecPkgContext_KeyInfoA
#endif

typedef struct _SecPkgContext_SessionKey
{
    ULONG SessionKeyLength;
    _Field_size_bytes_(SessionKeyLength) PUCHAR SessionKey;
} SecPkgContext_SessionKey, *PSecPkgContext_SessionKey;

typedef struct _SecPkgContext_NegoKeys
{
    ULONG KeyType;
    USHORT KeyLength;
    _Field_size_bytes_(KeyLength) PUCHAR KeyValue;
    ULONG  VerifyKeyType;
    USHORT VerifyKeyLength;
    _Field_size_bytes_(VerifyKeyLength) PUCHAR VerifyKeyValue;
} SecPkgContext_NegoKeys, *PSecPkgContext_NegoKeys;

typedef struct _SecPkgContext_DceInfo
{
    ULONG AuthzSvc;
    PVOID pPac;
} SecPkgContext_DceInfo, *PSecPkgContext_DceInfo;

typedef struct _SecPkgContext_PackageInfoA
{
    PSecPkgInfoA PackageInfo;
} SecPkgContext_PackageInfoA, * PSecPkgContext_PackageInfoA;
typedef struct _SecPkgContext_PackageInfoW
{
    PSecPkgInfoW PackageInfo;
} SecPkgContext_PackageInfoW, *PSecPkgContext_PackageInfoW;
#ifdef UNICODE
#define SecPkgContext_PackageInfo SecPkgContext_PackageInfoW
#define PSecPkgContext_PackageInfo PSecPkgContext_PackageInfoW
#else
#define SecPkgContext_PackageInfo SecPkgContext_PackageInfoA
#define PSecPkgContext_PackageInfo PSecPkgContext_PackageInfoA
#endif

typedef struct _SecPkgContext_UserFlags
{
    ULONG UserFlags;
} SecPkgContext_UserFlags, *PSecPkgContext_UserFlags;

typedef struct _SecPkgContext_Flags
{
    ULONG Flags;
} SecPkgContext_Flags, *PSecPkgContext_Flags;

typedef struct _SecPkgContext_NegotiationInfoA
{
    PSecPkgInfoA PackageInfo;
    ULONG NegotiationState;
} SecPkgContext_NegotiationInfoA, *PSecPkgContext_NegotiationInfoA;
typedef struct _SecPkgContext_NegotiationInfoW
{
    PSecPkgInfoW PackageInfo;
    ULONG NegotiationState;
} SecPkgContext_NegotiationInfoW, *PSecPkgContext_NegotiationInfoW;
#ifdef UNICODE
#define SecPkgContext_NegotiationInfo SecPkgContext_NegotiationInfoW
#define PSecPkgContext_NegotiationInfo PSecPkgContext_NegotiationInfoW
#else
#define SecPkgContext_NegotiationInfo SecPkgContext_NegotiationInfoA
#define PSecPkgContext_NegotiationInfo PSecPkgContext_NegotiationInfoA
#endif

typedef struct _SecPkgContext_AuthorityA
{
    SEC_CHAR *sAuthorityName;
} SecPkgContext_AuthorityA, *PSecPkgContext_AuthorityA;
typedef struct _SecPkgContext_AuthorityW
{
    SEC_WCHAR *sAuthorityName;
} SecPkgContext_AuthorityW, *PSecPkgContext_AuthorityW;
#ifdef UNICODE
#define SecPkgContext_Authority SecPkgContext_AuthorityW
#define PSecPkgContext_Authority PSecPkgContext_AuthorityW
#else
#define SecPkgContext_Authority SecPkgContext_AuthorityA
#define PSecPkgContext_Authority PSecPkgContext_AuthorityA
#endif

#if NTDDI_VERSION > NTDDI_WS03
typedef struct _SecPkgCredentials_SSIProviderA
{
    SEC_CHAR *sProviderName;
    ULONG ProviderInfoLength;
    PCHAR ProviderInfo;
} SecPkgCredentials_SSIProviderA, * PSecPkgCredentials_SSIProviderA;
typedef struct _SecPkgCredentials_SSIProviderW
{
    SEC_WCHAR *sProviderName;
    ULONG ProviderInfoLength;
    PCHAR ProviderInfo;
} SecPkgCredentials_SSIProviderW, *PSecPkgCredentials_SSIProviderW;
#ifdef UNICODE
#define SecPkgCredentials_SSIProvider SecPkgCredentials_SSIProviderW
#define PSecPkgCredentials_SSIProvider PSecPkgCredentials_SSIProviderW
#else
#define SecPkgCredentials_SSIProvider SecPkgCredentials_SSIProviderA
#define PSecPkgCredentials_SSIProvider PSecPkgCredentials_SSIProviderA
#endif

typedef struct _SecPkgContext_LogoffTime
{
    TimeStamp tsLogoffTime;
} SecPkgContext_LogoffTime, *PSecPkgContext_LogoffTime;
#endif

typedef struct _SecPkgCredentials_KdcProxySettingsW
{
    ULONG Version;
    ULONG Flags;
    USHORT ProxyServerOffset;
    USHORT ProxyServerLength;
    USHORT ClientTlsCredOffset;
    USHORT ClientTlsCredLength;
} SecPkgCredentials_KdcProxySettingsW, *PSecPkgCredentials_KdcProxySettingsW;

typedef struct _SecPkgCredentials_Cert
{
    ULONG EncodedCertSize;
    PUCHAR EncodedCert;
} SecPkgCredentials_Cert, *PSecPkgCredentials_Cert;

typedef SecPkgContext_StreamSizes SecPkgContext_DatagramSizes;
typedef PSecPkgContext_StreamSizes PSecPkgContext_DatagramSizes;

typedef enum _SECPKG_ATTR_LCT_STATUS
{
    SecPkgAttrLastClientTokenYes,
    SecPkgAttrLastClientTokenNo,
    SecPkgAttrLastClientTokenMaybe
} SECPKG_ATTR_LCT_STATUS, *PSECPKG_ATTR_LCT_STATUS;

typedef struct _SecPkgContext_LastClientTokenStatus
{
    SECPKG_ATTR_LCT_STATUS LastClientTokenStatus;
} SecPkgContext_LastClientTokenStatus, *PSecPkgContext_LastClientTokenStatus;

typedef struct _SecPkgContext_AccessToken
{
    PVOID AccessToken;
} SecPkgContext_AccessToken, *PSecPkgContext_AccessToken;

typedef struct _SecPkgContext_TargetInformation
{
    ULONG MarshalledTargetInfoLength;
    PUCHAR MarshalledTargetInfo;
} SecPkgContext_TargetInformation, *PSecPkgContext_TargetInformation;

typedef struct _SecPkgContext_AuthzID
{
    ULONG AuthzIDLength;
    PCHAR AuthzID;
} SecPkgContext_AuthzID, *PSecPkgContext_AuthzID;

typedef struct _SecPkgContext_Target
{
    ULONG TargetLength;
    PCHAR Target;
} SecPkgContext_Target, *PSecPkgContext_Target;


typedef struct _SecPkgContext_ClientSpecifiedTarget
{
    SEC_WCHAR *sTargetName;
} SecPkgContext_ClientSpecifiedTarget, *PSecPkgContext_ClientSpecifiedTarget;

typedef struct _SecPkgContext_Bindings
{
    ULONG BindingsLength;
    _Field_size_bytes_(BindingsLength) SEC_CHANNEL_BINDINGS *Bindings;
} SecPkgContext_Bindings, *PSecPkgContext_Bindings;

typedef enum _SEC_APPLICATION_PROTOCOL_NEGOTIATION_STATUS
{
    SecApplicationProtocolNegotiationStatus_None,
    SecApplicationProtocolNegotiationStatus_Success,
    SecApplicationProtocolNegotiationStatus_SelectedClientOnly
} SEC_APPLICATION_PROTOCOL_NEGOTIATION_STATUS, *PSEC_APPLICATION_PROTOCOL_NEGOTIATION_STATUS;

#define MAX_PROTOCOL_ID_SIZE 0xff

typedef struct _SecPkgContext_ApplicationProtocol
{
    SEC_APPLICATION_PROTOCOL_NEGOTIATION_STATUS ProtoNegoStatus;
    SEC_APPLICATION_PROTOCOL_NEGOTIATION_EXT ProtoNegoExt;
    UCHAR ProtocolIdSize;
    UCHAR ProtocolId[MAX_PROTOCOL_ID_SIZE];
} SecPkgContext_ApplicationProtocol, *PSecPkgContext_ApplicationProtocol;

typedef struct _SecPkgContext_NegotiatedTlsExtensions
{
    ULONG ExtensionsCount;
    _Field_size_(ExtensionsCount) unsigned short * Extensions;
} SecPkgContext_NegotiatedTlsExtensions, *PSecPkgContext_NegotiatedTlsExtensions;

typedef struct _SECPKG_APP_MODE_INFO
{
    ULONG UserFunction;
    ULONG_PTR Argument1;
    ULONG_PTR Argument2;
    SecBuffer UserData;
    BOOLEAN ReturnToLsa;
} SECPKG_APP_MODE_INFO, *PSECPKG_APP_MODE_INFO;

#define FreeCredentialHandle FreeCredentialsHandle
typedef struct _SECURITY_FUNCTION_TABLE_A
{
    ULONG dwVersion;
    ENUMERATE_SECURITY_PACKAGES_FN_A EnumerateSecurityPackagesA;
    QUERY_CREDENTIALS_ATTRIBUTES_FN_A QueryCredentialsAttributesA;
    ACQUIRE_CREDENTIALS_HANDLE_FN_A AcquireCredentialsHandleA;
    FREE_CREDENTIALS_HANDLE_FN FreeCredentialHandle;
    PVOID Reserved2;
    INITIALIZE_SECURITY_CONTEXT_FN_A InitializeSecurityContextA;
    ACCEPT_SECURITY_CONTEXT_FN AcceptSecurityContext;
    COMPLETE_AUTH_TOKEN_FN CompleteAuthToken;
    DELETE_SECURITY_CONTEXT_FN DeleteSecurityContext;
    APPLY_CONTROL_TOKEN_FN ApplyControlToken;
    QUERY_CONTEXT_ATTRIBUTES_FN_A QueryContextAttributesA;
    IMPERSONATE_SECURITY_CONTEXT_FN ImpersonateSecurityContext;
    REVERT_SECURITY_CONTEXT_FN RevertSecurityContext;
    MAKE_SIGNATURE_FN MakeSignature;
    VERIFY_SIGNATURE_FN VerifySignature;
    FREE_CONTEXT_BUFFER_FN FreeContextBuffer;
    QUERY_SECURITY_PACKAGE_INFO_FN_A QuerySecurityPackageInfoA;
    PVOID Reserved3;
    PVOID Reserved4;
    EXPORT_SECURITY_CONTEXT_FN ExportSecurityContext;
    IMPORT_SECURITY_CONTEXT_FN_A ImportSecurityContextA;
    ADD_CREDENTIALS_FN_A AddCredentialsA ;
    PVOID Reserved8;
    QUERY_SECURITY_CONTEXT_TOKEN_FN QuerySecurityContextToken;
    ENCRYPT_MESSAGE_FN EncryptMessage;
    DECRYPT_MESSAGE_FN DecryptMessage;
    SET_CONTEXT_ATTRIBUTES_FN_A SetContextAttributesA;
    SET_CREDENTIALS_ATTRIBUTES_FN_A SetCredentialsAttributesA;
#if (ISSP_MODE != 0)
    CHANGE_PASSWORD_FN_A ChangeAccountPasswordA;
#else
    PVOID Reserved9;
#endif
#if (NTDDI_VERSION > NTDDI_WINBLUE)
    QUERY_CONTEXT_ATTRIBUTES_EX_FN_A QueryContextAttributesExA;
    QUERY_CREDENTIALS_ATTRIBUTES_EX_FN_A QueryCredentialsAttributesExA;
#endif
} SecurityFunctionTableA, *PSecurityFunctionTableA;
typedef struct _SECURITY_FUNCTION_TABLE_W
{
    ULONG dwVersion;
    ENUMERATE_SECURITY_PACKAGES_FN_W EnumerateSecurityPackagesW;
    QUERY_CREDENTIALS_ATTRIBUTES_FN_W QueryCredentialsAttributesW;
    ACQUIRE_CREDENTIALS_HANDLE_FN_W AcquireCredentialsHandleW;
    FREE_CREDENTIALS_HANDLE_FN FreeCredentialsHandle;
    PVOID Reserved2;
    INITIALIZE_SECURITY_CONTEXT_FN_W InitializeSecurityContextW;
    ACCEPT_SECURITY_CONTEXT_FN AcceptSecurityContext;
    COMPLETE_AUTH_TOKEN_FN CompleteAuthToken;
    DELETE_SECURITY_CONTEXT_FN DeleteSecurityContext;
    APPLY_CONTROL_TOKEN_FN ApplyControlToken;
    QUERY_CONTEXT_ATTRIBUTES_FN_W QueryContextAttributesW;
    IMPERSONATE_SECURITY_CONTEXT_FN ImpersonateSecurityContext;
    REVERT_SECURITY_CONTEXT_FN RevertSecurityContext;
    MAKE_SIGNATURE_FN MakeSignature;
    VERIFY_SIGNATURE_FN VerifySignature;
    FREE_CONTEXT_BUFFER_FN FreeContextBuffer;
    QUERY_SECURITY_PACKAGE_INFO_FN_W QuerySecurityPackageInfoW;
    PVOID Reserved3;
    PVOID Reserved4;
    EXPORT_SECURITY_CONTEXT_FN ExportSecurityContext;
    IMPORT_SECURITY_CONTEXT_FN_W ImportSecurityContextW;
    ADD_CREDENTIALS_FN_W AddCredentialsW ;
    PVOID Reserved8;
    QUERY_SECURITY_CONTEXT_TOKEN_FN QuerySecurityContextToken;
    ENCRYPT_MESSAGE_FN EncryptMessage;
    DECRYPT_MESSAGE_FN DecryptMessage;
#if OSVER(NTDDI_VERSION) > NTDDI_WIN2K // ???
    SET_CONTEXT_ATTRIBUTES_FN_W SetContextAttributesW;
#endif
#if NTDDI_VERSION > NTDDI_WS03SP1
    SET_CREDENTIALS_ATTRIBUTES_FN_W SetCredentialsAttributesW;
#endif
#if ISSP_MODE != 0
    CHANGE_PASSWORD_FN_W ChangeAccountPasswordW;
#else
    PVOID Reserved9;
#endif
#if NTDDI_VERSION > NTDDI_WINBLUE
    QUERY_CONTEXT_ATTRIBUTES_EX_FN_W    QueryContextAttributesExW;
    QUERY_CREDENTIALS_ATTRIBUTES_EX_FN_W QueryCredentialsAttributesExW;
#endif
} SecurityFunctionTableW, *PSecurityFunctionTableW;
#ifdef UNICODE
#define SecurityFunctionTable SecurityFunctionTableW
#define PSecurityFunctionTable PSecurityFunctionTableW
#else
#define SecurityFunctionTable SecurityFunctionTableA
#define PSecurityFunctionTable PSecurityFunctionTableA
#endif

typedef
VOID
(SEC_ENTRY * SEC_GET_KEY_FN)(
    PVOID Arg,
    PVOID Principal,
    ULONG KeyVer,
    PVOID *Key,
    SECURITY_STATUS *Status);

typedef
SECURITY_STATUS
(SEC_ENTRY * ACQUIRE_CREDENTIALS_HANDLE_FN_A)(
    SEC_CHAR *,
    SEC_CHAR *,
    ULONG,
    PVOID,
    PVOID,
    SEC_GET_KEY_FN,
    PVOID,
    PCredHandle,
    PTimeStamp);
typedef
SECURITY_STATUS
(SEC_ENTRY * ACQUIRE_CREDENTIALS_HANDLE_FN_W)(
    PSSPI_SEC_STRING,
    PSSPI_SEC_STRING,
    ULONG,
    PVOID,
    PVOID,
    SEC_GET_KEY_FN,
    PVOID,
    PCredHandle,
    PTimeStamp);
#define ACQUIRE_CREDENTIALS_HANDLE_FN ACQUIRE_CREDENTIALS_HANDLE_FN_W
#ifdef UNICODE
#define AcquireCredentialsHandle AcquireCredentialsHandleW
#define ACQUIRE_CREDENTIALS_HANDLE_FN ACQUIRE_CREDENTIALS_HANDLE_FN_W
#else
#define AcquireCredentialsHandle AcquireCredentialsHandleA
#define ACQUIRE_CREDENTIALS_HANDLE_FN ACQUIRE_CREDENTIALS_HANDLE_FN_A
#endif

typedef
PSecurityFunctionTableA
(SEC_ENTRY * INIT_SECURITY_INTERFACE_A)(VOID);
typedef
PSecurityFunctionTableW
(SEC_ENTRY * INIT_SECURITY_INTERFACE_W)(VOID);
#ifdef UNICODE
#define INIT_SECURITY_INTERFACE INIT_SECURITY_INTERFACE_W
#else
#define INIT_SECURITY_INTERFACE INIT_SECURITY_INTERFACE_A
#endif

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
AcceptSecurityContext(
    _In_opt_ PCredHandle phCredential,
    _In_opt_ PCtxtHandle phContext,
    _In_opt_ PSecBufferDesc pInput,
    _In_ ULONG fContextReq,
    _In_ ULONG TargetDataRep,
    _Inout_opt_ PCtxtHandle phNewContext,
    _Inout_opt_ PSecBufferDesc pOutput,
    _Out_ PULONG pfContextAttr,
    _Out_opt_ PTimeStamp ptsExpiry);

typedef
SECURITY_STATUS
(SEC_ENTRY * ACCEPT_SECURITY_CONTEXT_FN)(
    PCredHandle,
    PCtxtHandle,
    PSecBufferDesc,
    ULONG,
    ULONG,
    PCtxtHandle,
    PSecBufferDesc,
    PULONG,
    PTimeStamp);

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
AcquireCredentialsHandleW(
#if ISSP_MODE == 0
    _In_opt_ PSECURITY_STRING pPrincipal,
    _In_ PSECURITY_STRING pPackage,
#else
    _In_opt_ LPWSTR pszPrincipal,
    _In_ LPWSTR pszPackage,
#endif
    _In_ ULONG fCredentialUse,
    _In_opt_ PVOID pvLogonId,
    _In_opt_ PVOID pAuthData,
    _In_opt_ SEC_GET_KEY_FN pGetKeyFn,
    _In_opt_ PVOID pvGetKeyArgument,
    _Out_ PCredHandle phCredential,
    _Out_opt_ PTimeStamp ptsExpiry);
#define AcquireCredentialsHandle AcquireCredentialsHandleW

SECURITY_STATUS
SEC_ENTRY
AddCredentialsA(
    _In_ PCredHandle hCredentials,
    _In_opt_ LPSTR pszPrincipal,
    _In_ LPSTR pszPackage,
    _In_ ULONG fCredentialUse,
    _In_opt_ PVOID pAuthData,
    _In_opt_ SEC_GET_KEY_FN pGetKeyFn,
    _In_opt_ PVOID pvGetKeyArgument,
    _Out_opt_ PTimeStamp ptsExpiry);

typedef
SECURITY_STATUS
(SEC_ENTRY * ADD_CREDENTIALS_FN_A)(
    PCredHandle,
    SEC_CHAR *,
    SEC_CHAR *,
    ULONG,
    PVOID,
    SEC_GET_KEY_FN,
    PVOID,
    PTimeStamp);

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
AddCredentialsW(
    _In_ PCredHandle hCredentials,
#if ISSP_MODE == 0
    _In_opt_ PSECURITY_STRING pPrincipal,
    _In_ PSECURITY_STRING pPackage,
#else
    _In_opt_ LPWSTR pszPrincipal,
    _In_ LPWSTR pszPackage,
#endif
    _In_ ULONG fCredentialUse,
    _In_opt_ PVOID pAuthData,
    _In_opt_ SEC_GET_KEY_FN pGetKeyFn,
    _In_opt_ PVOID pvGetKeyArgument,
    _Out_opt_ PTimeStamp ptsExpiry);

typedef
SECURITY_STATUS
(SEC_ENTRY * ADD_CREDENTIALS_FN_W)(
    PCredHandle,
    PSSPI_SEC_STRING,
    PSSPI_SEC_STRING,
    ULONG,
    PVOID,
    SEC_GET_KEY_FN,
    PVOID,
    PTimeStamp);

#ifdef UNICODE
#define AddCredentials  AddCredentialsW
#define ADD_CREDENTIALS_FN  ADD_CREDENTIALS_FN_W
#else
#define AddCredentials  AddCredentialsA
#define ADD_CREDENTIALS_FN ADD_CREDENTIALS_FN_A
#endif

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
ApplyControlToken(
    _In_ PCtxtHandle phContext,
    _In_ PSecBufferDesc pInput);

typedef
SECURITY_STATUS
(SEC_ENTRY * APPLY_CONTROL_TOKEN_FN)(
    PCtxtHandle, PSecBufferDesc);

#if (ISSP_MODE != 0)

SECURITY_STATUS
SEC_ENTRY
ChangeAccountPasswordA(
    _In_ SEC_CHAR* pszPackageName,
    _In_ SEC_CHAR* pszDomainName,
    _In_ SEC_CHAR* pszAccountName,
    _In_ SEC_CHAR* pszOldPassword,
    _In_ SEC_CHAR* pszNewPassword,
    _In_ BOOLEAN bImpersonating,
    _In_ ULONG dwReserved,
    _Inout_ PSecBufferDesc pOutput);

typedef
SECURITY_STATUS
(SEC_ENTRY * CHANGE_PASSWORD_FN_A)(
    SEC_CHAR *,
    SEC_CHAR *,
    SEC_CHAR *,
    SEC_CHAR *,
    SEC_CHAR *,
    BOOLEAN,
    ULONG,
    PSecBufferDesc);

SECURITY_STATUS
SEC_ENTRY
ChangeAccountPasswordW(
    _In_ SEC_WCHAR* pszPackageName,
    _In_ SEC_WCHAR* pszDomainName,
    _In_ SEC_WCHAR* pszAccountName,
    _In_ SEC_WCHAR* pszOldPassword,
    _In_ SEC_WCHAR* pszNewPassword,
    _In_ BOOLEAN bImpersonating,
    _In_ ULONG dwReserved,
    _Inout_ PSecBufferDesc pOutput);

typedef
SECURITY_STATUS
(SEC_ENTRY * CHANGE_PASSWORD_FN_W)(
    SEC_WCHAR *,
    SEC_WCHAR *,
    SEC_WCHAR *,
    SEC_WCHAR *,
    SEC_WCHAR *,
    BOOLEAN,
    ULONG,
    PSecBufferDesc);

#ifdef UNICODE
#define ChangeAccountPassword ChangeAccountPasswordW
#define CHANGE_PASSWORD_FN CHANGE_PASSWORD_FN_W
#else
#define ChangeAccountPassword ChangeAccountPasswordA
#define CHANGE_PASSWORD_FN CHANGE_PASSWORD_FN_A
#endif

#endif /* ISSP_MODE != 0 */

SECURITY_STATUS
SEC_ENTRY
CompleteAuthToken(
    _In_ PCtxtHandle phContext,
    _In_ PSecBufferDesc pToken);

typedef
SECURITY_STATUS
(SEC_ENTRY * COMPLETE_AUTH_TOKEN_FN)(
    PCtxtHandle,
    PSecBufferDesc);

SECURITY_STATUS
SEC_ENTRY
DecryptMessage(
    _In_ PCtxtHandle phContext,
    _Inout_ PSecBufferDesc pMessage,
    _In_ ULONG MessageSeqNo,
    _Out_opt_ PULONG pfQOP);

typedef
SECURITY_STATUS
(SEC_ENTRY * DECRYPT_MESSAGE_FN)(
    PCtxtHandle,
    PSecBufferDesc,
    ULONG,
    PULONG);

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
DeleteSecurityContext(
    _In_ PCtxtHandle phContext);

typedef
SECURITY_STATUS
(SEC_ENTRY * DELETE_SECURITY_CONTEXT_FN)(
    PCtxtHandle);

SECURITY_STATUS
SEC_ENTRY
EncryptMessage(
    _In_ PCtxtHandle phContext,
    _In_ ULONG fQOP,
    _In_ PSecBufferDesc pMessage,
    _In_ ULONG MessageSeqNo);

typedef
SECURITY_STATUS
(SEC_ENTRY * ENCRYPT_MESSAGE_FN)(
    PCtxtHandle,
    ULONG,
    PSecBufferDesc,
    ULONG);

SECURITY_STATUS
SEC_ENTRY
EnumerateSecurityPackagesA(
    _Out_ PULONG pcPackages,
    _Outptr_ PSecPkgInfoA* ppPackageInfo);

typedef SECURITY_STATUS
(SEC_ENTRY * ENUMERATE_SECURITY_PACKAGES_FN_A)(
    PULONG,
    PSecPkgInfoA*);

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
EnumerateSecurityPackagesW(
    _Out_ PULONG pcPackages,
    _Outptr_ PSecPkgInfoW* ppPackageInfo);

typedef
SECURITY_STATUS
(SEC_ENTRY * ENUMERATE_SECURITY_PACKAGES_FN_W)(
    PULONG,
    PSecPkgInfoW*);

#ifdef UNICODE
#define EnumerateSecurityPackages EnumerateSecurityPackagesW
#define ENUMERATE_SECURITY_PACKAGES_FN ENUMERATE_SECURITY_PACKAGES_FN_W
#else
#define EnumerateSecurityPackages EnumerateSecurityPackagesA
#define ENUMERATE_SECURITY_PACKAGES_FN ENUMERATE_SECURITY_PACKAGES_FN_A
#endif

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
ExportSecurityContext(
    _In_ PCtxtHandle phContext,
    _In_ ULONG fFlags,
    _Out_ PSecBuffer pPackedContext,
    _Out_ PVOID* pToken);

typedef
SECURITY_STATUS
(SEC_ENTRY * EXPORT_SECURITY_CONTEXT_FN)(
    PCtxtHandle,
    ULONG,
    PSecBuffer,
    PVOID*);

SECURITY_STATUS
SEC_ENTRY
FreeContextBuffer(
    _Inout_ PVOID pvContextBuffer);

typedef
SECURITY_STATUS
(SEC_ENTRY * FREE_CONTEXT_BUFFER_FN)(
    _Inout_ PVOID);

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
FreeCredentialsHandle(
    _In_ PCredHandle phCredential);

typedef
SECURITY_STATUS
(SEC_ENTRY * FREE_CREDENTIALS_HANDLE_FN)(
    PCredHandle);

KSECDDDECLSPEC
_Check_return_
SECURITY_STATUS
SEC_ENTRY
ImpersonateSecurityContext(
    _In_ PCtxtHandle phContext);

typedef
SECURITY_STATUS
(SEC_ENTRY * IMPERSONATE_SECURITY_CONTEXT_FN)(
    PCtxtHandle);

SECURITY_STATUS
SEC_ENTRY
ImportSecurityContextA(
    _In_ LPSTR pszPackage,
    _In_ PSecBuffer pPackedContext,
    _In_ PVOID Token,
    _Out_ PCtxtHandle phContext
    );

typedef
SECURITY_STATUS
(SEC_ENTRY * IMPORT_SECURITY_CONTEXT_FN_A)(
    SEC_CHAR*,
    PSecBuffer,
    PVOID,
    PCtxtHandle);

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
ImportSecurityContextW(
    _In_ PSSPI_SEC_STRING pszPackage,
    _In_ PSecBuffer pPackedContext,
    _In_ PVOID Token,
    _Out_ PCtxtHandle phContext);

typedef
SECURITY_STATUS
(SEC_ENTRY * IMPORT_SECURITY_CONTEXT_FN_W)(
    PSSPI_SEC_STRING,
    PSecBuffer,
    PVOID,
    PCtxtHandle);

#ifdef UNICODE
#define ImportSecurityContext ImportSecurityContextW
#define IMPORT_SECURITY_CONTEXT_FN IMPORT_SECURITY_CONTEXT_FN_W
#else
#define ImportSecurityContext ImportSecurityContextA
#define IMPORT_SECURITY_CONTEXT_FN IMPORT_SECURITY_CONTEXT_FN_A
#endif

SECURITY_STATUS
SEC_ENTRY
InitializeSecurityContextA(
    _In_opt_ PCredHandle phCredential,
    _In_opt_ PCtxtHandle phContext,
    _In_opt_ SEC_CHAR* pszTargetName,
    _In_ ULONG fContextReq,
    _In_ ULONG Reserved1,
    _In_ ULONG TargetDataRep,
    _In_opt_ PSecBufferDesc pInput,
    _In_ ULONG Reserved2,
    _Inout_opt_ PCtxtHandle phNewContext,
    _Inout_opt_ PSecBufferDesc pOutput,
    _Out_ PULONG pfContextAttr,
    _Out_opt_ PTimeStamp ptsExpiry);

typedef
SECURITY_STATUS
(SEC_ENTRY * INITIALIZE_SECURITY_CONTEXT_FN_A)(
    PCredHandle,
    PCtxtHandle,
    SEC_CHAR*,
    ULONG,
    ULONG,
    ULONG,
    PSecBufferDesc,
    ULONG,
    PCtxtHandle,
    PSecBufferDesc,
    PULONG,
    PTimeStamp);

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
InitializeSecurityContextW(
    _In_opt_ PCredHandle phCredential,
    _In_opt_ PCtxtHandle phContext,
    _In_opt_ PSSPI_SEC_STRING pTargetName,
    _In_ ULONG fContextReq,
    _In_ ULONG Reserved1,
    _In_ ULONG TargetDataRep,
    _In_opt_ PSecBufferDesc pInput,
    _In_ ULONG Reserved2,
    _Inout_opt_ PCtxtHandle phNewContext,
    _Inout_opt_ PSecBufferDesc pOutput,
    _Out_ PULONG pfContextAttr,
    _Out_opt_ PTimeStamp ptsExpiry);

typedef
SECURITY_STATUS
(SEC_ENTRY * INITIALIZE_SECURITY_CONTEXT_FN_W)(
    PCredHandle,
    PCtxtHandle,
    PSSPI_SEC_STRING,
    ULONG,
    ULONG,
    ULONG,
    PSecBufferDesc,
    ULONG,
    PCtxtHandle,
    PSecBufferDesc,
    PULONG,
    PTimeStamp);

#ifdef UNICODE
#define InitializeSecurityContext InitializeSecurityContextW
#define INITIALIZE_SECURITY_CONTEXT_FN INITIALIZE_SECURITY_CONTEXT_FN_W
#else
#define InitializeSecurityContext InitializeSecurityContextA
#define INITIALIZE_SECURITY_CONTEXT_FN INITIALIZE_SECURITY_CONTEXT_FN_A
#endif

PSecurityFunctionTableA
SEC_ENTRY
InitSecurityInterfaceA(VOID);

KSECDDDECLSPEC
PSecurityFunctionTableW
SEC_ENTRY
InitSecurityInterfaceW(VOID);

#ifdef UNICODE
#define InitSecurityInterface InitSecurityInterfaceW
#else
#define InitSecurityInterface InitSecurityInterfaceA
#endif

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
MakeSignature(
    _In_ PCtxtHandle phContext,
    _In_ ULONG fQOP,
    _In_ PSecBufferDesc pMessage,
    _In_ ULONG MessageSeqNo);

typedef
SECURITY_STATUS
(SEC_ENTRY * MAKE_SIGNATURE_FN)(
    PCtxtHandle,
    ULONG,
    PSecBufferDesc,
    ULONG);

SECURITY_STATUS
SEC_ENTRY
QueryContextAttributesA(
    _In_ PCtxtHandle phContext,
    _In_ ULONG ulAttribute,
    _Out_ PVOID pBuffer);

typedef SECURITY_STATUS
(SEC_ENTRY * QUERY_CONTEXT_ATTRIBUTES_FN_A)(
    PCtxtHandle,
    ULONG,
    PVOID);

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
QueryContextAttributesW(
    _In_ PCtxtHandle phContext,
    _In_ ULONG ulAttribute,
    _Out_ PVOID pBuffer);

typedef
SECURITY_STATUS
(SEC_ENTRY * QUERY_CONTEXT_ATTRIBUTES_FN_W)(
    PCtxtHandle,
    ULONG,
    PVOID);

#ifdef UNICODE
#define QueryContextAttributes QueryContextAttributesW
#define QUERY_CONTEXT_ATTRIBUTES_FN QUERY_CONTEXT_ATTRIBUTES_FN_W
#else
#define QueryContextAttributes QueryContextAttributesA
#define QUERY_CONTEXT_ATTRIBUTES_FN QUERY_CONTEXT_ATTRIBUTES_FN_A
#endif // !UNICODE

SECURITY_STATUS
SEC_ENTRY
QueryContextAttributesExA(
    _In_ PCtxtHandle phContext,
    _In_ ULONG ulAttribute,
    _Out_writes_bytes_(cbBuffer) PVOID pBuffer,
    _In_ ULONG cbBuffer);

typedef
SECURITY_STATUS
(SEC_ENTRY * QUERY_CONTEXT_ATTRIBUTES_EX_FN_A)(
    PCtxtHandle,
    ULONG,
    PVOID,
    ULONG);

SECURITY_STATUS
SEC_ENTRY
QueryContextAttributesExW(
    _In_ PCtxtHandle phContext,
    _In_ ULONG ulAttribute,
    _Out_writes_bytes_(cbBuffer) PVOID pBuffer,
    _In_ ULONG cbBuffer);

typedef
SECURITY_STATUS
(SEC_ENTRY * QUERY_CONTEXT_ATTRIBUTES_EX_FN_W)(
    PCtxtHandle,
    ULONG,
    PVOID,
    ULONG);

#ifdef UNICODE
#define QueryContextAttributesEx QueryContextAttributesExW
#define QUERY_CONTEXT_ATTRIBUTES_EX_FN QUERY_CONTEXT_ATTRIBUTES_EX_FN_W
#else
#define QueryContextAttributesEx QueryContextAttributesExA
#define QUERY_CONTEXT_ATTRIBUTES_EX_FN QUERY_CONTEXT_ATTRIBUTES_EX_FN_A
#endif // !UNICODE

SECURITY_STATUS
SEC_ENTRY
QueryCredentialsAttributesA(
    _In_ PCredHandle phCredential,
    _In_ ULONG ulAttribute,
    _Inout_ PVOID pBuffer);

typedef
SECURITY_STATUS
(SEC_ENTRY * QUERY_CREDENTIALS_ATTRIBUTES_FN_A)(
    PCredHandle,
    ULONG,
    PVOID);

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
QueryCredentialsAttributesW(
    _In_ PCredHandle phCredential,
    _In_ ULONG ulAttribute,
    _Inout_ PVOID pBuffer);
#define QueryCredentialsAttributes QueryCredentialsAttributesW

typedef
SECURITY_STATUS
(SEC_ENTRY * QUERY_CREDENTIALS_ATTRIBUTES_FN_W)(
    PCredHandle,
    ULONG,
    PVOID);
#define QUERY_CREDENTIALS_ATTRIBUTES_FN QUERY_CREDENTIALS_ATTRIBUTES_FN_W

#ifdef UNICODE
#define QueryCredentialsAttributes QueryCredentialsAttributesW
#define QUERY_CREDENTIALS_ATTRIBUTES_FN QUERY_CREDENTIALS_ATTRIBUTES_FN_W
#else
#define QueryCredentialsAttributes QueryCredentialsAttributesA
#define QUERY_CREDENTIALS_ATTRIBUTES_FN QUERY_CREDENTIALS_ATTRIBUTES_FN_A
#endif

SECURITY_STATUS SEC_ENTRY
QueryCredentialsAttributesExA(
    _In_ PCredHandle phCredential,
    _In_ ULONG ulAttribute,
    _Inout_updates_bytes_(cbBuffer) PVOID pBuffer,
    _In_ ULONG cbBuffer);

typedef SECURITY_STATUS
(SEC_ENTRY * QUERY_CREDENTIALS_ATTRIBUTES_EX_FN_A)(
    PCredHandle,
    ULONG,
    PVOID,
    ULONG);

SECURITY_STATUS SEC_ENTRY
QueryCredentialsAttributesExW(
    _In_ PCredHandle phCredential,
    _In_ ULONG ulAttribute,
    _Inout_updates_bytes_(cbBuffer) PVOID pBuffer,
    _In_ ULONG cbBuffer);

typedef SECURITY_STATUS
(SEC_ENTRY * QUERY_CREDENTIALS_ATTRIBUTES_EX_FN_W)(
    PCredHandle,
    ULONG,
    PVOID,
    ULONG);

#ifdef UNICODE
#define QueryCredentialsAttributesEx QueryCredentialsAttributesExW
#define QUERY_CREDENTIALS_ATTRIBUTES_EX_FN QUERY_CREDENTIALS_ATTRIBUTES_EX_FN_W
#else
#define QueryCredentialsAttributesEx QueryCredentialsAttributesExA
#define QUERY_CREDENTIALS_ATTRIBUTES_EX_FN QUERY_CREDENTIALS_ATTRIBUTES_EX_FN_A
#endif

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
QuerySecurityContextToken(
    _In_ PCtxtHandle phContext,
    _Out_ PVOID* Token);

typedef
SECURITY_STATUS
(SEC_ENTRY * QUERY_SECURITY_CONTEXT_TOKEN_FN)(
    PCtxtHandle,
    PVOID*);

SECURITY_STATUS
SEC_ENTRY
QuerySecurityPackageInfoA(
    _In_ LPSTR pszPackageName,
    _Outptr_ PSecPkgInfoA *ppPackageInfo);

typedef
SECURITY_STATUS
(SEC_ENTRY * QUERY_SECURITY_PACKAGE_INFO_FN_A)(
    SEC_CHAR *,
    PSecPkgInfoA *);

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
QuerySecurityPackageInfoW(
    _In_ PSSPI_SEC_STRING pPackageName,
    _Outptr_ PSecPkgInfoW *ppPackageInfo);

typedef
SECURITY_STATUS
(SEC_ENTRY * QUERY_SECURITY_PACKAGE_INFO_FN_W)(
    PSSPI_SEC_STRING,
    PSecPkgInfoW *);

#ifdef UNICODE
#define QuerySecurityPackageInfo QuerySecurityPackageInfoW
#define QUERY_SECURITY_PACKAGE_INFO_FN QUERY_SECURITY_PACKAGE_INFO_FN_W
#else
#define QuerySecurityPackageInfo QuerySecurityPackageInfoA
#define QUERY_SECURITY_PACKAGE_INFO_FN QUERY_SECURITY_PACKAGE_INFO_FN_A
#endif

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
RevertSecurityContext(
    _In_ PCtxtHandle phContext);

typedef
SECURITY_STATUS
(SEC_ENTRY * REVERT_SECURITY_CONTEXT_FN)(
    PCtxtHandle);

SECURITY_STATUS
SEC_ENTRY
SetContextAttributesA(
    _In_ PCtxtHandle phContext,
    _In_ ULONG ulAttribute,
    _In_reads_bytes_(cbBuffer) PVOID pBuffer,
    _In_ ULONG cbBuffer);

typedef
SECURITY_STATUS
(SEC_ENTRY * SET_CONTEXT_ATTRIBUTES_FN_A)(
    PCtxtHandle,
    ULONG,
    PVOID,
    ULONG);

SECURITY_STATUS
SEC_ENTRY
SetContextAttributesW(
    _In_ PCtxtHandle phContext,
    _In_ ULONG ulAttribute,
    _In_reads_bytes_(cbBuffer) PVOID pBuffer,
    _In_ ULONG cbBuffer);

typedef
SECURITY_STATUS
(SEC_ENTRY * SET_CONTEXT_ATTRIBUTES_FN_W)(
    PCtxtHandle,
    ULONG,
    PVOID,
    ULONG);

#ifdef UNICODE
#define SetContextAttributes SetContextAttributesW
#define SET_CONTEXT_ATTRIBUTES_FN SET_CONTEXT_ATTRIBUTES_FN_W
#else
#define SetContextAttributes SetContextAttributesA
#define SET_CONTEXT_ATTRIBUTES_FN SET_CONTEXT_ATTRIBUTES_FN_A
#endif

#if (NTDDI_VERSION > NTDDI_WS03)

SECURITY_STATUS
SEC_ENTRY
SetCredentialsAttributesA(
    _In_ PCredHandle phCredential,
    _In_ ULONG ulAttribute,
    _In_reads_bytes_(cbBuffer) PVOID pBuffer,
    _In_ ULONG cbBuffer
    );

typedef
SECURITY_STATUS
(SEC_ENTRY * SET_CREDENTIALS_ATTRIBUTES_FN_A)(
    PCredHandle,
    ULONG,
    PVOID,
    ULONG);

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
SetCredentialsAttributesW(
    _In_ PCredHandle phCredential,
    _In_ ULONG ulAttribute,
    _In_reads_bytes_(cbBuffer) PVOID pBuffer,
    _In_ ULONG cbBuffer);

typedef
SECURITY_STATUS
(SEC_ENTRY * SET_CREDENTIALS_ATTRIBUTES_FN_W)(
    PCredHandle,
    ULONG,
    PVOID,
    ULONG);

#ifdef UNICODE
#define SetCredentialsAttributes SetCredentialsAttributesW
#define SET_CREDENTIALS_ATTRIBUTES_FN SET_CREDENTIALS_ATTRIBUTES_FN_W
#else
#define SetCredentialsAttributes SetCredentialsAttributesA
#define SET_CREDENTIALS_ATTRIBUTES_FN SET_CREDENTIALS_ATTRIBUTES_FN_A
#endif

#endif /* NTDDI_VERSION > NTDDI_WS03 */

KSECDDDECLSPEC
SECURITY_STATUS
SEC_ENTRY
VerifySignature(
    _In_ PCtxtHandle phContext,
    _In_ PSecBufferDesc pMessage,
    _In_ ULONG MessageSeqNo,
    _Out_ PULONG pfQOP);

typedef
SECURITY_STATUS
(SEC_ENTRY * VERIFY_SIGNATURE_FN)(
    PCtxtHandle,
    PSecBufferDesc,
    ULONG,
    PULONG);

#if (ISSP_MODE == 0)

KSECDDDECLSPEC
NTSTATUS
NTAPI
SecMakeSPN(
    _In_ PUNICODE_STRING ServiceClass,
    _In_ PUNICODE_STRING ServiceName,
    _In_opt_ PUNICODE_STRING InstanceName,
    _In_opt_ USHORT InstancePort,
    _In_opt_ PUNICODE_STRING Referrer,
    _Inout_ PUNICODE_STRING Spn,
    _Out_opt_ PULONG Length,
    _In_ BOOLEAN Allocate);

KSECDDDECLSPEC
NTSTATUS
NTAPI
SecMakeSPNEx(
    _In_ PUNICODE_STRING ServiceClass,
    _In_ PUNICODE_STRING ServiceName,
    _In_opt_ PUNICODE_STRING InstanceName,
    _In_opt_ USHORT InstancePort,
    _In_opt_ PUNICODE_STRING Referrer,
    _In_opt_ PUNICODE_STRING TargetInfo,
    _Inout_ PUNICODE_STRING Spn,
    _Out_ PULONG Length OPTIONAL,
    _In_ BOOLEAN Allocate);

#if (NTDDI_VERSION >= NTDDI_WINXP)

KSECDDDECLSPEC
NTSTATUS
SEC_ENTRY
SecLookupAccountSid(
    _In_ PSID Sid,
    _Out_ PULONG NameSize,
    _Inout_ PUNICODE_STRING NameBuffer,
    _Out_ PULONG DomainSize OPTIONAL,
    _Out_opt_ PUNICODE_STRING DomainBuffer,
    _Out_ PSID_NAME_USE NameUse);

KSECDDDECLSPEC
NTSTATUS
SEC_ENTRY
SecLookupAccountName(
    _In_ PUNICODE_STRING Name,
    _Inout_ PULONG SidSize,
    _Out_ PSID Sid,
    _Out_ PSID_NAME_USE NameUse,
    _Out_opt_ PULONG DomainSize, // WDK says _Out_ only + ... OPTIONAL
    _Inout_opt_ PUNICODE_STRING ReferencedDomain);
#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)
KSECDDDECLSPEC
NTSTATUS
SEC_ENTRY
SecLookupWellKnownSid(
    _In_ WELL_KNOWN_SID_TYPE SidType,
    _Out_ PSID Sid,
    _In_ ULONG SidBufferSize,
    _Inout_opt_ PULONG SidSize);
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
KSECDDDECLSPEC
NTSTATUS
NTAPI
SecMakeSPNEx2(
    _In_ PUNICODE_STRING ServiceClass,
    _In_ PUNICODE_STRING ServiceName,
    _In_opt_ PUNICODE_STRING InstanceName,
    _In_opt_ USHORT InstancePort,
    _In_opt_ PUNICODE_STRING Referrer,
    _In_opt_ PUNICODE_STRING InTargetInfo,
    _Inout_ PUNICODE_STRING Spn,
    _Out_opt_ PULONG TotalSize,
    _In_ BOOLEAN Allocate,
    _In_ BOOLEAN IsTargetInfoMarshaled);
#endif

#endif /* ISSP_MODE == 0 */

#if (NTDDI_VERSION >= NTDDI_WIN7)

SECURITY_STATUS
SEC_ENTRY
SspiEncodeAuthIdentityAsStrings(
    _In_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE pAuthIdentity,
    _Outptr_result_maybenull_ PCWSTR* ppszUserName,
    _Outptr_result_maybenull_ PCWSTR* ppszDomainName,
    _Outptr_opt_result_maybenull_ PCWSTR* ppszPackedCredentialsString);

SECURITY_STATUS
SEC_ENTRY
SspiValidateAuthIdentity(
    _In_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE AuthData);

SECURITY_STATUS
SEC_ENTRY
SspiCopyAuthIdentity(
    _In_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE AuthData,
    _Outptr_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE* AuthDataCopy);

VOID
SEC_ENTRY
SspiFreeAuthIdentity(
    _In_opt_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE AuthData);

VOID
SEC_ENTRY
SspiZeroAuthIdentity(
    _In_opt_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE AuthData);

VOID
SEC_ENTRY
SspiLocalFree(
    _In_opt_ PVOID DataBuffer);

SECURITY_STATUS
SEC_ENTRY
SspiEncodeStringsAsAuthIdentity(
    _In_opt_ PCWSTR pszUserName,
    _In_opt_ PCWSTR pszDomainName,
    _In_opt_ PCWSTR pszPackedCredentialsString,
    _Outptr_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE* ppAuthIdentity);

SECURITY_STATUS
SEC_ENTRY
SspiCompareAuthIdentities(
    _In_opt_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE AuthIdentity1,
    _In_opt_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE AuthIdentity2,
    _Out_opt_ PBOOLEAN SameSuppliedUser,
    _Out_opt_ PBOOLEAN SameSuppliedIdentity);

SECURITY_STATUS
SEC_ENTRY
SspiMarshalAuthIdentity(
    _In_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE AuthIdentity,
    _Out_ PULONG AuthIdentityLength,
    _Outptr_result_bytebuffer_(*AuthIdentityLength) char** AuthIdentityByteArray);

SECURITY_STATUS
SEC_ENTRY
SspiUnmarshalAuthIdentity(
    _In_ ULONG AuthIdentityLength,
    _In_reads_bytes_(AuthIdentityLength) char* AuthIdentityByteArray,
    _Outptr_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE* ppAuthIdentity);

BOOLEAN
SEC_ENTRY
SspiIsPromptingNeeded(
    _In_ ULONG ErrorOrNtStatus);

SECURITY_STATUS
SEC_ENTRY
SspiGetTargetHostName(
    _In_ PCWSTR pszTargetName,
    _Outptr_ PWSTR* pszHostName);

SECURITY_STATUS
SEC_ENTRY
SspiExcludePackage(
    _In_opt_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE AuthIdentity,
    _In_ PCWSTR pszPackageName,
    _Outptr_ PSEC_WINNT_AUTH_IDENTITY_OPAQUE* ppNewAuthIdentity);

#endif /* NTDDI_VERSION >= NTDDI_WIN7 */

#define SEC_WINNT_AUTH_IDENTITY_MARSHALLED 0x04
#define SEC_WINNT_AUTH_IDENTITY_ONLY 0x08

typedef struct _SECURITY_PACKAGE_OPTIONS
{
    ULONG Size;
    ULONG Type;
    ULONG Flags;
    ULONG SignatureSize;
    PVOID Signature;
} SECURITY_PACKAGE_OPTIONS, *PSECURITY_PACKAGE_OPTIONS;

#define SECPKG_OPTIONS_TYPE_UNKNOWN 0
#define SECPKG_OPTIONS_TYPE_LSA     1
#define SECPKG_OPTIONS_TYPE_SSPI    2

#define SECPKG_OPTIONS_PERMANENT 0x00000001

SECURITY_STATUS
SEC_ENTRY
AddSecurityPackageA(
    _In_ LPSTR pszPackageName,
    _In_opt_ PSECURITY_PACKAGE_OPTIONS pOptions);

SECURITY_STATUS
SEC_ENTRY
AddSecurityPackageW(
    _In_ LPWSTR pszPackageName,
    _In_opt_ PSECURITY_PACKAGE_OPTIONS pOptions);

#ifdef UNICODE
#define AddSecurityPackage AddSecurityPackageW
#else
#define AddSecurityPackage AddSecurityPackageA
#endif

SECURITY_STATUS
SEC_ENTRY
DeleteSecurityPackageA(
    _In_ LPSTR pszPackageName);

SECURITY_STATUS
SEC_ENTRY
DeleteSecurityPackageW(
    _In_ LPWSTR pszPackageName);

#ifdef UNICODE
#define DeleteSecurityPackage DeleteSecurityPackageW
#else
#define DeleteSecurityPackage DeleteSecurityPackageA
#endif

#ifdef __cplusplus
}  // extern "C"
#endif
