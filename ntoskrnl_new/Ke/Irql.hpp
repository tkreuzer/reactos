
#include "Kep.hpp"

#define PASSIVE_LEVEL 0
#define LOW_LEVEL 0
#define APC_LEVEL 1
#define DISPATCH_LEVEL 2
#if defined(_X86_)
 #define CMCI_LEVEL 5
 #define PROFILE_LEVEL 27        .
 #define CLOCK1_LEVEL 28
 #define CLOCK2_LEVEL 28
 #define CLOCK_LEVEL CLOCK2_LEVEL
 #define IPI_LEVEL 29
 #define POWER_LEVEL 30
 #define HIGH_LEVEL 31
#elif defined(_AMD64_)
 #define CMCI_LEVEL 5
 #define CLOCK_LEVEL 13
 #define IPI_LEVEL 14
 #define DRS_LEVEL 14
 #define POWER_LEVEL 14
 #define PROFILE_LEVEL 15
 #define HIGH_LEVEL 15
#elif defined(_ARM_)
 #define CLOCK_LEVEL 13
 #define IPI_LEVEL 14
 #define DRS_LEVEL 14
 #define POWER_LEVEL 14
 #define PROFILE_LEVEL 15
 #define HIGH_LEVEL 15
#elif defined(_ARM64_)
 #define CLOCK_LEVEL 13
 #define IPI_LEVEL 14
 #define DRS_LEVEL 14
 #define POWER_LEVEL 14
 #define PROFILE_LEVEL 15
 #define HIGH_LEVEL 15
#endif
#define SYNCH_LEVEL (IPI_LEVEL-2)

extern "C" {

#ifdef _M_AMD64

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_saves_
__forceinline
KIRQL
KeGetCurrentIrql (
    VOID)
{
    return (KIRQL)__readcr8();
}

#define KzRaiseIrql KfRaiseIrql
#define KzLowerIrql KeLowerIrql

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_raises_(NewIrql)
_IRQL_saves_
__forceinline
KIRQL
KzRaiseIrql (
    _In_ KIRQL NewIrql)
{
    KIRQL OldIrql = KeGetCurrentIrql();
    NT_ASSERT(OldIrql <= NewIrql);
    __writecr8(NewIrql);
    return OldIrql;
}
#define KeRaiseIrql(a,b) *(b) = KfRaiseIrql(a)

_IRQL_requires_max_(HIGH_LEVEL)
__forceinline
VOID
KzLowerIrql (
    _In_ _Notliteral_ _IRQL_restores_ KIRQL NewIrql)
{
    NT_ASSERT(KeGetCurrentIrql() >= NewIrql);
    __writecr8(NewIrql);
}

#else

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_saves_
NTHALAPI
KIRQL
NTAPI
KeGetCurrentIrql (
    VOID);

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_raises_(NewIrql)
_IRQL_saves_
_DECL_HAL_KE_IMPORT
KIRQL
FASTCALL
KfRaiseIrql (
    _In_ KIRQL NewIrql);
#define KeRaiseIrql(a,b) *(b) = KfRaiseIrql(a)

_IRQL_requires_max_(HIGH_LEVEL)
_DECL_HAL_KE_IMPORT
VOID
FASTCALL
KfLowerIrql (
    _In_ _IRQL_restores_ _Notliteral_ KIRQL NewIrql);
#define KeLowerIrql(a) KfLowerIrql(a)

#endif // _M_AMD64

_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
FORCEINLINE
KIRQL
KeRaiseIrqlToDpcLevel (
    VOID)
{
    return KfRaiseIrql(DISPATCH_LEVEL);
}

}; // extern "C"
