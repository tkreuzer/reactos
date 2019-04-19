          typedef union _LARGE_INTEGER   // 4 elements, 0x8 bytes (sizeof)
          {
              struct                     // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         ULONG32      LowPart;
/*0x004*/         LONG32       HighPart;
              };
              struct                     // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         ULONG32      LowPart;
/*0x004*/         LONG32       HighPart;
              }u;
/*0x000*/     INT64        QuadPart;
          }LARGE_INTEGER, *PLARGE_INTEGER;

          typedef struct _LIST_ENTRY     // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _LIST_ENTRY* Flink;
/*0x008*/     struct _LIST_ENTRY* Blink;
          }LIST_ENTRY, *PLIST_ENTRY;

          typedef struct _M128A  // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       Low;
/*0x008*/     INT64        High;
          }M128A, *PM128A;

          typedef struct _SINGLE_LIST_ENTRY    // 1 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     struct _SINGLE_LIST_ENTRY* Next;
          }SINGLE_LIST_ENTRY, *PSINGLE_LIST_ENTRY;

          typedef struct _SINGLE_LIST_ENTRY32 // 1 elements, 0x4 bytes (sizeof)
          {
/*0x000*/     ULONG32      Next;
          }SINGLE_LIST_ENTRY32, *PSINGLE_LIST_ENTRY32;

          typedef struct _SLIST_ENTRY       // 1 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     struct _SLIST_ENTRY* Next;
/*0x008*/     UINT8        _PADDING0_[0x8];
          }SLIST_ENTRY, *PSLIST_ENTRY;

          typedef union _SLIST_HEADER              // 4 elements, 0x10 bytes (sizeof)
          {
              struct                               // 2 elements, 0x10 bytes (sizeof)
              {
/*0x000*/         UINT64       Alignment;
/*0x008*/         UINT64       Region;
              };
              struct                               // 7 elements, 0x10 bytes (sizeof)
              {
                  struct                           // 3 elements, 0x8 bytes (sizeof)
                  {
/*0x000*/             UINT64       Depth : 16;     // 0 BitPosition
/*0x000*/             UINT64       Sequence : 9;   // 16 BitPosition
/*0x000*/             UINT64       NextEntry : 39; // 25 BitPosition
                  };
                  struct                           // 4 elements, 0x8 bytes (sizeof)
                  {
/*0x008*/             UINT64       HeaderType : 1; // 0 BitPosition
/*0x008*/             UINT64       Init : 1;       // 1 BitPosition
/*0x008*/             UINT64       Reserved : 59;  // 2 BitPosition
/*0x008*/             UINT64       Region : 3;     // 61 BitPosition
                  };
              }Header8;
              struct                               // 5 elements, 0x10 bytes (sizeof)
              {
                  struct                           // 2 elements, 0x8 bytes (sizeof)
                  {
/*0x000*/             UINT64       Depth : 16;     // 0 BitPosition
/*0x000*/             UINT64       Sequence : 48;  // 16 BitPosition
                  };
                  struct                           // 3 elements, 0x8 bytes (sizeof)
                  {
/*0x008*/             UINT64       HeaderType : 1; // 0 BitPosition
/*0x008*/             UINT64       Reserved : 3;   // 1 BitPosition
/*0x008*/             UINT64       NextEntry : 60; // 4 BitPosition
                  };
              }HeaderX64;
          }SLIST_HEADER, *PSLIST_HEADER;


          typedef struct _STRING            // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT16       Length;
/*0x002*/     UINT16       MaximumLength;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     CHAR*        Buffer;
          }STRING, *PSTRING;

          typedef struct _STRING32        // 3 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     UINT16       Length;
/*0x002*/     UINT16       MaximumLength;
/*0x004*/     ULONG32      Buffer;
          }STRING32, *PSTRING32;

          typedef struct _STRING64          // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT16       Length;
/*0x002*/     UINT16       MaximumLength;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     UINT64       Buffer;
          }STRING64, *PSTRING64;

          typedef struct _TIME_FIELDS    // 8 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     INT16        Year;
/*0x002*/     INT16        Month;
/*0x004*/     INT16        Day;
/*0x006*/     INT16        Hour;
/*0x008*/     INT16        Minute;
/*0x00A*/     INT16        Second;
/*0x00C*/     INT16        Milliseconds;
/*0x00E*/     INT16        Weekday;
          }TIME_FIELDS, *PTIME_FIELDS;

          typedef union _ULARGE_INTEGER  // 4 elements, 0x8 bytes (sizeof)
          {
              struct                     // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         ULONG32      LowPart;
/*0x004*/         ULONG32      HighPart;
              };
              struct                     // 2 elements, 0x8 bytes (sizeof)
              {
/*0x000*/         ULONG32      LowPart;
/*0x004*/         ULONG32      HighPart;
              }u;
/*0x000*/     UINT64       QuadPart;
          }ULARGE_INTEGER, *PULARGE_INTEGER;

          typedef struct _UNICODE_STRING    // 3 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT16       Length;
/*0x002*/     UINT16       MaximumLength;
/*0x004*/     UINT8        _PADDING0_[0x4];
/*0x008*/     UINT16*      Buffer;
          }UNICODE_STRING, *PUNICODE_STRING;

          typedef struct _LIST_ENTRY32 // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      Flink;
/*0x004*/     ULONG32      Blink;
          }LIST_ENTRY32, *PLIST_ENTRY32;

          typedef struct _LIST_ENTRY64 // 2 elements, 0x10 bytes (sizeof)
          {
/*0x000*/     UINT64       Flink;
/*0x008*/     UINT64       Blink;
          }LIST_ENTRY64, *PLIST_ENTRY64;

