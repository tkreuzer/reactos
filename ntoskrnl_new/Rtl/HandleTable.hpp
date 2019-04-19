
#pragma once

#include "Rtl.hpp"

typedef struct _HANDLE_TABLE_ENTRY_INFO
{
    ULONG AuditMask;
} HANDLE_TABLE_ENTRY_INFO, *PHANDLE_TABLE_ENTRY_INFO;

typedef union _HANDLE_TABLE_ENTRY
{
    LONG_PTR VolatileLowValue;
    struct
    {
        LONG_PTR LowValue;
        LONG_PTR HighValue;
    };
    struct
    {
        PHANDLE_TABLE_ENTRY_INFO InfoTable;
        union
        {
            union _HANDLE_TABLE_ENTRY* NextFreeHandleEntry;
            EXHANDLE LeafHandleValue;
        };
    };
#ifdef _WIN64
    LONG64 RefCountField;
#endif // _WIN64
    struct
    {
        ULONG_PTR Unlocked : 1;
        ULONG_PTR RefCnt : 16;
        ULONG_PTR Attributes : 3;
        ULONG_PTR ObjectPointerBits : 44;
#ifndef _WIN64
        LONG RefCountField;
#endif // _WIN64
        ULONG32 GrantedAccessBits : 25;
        ULONG32 NoRightsUpgrade : 1;
        ULONG32 Spare1 : 6;
        ULONG32 Spare2;
    };
} HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY;

typedef struct _HANDLE_TABLE_FREE_LIST               // 6 elements, 0x40 bytes (sizeof)
{
/*0x000*/     struct _EX_PUSH_LOCK FreeListLock;               // 7 elements, 0x8 bytes (sizeof)
/*0x008*/     union _HANDLE_TABLE_ENTRY* FirstFreeHandleEntry;
/*0x010*/     union _HANDLE_TABLE_ENTRY* LastFreeHandleEntry;
/*0x018*/     LONG32       HandleCount;
/*0x01C*/     ULONG32      HighWaterMark;
/*0x020*/     ULONG32      Reserved[8];
} HANDLE_TABLE_FREE_LIST, *PHANDLE_TABLE_FREE_LIST;

typedef struct _HANDLE_TRACE_DB_ENTRY // 4 elements, 0xA0 bytes (sizeof)
{
/*0x000*/     struct _CLIENT_ID ClientId;       // 2 elements, 0x10 bytes (sizeof)
/*0x010*/     VOID*        Handle;
/*0x018*/     ULONG32      Type;
/*0x01C*/     UINT8        _PADDING0_[0x4];
/*0x020*/     VOID*        StackTrace[16];
} HANDLE_TRACE_DB_ENTRY, *PHANDLE_TRACE_DB_ENTRY;

typedef struct _HANDLE_TRACE_DEBUG_INFO       // 6 elements, 0xF0 bytes (sizeof)
{
/*0x000*/     LONG32       RefCount;
/*0x004*/     ULONG32      TableSize;
/*0x008*/     ULONG32      BitMaskFlags;
/*0x00C*/     UINT8        _PADDING0_[0x4];
/*0x010*/     struct _FAST_MUTEX CloseCompactionLock;   // 5 elements, 0x38 bytes (sizeof)
/*0x048*/     ULONG32      CurrentStackIndex;
/*0x04C*/     UINT8        _PADDING1_[0x4];
/*0x050*/     HANDLE_TRACE_DB_ENTRY TraceDb[1];
} HANDLE_TRACE_DEBUG_INFO, *PHANDLE_TRACE_DEBUG_INFO;

typedef struct _HANDLE_TABLE
{
    ULONG32      NextHandleNeedingPool;
    LONG32       ExtraInfoPages;
    UINT64       TableCode;
    struct _EPROCESS* QuotaProcess;
/*0x018*/     struct _LIST_ENTRY HandleTableList;
/*0x028*/     ULONG32      UniqueProcessId;
              union
              {
/*0x02C*/         ULONG32      Flags;
                  struct
                  {
/*0x02C*/             UINT8        StrictFIFO : 1;
/*0x02C*/             UINT8        EnableHandleExceptions : 1;
/*0x02C*/             UINT8        Rundown : 1;
/*0x02C*/             UINT8        Duplicated : 1;
/*0x02C*/             UINT8        RaiseUMExceptionOnInvalidHandleClose : 1;
                  };
              };
/*0x030*/     struct _EX_PUSH_LOCK HandleContentionEvent;
/*0x038*/     struct _EX_PUSH_LOCK HandleTableLock;
              union
              {
/*0x040*/         struct _HANDLE_TABLE_FREE_LIST FreeLists[1];
                  struct
                  {
/*0x040*/             UINT8        ActualEntry[32];
/*0x060*/             struct _HANDLE_TRACE_DEBUG_INFO* DebugInfo;
/*0x068*/             UINT8        _PADDING0_[0x18];
                  };
              };
} HANDLE_TABLE, *PHANDLE_TABLE;

