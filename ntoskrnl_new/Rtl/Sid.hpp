
#pragma once

#include "Rtl.hpp"

typedef struct _SID_IDENTIFIER_AUTHORITY
{
    UCHAR Value[6];
} SID_IDENTIFIER_AUTHORITY, *PSID_IDENTIFIER_AUTHORITY;

typedef struct _SID
{
   UCHAR Revision;
   UCHAR SubAuthorityCount;
   SID_IDENTIFIER_AUTHORITY IdentifierAuthority;
#ifdef MIDL_PASS
   [size_is(SubAuthorityCount)] ULONG SubAuthority[*];
#else // MIDL_PASS
   ULONG SubAuthority[ANYSIZE_ARRAY];
#endif // MIDL_PASS
} SID, *PSID, *PISID;

// ntifs.h
typedef struct _SID_AND_ATTRIBUTES
{
    PSID Sid;
    ULONG Attributes;
} SID_AND_ATTRIBUTES, * PSID_AND_ATTRIBUTES;

typedef SID_AND_ATTRIBUTES SID_AND_ATTRIBUTES_ARRAY[ANYSIZE_ARRAY];
typedef SID_AND_ATTRIBUTES_ARRAY *PSID_AND_ATTRIBUTES_ARRAY;

// ntifs.h
#define SID_HASH_SIZE 32
typedef ULONG_PTR SID_HASH_ENTRY, *PSID_HASH_ENTRY;
typedef struct _SID_AND_ATTRIBUTES_HASH
{
    ULONG SidCount;
    PSID_AND_ATTRIBUTES SidAttr;
    SID_HASH_ENTRY Hash[SID_HASH_SIZE];
} SID_AND_ATTRIBUTES_HASH, *PSID_AND_ATTRIBUTES_HASH;

