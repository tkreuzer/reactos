
/* Based on Windows 8 */
class USER_SHARED_DATA
{
    ULONG TickCountLowDeprecated;
    ULONG TickCountMultiplier;
    KSYSTEM_TIME InterruptTime;
    KSYSTEM_TIME SystemTime;
    KSYSTEM_TIME TimeZoneBias;
    USHORT ImageNumberLow;
    USHORT ImageNumberHigh;
    WCHAR NtSystemRoot[260];
    ULONG MaxStackTraceDepth;
    ULONG CryptoExponent;
    ULONG TimeZoneId;
    ULONG LargePageMinimum;
    ULONG AitSamplingValue;
    ULONG AppCompatFlag;
    UINT64 RNGSeedVersion;
    ULONG GlobalValidationRunlevel;
    ULONG Reserved2[2];
    enum _NT_PRODUCT_TYPE NtProductType;
    UCHAR ProductTypeIsValid;
    UCHAR Reserved0[1];
    USHORT NativeProcessorArchitecture;
    ULONG NtMajorVersion;
    ULONG NtMinorVersion;
    UCHAR ProcessorFeatures[64];
    ULONG HighestUserAddress32; // Reserved1;
    ULONG SystemRangeStart32; // Reserved3;
    ULONG TimeSlip;
    enum _ALTERNATIVE_ARCHITECTURE_TYPE AlternativeArchitecture;
    ULONG AltArchitecturePad[1];
    LARGE_INTEGER SystemExpirationDate;
    ULONG SuiteMask;
    UCHAR KdDebuggerEnabled;
    union
    {
        UCHAR MitigationPolicies;
        struct
        {
            UCHAR NXSupportPolicy : 2;
            UCHAR SEHValidationPolicy : 2;
            UCHAR CurDirDevicesSkippedForDlls : 2;
            UCHAR Reserved : 2;
        };
    };
    UCHAR Reserved6[2];
    ULONG ActiveConsoleId;
    ULONG DismountCount;
    ULONG ComPlusPackage;
    ULONG LastSystemRITEventTickCount;
    ULONG NumberOfPhysicalPages;
    UCHAR SafeBootMode;
    UCHAR Reserved12[3];
    union
    {
        ULONG SharedDataFlags;
        struct
        {
            ULONG DbgErrorPortPresent : 1;
            ULONG DbgElevationEnabled : 1;
            ULONG DbgVirtEnabled : 1;
            ULONG DbgInstallerDetectEnabled : 1;
            ULONG DbgLkgEnabled : 1;
            ULONG DbgDynProcessorEnabled : 1;
            ULONG DbgConsoleBrokerEnabled : 1;
            ULONG SpareBits : 25;
        };
    };
    ULONG DataFlagsPad[1];
    UINT64 TestRetInstruction;
    ULONG Reserved9;
    ULONG Reserved10;
    UINT64 SystemCallPad[3];
    union
    {
        KSYSTEM_TIME TickCount;
        UINT64 TickCountQuad;
        ULONG ReservedTickCountOverlay[3];
    };
    ULONG TickCountPad[1];
    ULONG Cookie;
    ULONG CookiePad[1];
    INT64 ConsoleSessionForegroundProcessId;
    UINT64 TimeUpdateSequence;
    UINT64 LastTimeUpdateQpcValue;
    UINT64 LastInterruptTimeUpdateQpcValue;
    UINT64 QpcTimeIncrement;
    ULONG QpcTimeIncrement32;
    ULONG Reserved8[7];
    USHORT UserModeGlobalLogger[16];
    ULONG ImageFileExecutionOptions;
    ULONG LangGenerationCount;
    UINT64 InterruptTimeBias;
    UINT64 TscQpcBias;
    ULONG ActiveProcessorCount;
    UCHAR ActiveGroupCount;
    UCHAR QpcTimeIncrementShift;
    union
    {
        USHORT TscQpcData;
        struct
        {
            UCHAR TscQpcEnabled;
            UCHAR TscQpcShift;
        };
    };
    struct _XSTATE_CONFIGURATION XState;

    //
    VOID
    Initialize (
        VOID);

    VOID
    UpdateSystemTime (
        );


};

typedef class USER_SHARED_DATA *PUSER_SHARED_DATA;


