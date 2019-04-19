
#include <ntbase.h>
#include "KeTypes.hpp"
#include <intrin.h>

/*! \brief VCPU interface definition
 *
 * This defines the interface of the VCPU class.
 *
 * VCPU is a "virtual" class, not in the sense of having virtual methods, but
 * in the sense of not maintaining an actual state in the object instance.
 * VCPU does not have any member variables and all methods are static.
 * The complete state of a VCPU object is implicit in the CPU state.
 * Additional state information can be accessed through the PCR.
 *
 * The actual architecture specific implementation is in <arch>/VCpu.hpp and
 * <arch>/Vcpu.cpp.
 */
class VCPU
{
private:
    // the kernel may access our private classes
    friend class KERNEL;

    static
    VOID
    Initialize (VOID);

public:

    static
    KIRQL
    GetCurrentIrql (VOID);

    static
    VOID
    RaiseIrql (
        _In_ KIRQL NewIrql);

    static
    VOID
    LowerIrql (
        _In_ KIRQL NewIrql);

    static
    BOOLEAN
    DisableInterrupts (VOID);

    static
    BOOLEAN
    EnableInterrupts (VOID);

    static
    class PCR*
    GetPcr (VOID);

    static
    ULONG_PTR
    GetPageDirectory (VOID);

    static
    VOID
    InvalidateTlbEntry (
        _In_ PVOID Address);

    static
    VOID
    FlushTlb (VOID);

};

#include _ARCH_RELATIVE_(VCpu.hpp)
