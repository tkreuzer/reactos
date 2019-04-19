
extern BOOLEAN NLS_MB_CODE_PAGE_TAG;
extern BOOLEAN NLS_MB_OEM_CODE_PAGE_TAG;


#define SHORT_SIZE  (sizeof(USHORT))
#define SHORT_MASK  (SHORT_SIZE - 1)
#define LONG_SIZE       (sizeof(LONG))
#define LONGLONG_SIZE   (sizeof(LONGLONG))
#define LONG_MASK       (LONG_SIZE - 1)
#define LONGLONG_MASK   (LONGLONG_SIZE - 1)
#define LOWBYTE_MASK 0x00FF

#define FIRSTBYTE(VALUE)  ((VALUE) & LOWBYTE_MASK)
#define SECONDBYTE(VALUE) (((VALUE) >> 8) & LOWBYTE_MASK)
#define THIRDBYTE(VALUE)  (((VALUE) >> 16) & LOWBYTE_MASK)
#define FOURTHBYTE(VALUE) (((VALUE) >> 24) & LOWBYTE_MASK)

#define SHORT_LEAST_SIGNIFICANT_BIT  0
#define SHORT_MOST_SIGNIFICANT_BIT   1

#define LONG_LEAST_SIGNIFICANT_BIT       0
#define LONG_3RD_MOST_SIGNIFICANT_BIT    1
#define LONG_2ND_MOST_SIGNIFICANT_BIT    2
#define LONG_MOST_SIGNIFICANT_BIT        3

#if defined(_AMD64_)
 #define RtlStoreUshort(ADDRESS,VALUE)                           \
        *(USHORT UNALIGNED *)(ADDRESS) = (VALUE)
#else
 #define RtlStoreUshort(ADDRESS,VALUE)                     \
         if ((ULONG_PTR)(ADDRESS) & SHORT_MASK) {         \
             ((PUCHAR) (ADDRESS))[SHORT_LEAST_SIGNIFICANT_BIT] = (UCHAR)(FIRSTBYTE(VALUE));    \
             ((PUCHAR) (ADDRESS))[SHORT_MOST_SIGNIFICANT_BIT ] = (UCHAR)(SECONDBYTE(VALUE));   \
         }                                                \
         else {                                           \
             *((PUSHORT) (ADDRESS)) = (USHORT) VALUE;     \
         }
#endif

#if defined(_AMD64_)
 #define RtlStoreUlong(ADDRESS,VALUE)                        \
        *(ULONG UNALIGNED *)(ADDRESS) = (VALUE)
#else
 #define RtlStoreUlong(ADDRESS,VALUE)                      \
         if ((ULONG_PTR)(ADDRESS) & LONG_MASK) {          \
             ((PUCHAR) (ADDRESS))[LONG_LEAST_SIGNIFICANT_BIT      ] = (UCHAR)(FIRSTBYTE(VALUE));    \
             ((PUCHAR) (ADDRESS))[LONG_3RD_MOST_SIGNIFICANT_BIT   ] = (UCHAR)(SECONDBYTE(VALUE));   \
             ((PUCHAR) (ADDRESS))[LONG_2ND_MOST_SIGNIFICANT_BIT   ] = (UCHAR)(THIRDBYTE(VALUE));    \
             ((PUCHAR) (ADDRESS))[LONG_MOST_SIGNIFICANT_BIT       ] = (UCHAR)(FOURTHBYTE(VALUE));   \
         }                                                \
         else {                                           \
             *((PULONG) (ADDRESS)) = (ULONG) (VALUE);     \
         }
#endif

#if defined(_AMD64_)
#define RtlStoreUlonglong(ADDRESS,VALUE)                        \
        *(ULONGLONG UNALIGNED *)(ADDRESS) = (VALUE)
#else
#define RtlStoreUlonglong(ADDRESS,VALUE)                        \
         if ((ULONG_PTR)(ADDRESS) & LONGLONG_MASK) {            \
             RtlStoreUlong((ULONG_PTR)(ADDRESS),                \
                           (ULONGLONG)(VALUE) & 0xFFFFFFFF);    \
             RtlStoreUlong((ULONG_PTR)(ADDRESS)+sizeof(ULONG),  \
                           (ULONGLONG)(VALUE) >> 32);           \
         } else {                                               \
             *((PULONGLONG)(ADDRESS)) = (ULONGLONG)(VALUE);     \
         }
#endif

#ifdef _WIN64
#define RtlStoreUlongPtr(ADDRESS,VALUE)                         \
         RtlStoreUlonglong(ADDRESS,VALUE)
#else
#define RtlStoreUlongPtr(ADDRESS,VALUE)                         \
         RtlStoreUlong(ADDRESS,VALUE)
#endif

#if defined(_AMD64_)
#define RtlRetrieveUshort(DEST_ADDRESS,SRC_ADDRESS)                     \
         *(USHORT UNALIGNED *)(DEST_ADDRESS) = *(PUSHORT)(SRC_ADDRESS)
#else
#define RtlRetrieveUshort(DEST_ADDRESS,SRC_ADDRESS)                   \
         if ((ULONG_PTR)SRC_ADDRESS & SHORT_MASK) {                       \
             ((PUCHAR) (DEST_ADDRESS))[0] = ((PUCHAR) (SRC_ADDRESS))[0];  \
             ((PUCHAR) (DEST_ADDRESS))[1] = ((PUCHAR) (SRC_ADDRESS))[1];  \
         }                                                            \
         else {                                                       \
             *((PUSHORT) DEST_ADDRESS) = *((PUSHORT) SRC_ADDRESS);    \
         }                                                            \
#endif

#if defined(_AMD64_)
#define RtlRetrieveUlong(DEST_ADDRESS,SRC_ADDRESS)                     \
         *(ULONG UNALIGNED *)(DEST_ADDRESS) = *(PULONG)(SRC_ADDRESS)
#else
#define RtlRetrieveUlong(DEST_ADDRESS,SRC_ADDRESS)                    \
         if ((ULONG_PTR)SRC_ADDRESS & LONG_MASK) {                        \
             ((PUCHAR) (DEST_ADDRESS))[0] = ((PUCHAR) (SRC_ADDRESS))[0];  \
             ((PUCHAR) (DEST_ADDRESS))[1] = ((PUCHAR) (SRC_ADDRESS))[1];  \
             ((PUCHAR) (DEST_ADDRESS))[2] = ((PUCHAR) (SRC_ADDRESS))[2];  \
             ((PUCHAR) (DEST_ADDRESS))[3] = ((PUCHAR) (SRC_ADDRESS))[3];  \
         }                                                            \
         else {                                                       \
             *((PULONG) DEST_ADDRESS) = *((PULONG) SRC_ADDRESS);      \
         }
#endif


#define RtlIsZeroLuid(L1) ((BOOLEAN) (((L1)->LowPart | (L1)->HighPart) == 0))

typedef struct _OSVERSIONINFOA {
    ULONG dwOSVersionInfoSize;
    ULONG dwMajorVersion;
    ULONG dwMinorVersion;
    ULONG dwBuildNumber;
    ULONG dwPlatformId;
    CHAR   szCSDVersion[128];
} OSVERSIONINFOA, *POSVERSIONINFOA, *LPOSVERSIONINFOA;

typedef struct _OSVERSIONINFOEXA {
    ULONG dwOSVersionInfoSize;
    ULONG dwMajorVersion;
    ULONG dwMinorVersion;
    ULONG dwBuildNumber;
    ULONG dwPlatformId;
    CHAR   szCSDVersion[128];
    USHORT wServicePackMajor;
    USHORT wServicePackMinor;
    USHORT wSuiteMask;
    UCHAR wProductType;
    UCHAR wReserved;
} OSVERSIONINFOEXA, *POSVERSIONINFOEXA, *LPOSVERSIONINFOEXA;

#define RtlInterlockedSetBits(Flags, Flag) \
    InterlockedOr((PLONG)(Flags), Flag)

#define RtlInterlockedAndBits(Flags, Flag) \
    InterlockedAnd((PLONG)(Flags), Flag)

#define RtlInterlockedClearBits(Flags, Flag) \
    RtlInterlockedAndBits(Flags, ~(Flag))

#define RtlInterlockedXorBits(Flags, Flag) \
    InterlockedXor(Flags, Flag)

#define RtlInterlockedSetBitsDiscardReturn(Flags, Flag) \
    (VOID) RtlInterlockedSetBits(Flags, Flag)

#define RtlInterlockedAndBitsDiscardReturn(Flags, Flag) \
    (VOID) RtlInterlockedAndBits(Flags, Flag)

#define RtlInterlockedClearBitsDiscardReturn(Flags, Flag) \
    RtlInterlockedAndBitsDiscardReturn(Flags, ~(Flag))

#define CTMF_INCLUDE_APPCONTAINER   0x00000001UL
#define CTMF_VALID_FLAGS            (CTMF_INCLUDE_APPCONTAINER)


#define RTL_STACK_WALKING_MODE_FRAMES_TO_SKIP_SHIFT     8

/// ntifs.h

#define RtlOffsetToPointer(B,O)  ((PCHAR)( ((PCHAR)(B)) + ((ULONG_PTR)(O))  ))
#define RtlPointerToOffset(B,P)  ((ULONG)( ((PCHAR)(P)) - ((PCHAR)(B))  ))

#define MAX_UNICODE_STACK_BUFFER_LENGTH 256

#define RTL_SYSTEM_VOLUME_INFORMATION_FOLDER    L"System Volume Information"


