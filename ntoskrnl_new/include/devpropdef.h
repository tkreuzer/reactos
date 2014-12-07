
/* Do not add #pragma once here! */

#ifndef _DEVPROPDEF_H_
#define _DEVPROPDEF_H_

#define DEVPROPID_FIRST_USABLE 2

#ifndef DEVPROPKEY_DEFINED
#define DEVPROPKEY_DEFINED
typedef GUID DEVPROPGUID, *PDEVPROPGUID;
typedef ULONG DEVPROPID, *PDEVPROPID;
typedef struct _DEVPROPKEY
{
    DEVPROPGUID fmtid;
    DEVPROPID   pid;
} DEVPROPKEY, *PDEVPROPKEY;
#endif /* DEVPROPKEY_DEFINED */

typedef CHAR DEVPROP_BOOLEAN, *PDEVPROP_BOOLEAN;
#define DEVPROP_TRUE  ((DEVPROP_BOOLEAN)-1)
#define DEVPROP_FALSE ((DEVPROP_BOOLEAN) 0)

typedef enum _DEVPROPTYPE
{
    /* Basic types */
    DEVPROP_TYPE_EMPTY                      = 0x00000000,
    DEVPROP_TYPE_NULL                       = 0x00000001,
    DEVPROP_TYPE_SBYTE                      = 0x00000002,
    DEVPROP_TYPE_BYTE                       = 0x00000003,
    DEVPROP_TYPE_INT16                      = 0x00000004,
    DEVPROP_TYPE_UINT16                     = 0x00000005,
    DEVPROP_TYPE_INT32                      = 0x00000006,
    DEVPROP_TYPE_UINT32                     = 0x00000007,
    DEVPROP_TYPE_INT64                      = 0x00000008,
    DEVPROP_TYPE_UINT64                     = 0x00000009,
    DEVPROP_TYPE_FLOAT                      = 0x0000000A,
    DEVPROP_TYPE_DOUBLE                     = 0x0000000B,
    DEVPROP_TYPE_DECIMAL                    = 0x0000000C,
    DEVPROP_TYPE_GUID                       = 0x0000000D,
    DEVPROP_TYPE_CURRENCY                   = 0x0000000E,
    DEVPROP_TYPE_DATE                       = 0x0000000F,
    DEVPROP_TYPE_FILETIME                   = 0x00000010,
    DEVPROP_TYPE_BOOLEAN                    = 0x00000011,
    DEVPROP_TYPE_STRING                     = 0x00000012,
    DEVPROP_TYPE_SECURITY_DESCRIPTOR        = 0x00000013,
    DEVPROP_TYPE_SECURITY_DESCRIPTOR_STRING = 0x00000014,
    DEVPROP_TYPE_DEVPROPKEY                 = 0x00000015,
    DEVPROP_TYPE_DEVPROPTYPE                = 0x00000016,
    DEVPROP_TYPE_ERROR                      = 0x00000017,
    DEVPROP_TYPE_NTSTATUS                   = 0x00000018,
    DEVPROP_TYPE_STRING_INDIRECT            = 0x00000019,

    /* Basic type range */
    MAX_DEVPROP_TYPE                        = 0x00000019,
    DEVPROP_MASK_TYPE                       = 0x00000FFF,

    /* Type modifiers */
    DEVPROP_TYPEMOD_ARRAY                   = 0x00001000,
    DEVPROP_TYPEMOD_LIST                    = 0x00002000,
    MAX_DEVPROP_TYPEMOD                     = 0x00002000,
    DEVPROP_MASK_TYPEMOD                    = 0x0000F000,

    /* Derived types */
    DEVPROP_TYPE_STRING_LIST = (DEVPROP_TYPE_STRING|DEVPROP_TYPEMOD_LIST),
    DEVPROP_TYPE_BINARY      = (DEVPROP_TYPE_BYTE|DEVPROP_TYPEMOD_ARRAY),

} DEVPROPTYPE, *PDEVPROPTYPE;

typedef
#ifdef MIDL_PASS
[v1_enum]
#endif
enum _DEVPROPSTORE
{
    DEVPROP_STORE_SYSTEM,
    DEVPROP_STORE_USER
} DEVPROPSTORE, *PDEVPROPSTORE;

typedef struct _DEVPROPCOMPKEY
{
    DEVPROPKEY Key;
    DEVPROPSTORE Store;
#ifdef MIDL_PASS
    [string] wchar_t *LocaleName;
#else
    PCWSTR LocaleName;
#endif
} DEVPROPCOMPKEY, *PDEVPROPCOMPKEY;

typedef struct _DEVPROPERTY
{
    DEVPROPCOMPKEY CompKey;
    DEVPROPTYPE Type;
    ULONG BufferSize;
#ifdef MIDL_PASS
    [size_is(BufferSize)] BYTE *Buffer;
#else
    _Field_size_bytes_opt_(BufferSize) PVOID Buffer;
#endif
} DEVPROPERTY, *PDEVPROPERTY;

#ifndef IsEqualDevPropKey
#ifdef __cplusplus
#define IsEqualDevPropKey(a, b) (((a).pid == (b).pid) && IsEqualGUID((a).fmtid, (b).fmtid))
#ifdef _SYS_GUID_OPERATOR_EQ_
extern "C++"
inline
bool
operator==(
    const DEVPROPKEY &a,
    const DEVPROPKEY &b)
{
    return ((a.pid == b.pid) && (a.fmtid == b.fmtid));
}

extern "C++"
inline
bool
operator!=(
    const DEVPROPKEY &a,
    const DEVPROPKEY &b)
{
    return !(a == b);
}
#endif // _SYS_GUID_OPERATOR_EQ_

#else // !__cplusplus

#define IsEqualDevPropKey(a, b) \
    (((a).pid == (b).pid) && IsEqualGUID(&(a).fmtid, &(b).fmtid))

#endif // __cplusplus
#endif // !IsEqualDevPropKey

#ifndef IsEqualLocaleName

#define IsEqualLocaleName(a, b) \
    (((a) == (b)) || \
     (((a) != NULL) && ((b) != NULL) && (_wcsicmp((a), (b)) == 0)))

#endif

#ifndef IsEqualDevPropCompKey

#define IsEqualDevPropCompKey(a, b) \
    (IsEqualDevPropKey((a).Key, (b).Key) && \
     ((a).Store == (b).Store) && \
     IsEqualLocaleName((a).LocaleName, (b).LocaleName))

#if defined(__cplusplus) && defined(_SYS_GUID_OPERATOR_EQ_)
extern "C++"
inline
bool
operator==(
    const DEVPROPCOMPKEY &a,
    const DEVPROPCOMPKEY &b)
{
    return ((a.Key == b.Key) && (a.Store == b.Store) &&
            IsEqualLocaleName(a.LocaleName, b.LocaleName));
}

extern "C++"
inline
bool
operator!=(
    const DEVPROPCOMPKEY &a,
    const DEVPROPCOMPKEY &b)
{
    return !(a == b);
}
#endif // defined(__cplusplus) && defined(_SYS_GUID_OPERATOR_EQ_)
#endif // !IsEqualDevPropCompKey

#endif // _DEVPROPDEF_H_

#ifdef DEFINE_DEVPROPKEY
#undef DEFINE_DEVPROPKEY
#endif
#ifdef INITGUID
#define DEFINE_DEVPROPKEY(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8, pid) EXTERN_C const DEVPROPKEY DECLSPEC_SELECTANY name = { { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }, pid }
#else
#define DEFINE_DEVPROPKEY(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8, pid) EXTERN_C const DEVPROPKEY name
#endif // INITGUID

