
enum _EFLAGS
{
    EFLAGS_IF = 0x00000200,
};

class VCPU_PRIVATE
{
private:
    static int
    PrivateMethod ();

    friend class VCPU;
};

inline
KIRQL
VCPU::GetCurrentIrql (VOID)
{
    (KIRQL)__readcr8();
}

inline
VOID
VCPU::RaiseIrql (
    _In_ KIRQL NewIrql)
{
    ASSERT(GetCurrentIrql() <= NewIrql);
    __writecr8(NewIrql);
}

inline
VOID
VCPU::LowerIrql (
    _In_ KIRQL NewIrql)
{
    ASSERT(GetCurrentIrql() >= NewIrql);
    __writecr8(NewIrql);
}

inline
BOOLEAN
VCPU::DisableInterrupts (VOID)
{
    ULONG_PTR eflags;

    eflags = __readeflags();
    _disable();

    return (eflags & EFLAGS_IF) != 0;
}

inline
BOOLEAN
VCPU::EnableInterrupts (VOID)
{
    ULONG_PTR eflags;

    eflags = __readeflags();
    _enable();

    return (eflags & EFLAGS_IF) != 0;
}

inline
class PCR*
VCPU::GetPcr (VOID)
{
    return reinterpret_cast<class PCR*>(
               __readgsqword(0x18)
           );
}

inline
ULONG_PTR
VCPU::GetPageDirectory (VOID)
{
    return __readcr3();
}

inline
VOID
VCPU::InvalidateTlbEntry (
    _In_ PVOID Address)
{
    __invlpg(Address);
}

inline
VOID
VCPU::FlushTlb (VOID)
{
    __writecr3(__readcr3());
}


