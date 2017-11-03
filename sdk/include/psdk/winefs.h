/*
 * PROJECT:         ReactOS PSDK
 * COPYRIGHT:       This file is in the Public Domain.
 * FILE:            include/psdk/winefs.h
 */

#pragma once
#define __WINEFS_H__

#if defined(MIDL_PASS) && !defined(MIDL_PROP)
#define MIDL_PROP(x) x
#else
#define MIDL_PROP(x)
#endif // MIDL_PASS

#ifndef ALGIDDEF
#define ALGIDDEF
typedef unsigned int ALG_ID;
#endif

typedef struct _CERTIFICATE_BLOB
{
    DWORD   dwCertEncodingType;
    MIDL_PROP([range(0,32768)]) DWORD cbData;
    MIDL_PROP([size_is(cbData)]) PBYTE pbData;
} EFS_CERTIFICATE_BLOB, *PEFS_CERTIFICATE_BLOB;

typedef struct _EFS_HASH_BLOB
{
    MIDL_PROP([range(0,100)]) DWORD cbData;
    MIDL_PROP([size_is(cbData)]) PBYTE pbData;
} EFS_HASH_BLOB, *PEFS_HASH_BLOB;

typedef struct _EFS_RPC_BLOB
{
    MIDL_PROP([range(0,266240)]) DWORD cbData;
    MIDL_PROP([size_is(cbData)]) PBYTE pbData;
} EFS_RPC_BLOB, *PEFS_RPC_BLOB;

typedef struct _EFS_KEY_INFO
{
    DWORD dwVersion;
    ULONG Entropy;
    ALG_ID Algorithm;
    ULONG KeyLength;
} EFS_KEY_INFO, *PEFS_KEY_INFO;

typedef struct _ENCRYPTION_CERTIFICATE
{
    DWORD cbTotalLength;
    SID* pUserSid;
    PEFS_CERTIFICATE_BLOB pCertBlob;
} ENCRYPTION_CERTIFICATE, *PENCRYPTION_CERTIFICATE;

#define MAX_SID_SIZE 256

typedef struct _ENCRYPTION_CERTIFICATE_HASH
{
    DWORD cbTotalLength;
    SID * pUserSid;
    PEFS_HASH_BLOB  pHash;
    MIDL_PROP([string]) LPWSTR lpDisplayInformation;
} ENCRYPTION_CERTIFICATE_HASH, *PENCRYPTION_CERTIFICATE_HASH;

typedef struct _ENCRYPTION_CERTIFICATE_LIST
{
    MIDL_PROP([range(0,500)]) DWORD nUsers;
    MIDL_PROP([size_is(nUsers)]) PENCRYPTION_CERTIFICATE * pUsers;
} ENCRYPTION_CERTIFICATE_LIST, *PENCRYPTION_CERTIFICATE_LIST;

typedef struct _ENCRYPTION_CERTIFICATE_HASH_LIST
{
    MIDL_PROP([range(0,500)]) DWORD nCert_Hash;
    MIDL_PROP([size_is(nCert_Hash)]) PENCRYPTION_CERTIFICATE_HASH * pUsers;
} ENCRYPTION_CERTIFICATE_HASH_LIST, *PENCRYPTION_CERTIFICATE_HASH_LIST;

#if (NTDDI_VERSION >= NTDDI_VISTA)

typedef struct _EFS_PIN_BLOB
{
    MIDL_PROP([range(0,8)]) DWORD cbPadding; 
    MIDL_PROP([range(0,2048)]) DWORD cbData;
    MIDL_PROP([size_is(cbData+cbPadding)]) PBYTE pbData;
} EFS_PIN_BLOB, *PEFS_PIN_BLOB;

typedef struct _EFS_DECRYPTION_STATUS_INFO
{
    DWORD dwDecryptionError;
    DWORD dwHashOffset;
    DWORD cbHash;
} EFS_DECRYPTION_STATUS_INFO, *PEFS_DECRYPTION_STATUS_INFO;

typedef struct _EFS_ENCRYPTION_STATUS_INFO
{
    BOOL bHasCurrentKey;
    DWORD dwEncryptionError;
} EFS_ENCRYPTION_STATUS_INFO, *PEFS_ENCRYPTION_STATUS_INFO;

#define EFS_METADATA_ADD_USER     0x00000001
#define EFS_METADATA_REMOVE_USER  0x00000002
#define EFS_METADATA_REPLACE_USER 0x00000004
#define EFS_METADATA_GENERAL_OP   0x00000008

typedef struct _ENCRYPTED_FILE_METADATA_SIGNATURE
{
    DWORD dwEfsAccessType;
    PENCRYPTION_CERTIFICATE_HASH_LIST pCertificatesAdded;
    PENCRYPTION_CERTIFICATE pEncryptionCertificate;
    PEFS_RPC_BLOB pEfsStreamSignature;
} ENCRYPTED_FILE_METADATA_SIGNATURE, *PENCRYPTED_FILE_METADATA_SIGNATURE;

#endif // (NTDDI_VERSION >= NTDDI_VISTA)

#if (NTDDI_VERSION >= NTDDI_WIN7)

typedef struct _EFS_COMPATIBILITY_INFO
{
    DWORD EfsVersion;
} EFS_COMPATIBILITY_INFO, *PEFS_COMPATIBILITY_INFO;

#endif // (NTDDI_VERSION >= NTDDI_WIN7)

#if (NTDDI_VERSION >= NTDDI_WIN8)

typedef struct _ENCRYPTION_PROTECTOR
{
    DWORD cbTotalLength;
    SID * pUserSid;
    MIDL_PROP([string]) LPWSTR lpProtectorDescriptor;
} ENCRYPTION_PROTECTOR, *PENCRYPTION_PROTECTOR;

typedef struct _ENCRYPTION_PROTECTOR_LIST
{
    DWORD nProtectors;
    MIDL_PROP([size_is(nProtectors)]) PENCRYPTION_PROTECTOR *pProtectors;
} ENCRYPTION_PROTECTOR_LIST, *PENCRYPTION_PROTECTOR_LIST;

#endif // (NTDDI_VERSION >= NTDDI_WIN8)

#if (NTDDI_VERSION >= NTDDI_WINBLUE)

#define EFS_COMPATIBILITY_VERSION_NCRYPT_PROTECTOR 5

#endif // #if (NTDDI_VERSION >= NTDDI_WINBLUE)

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

#define EFS_COMPATIBILITY_VERSION_PFILE_PROTECTOR 6

#define EFS_IS_DESCRIPTOR_VERSION(v) \
    (((v) == EFS_COMPATIBILITY_VERSION_NCRYPT_PROTECTOR) || \
     ((v) == EFS_COMPATIBILITY_VERSION_PFILE_PROTECTOR))

#define EFS_SUBVER_UNKNOWN      0
#define EFS_EFS_SUBVER_EFS_CERT 1
#define EFS_PFILE_SUBVER_RMS    2
#define EFS_PFILE_SUBVER_APPX   3

typedef struct _EFS_VERSION_INFO
{
    DWORD EfsVersion;
    DWORD SubVersion;
} EFS_VERSION_INFO, *PEFS_VERSION_INFO;

#define EFS_IS_APPX_VERSION(v, subV) \
    (((v) == EFS_COMPATIBILITY_VERSION_PFILE_PROTECTOR) && \
     ((subV) == EFS_PFILE_SUBVER_APPX))

#endif // #if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

WINADVAPI
DWORD
WINAPI
AddUsersToEncryptedFile(
    _In_ LPCWSTR lpFileName,
    _In_ PENCRYPTION_CERTIFICATE_LIST pEncryptionCertificates);

WINADVAPI
DWORD
WINAPI
RemoveUsersFromEncryptedFile(
    _In_ LPCWSTR lpFileName,
    _In_ PENCRYPTION_CERTIFICATE_HASH_LIST pHashes);

WINADVAPI
BOOL
WINAPI
EncryptionDisable(
    _In_ LPCWSTR DirPath,
    _In_ BOOL Disable);

WINADVAPI
DWORD
WINAPI
QueryUsersOnEncryptedFile(
    _In_ LPCWSTR lpFileName,
    _Outptr_ PENCRYPTION_CERTIFICATE_HASH_LIST *pUsers);

WINADVAPI
VOID
WINAPI
FreeEncryptionCertificateHashList(
    _In_ PENCRYPTION_CERTIFICATE_HASH_LIST pUsers);

WINADVAPI
DWORD
WINAPI
QueryRecoveryAgentsOnEncryptedFile(
    _In_ LPCWSTR lpFileName,
    _Outptr_ PENCRYPTION_CERTIFICATE_HASH_LIST *pRecoveryAgents);

#if (NTDDI_VERSION >= NTDDI_WS03)

WINADVAPI
DWORD
WINAPI
DuplicateEncryptionInfoFile(
    _In_ LPCWSTR SrcFileName,
    _In_ LPCWSTR DstFileName, 
    _In_ DWORD dwCreationDistribution, 
    _In_ DWORD dwAttributes, 
    _In_opt_ CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes);

#elif (NTDDI_VERSION >= NTDDI_WINXP)

WINADVAPI
DWORD
WINAPI
DuplicateEncryptionInfoFile(
    _In_ LPCWSTR SrcFileName,
    _In_ LPCWSTR DstFileName, 
    _In_ DWORD dwCreationDistribution, 
    _In_ DWORD dwAttributes, 
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes);

#endif // (NTDDI_VERSION >= NTDDI_WINXP)

#if (NTDDI_VERSION >= NTDDI_VISTA)

WINADVAPI
DWORD
WINAPI
SetUserFileEncryptionKey(
    _In_opt_ PENCRYPTION_CERTIFICATE pEncryptionCertificate);

#else // (NTDDI_VERSION >= NTDDI_VISTA)

WINADVAPI
DWORD
WINAPI
SetUserFileEncryptionKey(
    _In_ PENCRYPTION_CERTIFICATE pEncryptionCertificate);

#endif // (NTDDI_VERSION >= NTDDI_VISTA) 

#if (NTDDI_VERSION >= NTDDI_VISTA)

WINADVAPI
DWORD
WINAPI
SetUserFileEncryptionKeyEx(
    _In_opt_ PENCRYPTION_CERTIFICATE pEncryptionCertificate,
    _In_ DWORD dwCapabilities, 
    _In_ DWORD dwFlags,
    _Reserved_ LPVOID pvReserved);

__declspec(deprecated)
WINADVAPI
DWORD
WINAPI
GetEncryptedFileMetadata(
    _In_ LPCWSTR lpFileName,
    _Out_ PDWORD pcbMetadata, 
    _Outptr_result_bytebuffer_(*pcbMetadata) PBYTE *ppbMetadata);

__declspec(deprecated)
WINADVAPI
DWORD
WINAPI
SetEncryptedFileMetadata(
    _In_ LPCWSTR lpFileName,
    _In_opt_ PBYTE pbOldMetadata,
    _In_ PBYTE pbNewMetadata,
    _In_ PENCRYPTION_CERTIFICATE_HASH pOwnerHash,
    _In_ DWORD dwOperation,
    _In_opt_ PENCRYPTION_CERTIFICATE_HASH_LIST pCertificatesAdded); 
    
__declspec(deprecated)
WINADVAPI
VOID
WINAPI
FreeEncryptedFileMetadata(
    _In_ PBYTE pbMetadata); 

#endif // #if (NTDDI_VERSION >= NTDDI_VISTA)


