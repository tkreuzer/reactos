#if defined(_X86_)
#define KF_MMX                      0x0000000000000100ui64
#define KF_XMMI                     0x0000000000002000ui64
#define KF_3DNOW                    0x0000000000004000ui64
#define KF_XMMI64                   0x0000000000010000ui64
#define KF_SSE3                     0x0000000000080000ui64

VOID
NTAPI
Ke386SetLdtProcess (
    _In_ struct _KPROCESS  *Process,
    _In_ PLDT_ENTRY  Ldt,
    _In_ ULONG       Limit
    );

VOID
NTAPI
Ke386SetDescriptorProcess (
    _In_ struct _KPROCESS  *Process,
    _In_ ULONG       Offset,
    _In_ LDT_ENTRY   LdtEntry
    );

VOID
NTAPI
Ke386GetGdtEntryThread (
    _In_ struct _KTHREAD *Thread,
    _In_ ULONG Offset,
    _Out_ PKGDTENTRY Descriptor
    );

BOOLEAN
NTAPI
Ke386SetIoAccessMap (
    _In_range_(<, IOPM_COUNT) ULONG MapNumber,
    _In_reads_bytes_(IOPM_SIZE) PKIO_ACCESS_MAP IoAccessMap
    );

BOOLEAN
NTAPI
Ke386QueryIoAccessMap (
    _In_range_(<, IOPM_COUNT) ULONG MapNumber,
    _Out_writes_bytes_(IOPM_SIZE) PKIO_ACCESS_MAP IoAccessMap
    );

BOOLEAN
NTAPI
Ke386IoSetAccessProcess (
    _In_ struct _KPROCESS    *Process,
    _In_range_(<, IOPM_COUNT) ULONG  MapNumber
    );

VOID
NTAPI
KiEditIopmDpc (
    _In_ struct _KDPC *Dpc,
    _In_opt_ PVOID DeferredContext,
    _In_opt_ PVOID SystemArgument1,
    _In_opt_ PVOID SystemArgument2
    );

BOOLEAN
NTAPI
Ki386GetSelectorParameters(
    _In_ USHORT Selector,
    _Out_ PULONG Flags,
    _Out_ PULONG Base,
    _Out_ PULONG Limit
    );

ULONG
Ki386DispatchOpcodeV86 (
    _In_ PKTRAP_FRAME TrapFrame
    );

ULONG
Ki386DispatchOpcode (
    _In_ PKTRAP_FRAME TrapFrame
    );

NTSTATUS
NTAPI
Ke386SetVdmInterruptHandler (
    _In_ struct _KPROCESS *Process,
    _In_ ULONG Interrupt,
    _In_ USHORT Selector,
    _In_ ULONG  Offset,
    _In_ BOOLEAN Gate32
    );

ULONG
KiGetCpuVendor(
    VOID
    );

#endif //_X86_  // irqls
