#undef __MSVCRT__
#include <psdk/ntverp.h>

/* DDK/IFS/NDK Headers */
#define _NTSYSTEM_
#include <excpt.h>
#include <setjmp.h>
#include <ntdef.h>
#include <ntifs.h>
#include <arc/arc.h>
#include <ntndk.h>
#include <bugcodes.h>

/* KD Support */
#define NOEXTAPI
#include <windbgkd.h>
#include <wdbgexts.h>
#include <kddll.h>

#ifdef _M_AMD64
enum
{
    P1Home = 1 * sizeof(PVOID),
    P2Home = 2 * sizeof(PVOID),
    P3Home = 3 * sizeof(PVOID),
    P4Home = 4 * sizeof(PVOID),
};
#endif

typedef struct
{
    char Type;
    char Name[55];
    ULONGLONG Value;
} ASMGENDATA;

#define TYPE_END 0
#define TYPE_RAW 1
#define TYPE_CONSTANT 2
#define TYPE_HEADER 3
#define TYPE_BEGIN_STRUCT 4
#define TYPE_END_STRUCT 5
#define TYPE_MEMBER 6

#define SIZE_BYTE 0
#define SIZE_WORD 1
#define SIZE_DWORD 2
#define SIZE_PTR 3

#define MAKELONGLONG(l,h) ((l)|((ULONGLONG)(h)<<32))

#define RAW(x) {TYPE_RAW, {x}, 0}
#define CONSTANT(name) {TYPE_CONSTANT, {#name}, (ULONG)name}
#define CONSTANT64(name) {TYPE_CONSTANT, {#name}, (ULONGLONG)name}
#define CONSTANTPTR(name) {TYPE_CONSTANT, {#name}, (ULONG_PTR)name}
#define CONSTANTX(name, value) {TYPE_CONSTANT, {#name}, value}
#define OFFSET(name, struct, member) {TYPE_CONSTANT, {#name}, FIELD_OFFSET(struct, member)}
#define RELOFFSET(name, struct, member, to) {TYPE_CONSTANT, {#name}, FIELD_OFFSET(struct, member) - FIELD_OFFSET(struct, to)}
#define SIZE(name, struct) {TYPE_CONSTANT, {#name}, sizeof(struct)}
#define HEADER(x) {TYPE_HEADER, {x}, 0}
#define BEGIN_STRUCT(name) {TYPE_BEGIN_STRUCT, {#name}, 0}
#define END_STRUCT(name) {TYPE_END_STRUCT, {#name}, 0}
#define MEMBER(struct, name, type) {TYPE_MEMBER, {#name "\0" #type}, MAKELONGLONG(FIELD_OFFSET(struct, name),FIELD_SIZE(struct, name))}

#if defined(_MSC_VER)
#pragma section(".asmdef")
__declspec(allocate(".asmdef"))
#elif defined(__GNUC__)
__attribute__ ((section(".asmdef")))
#else
#error Your compiler is not supported.
#endif

ASMGENDATA Table[] =
{
#if defined (_M_IX86) || defined (_M_AMD64)
#if 0
/* PORTABLE CONSTANTS ********************************************************/
#include "ksx.template.h"
#endif

/* ARCHITECTURE SPECIFIC CONTSTANTS ******************************************/
#ifdef _M_IX86
#include "ks386.template.h"
#elif defined(_M_AMD64)
#include "ksamd64.template.h"
#elif defined(_M_ARM)
#include "ksarm.template.h"
#endif
#else
#ifdef _WIN64
RAW("\n#define POINTER QWORD\n"),
#else
RAW("\n#define POINTER DWORD\n"),
#endif
#ifdef _MSC_VER
RAW("#define Type Type_\n"),
RAW("#define Size Size_\n"),
RAW("#define Rax Rax_\n"),
RAW("#define Rbx Rbx_\n"),
RAW("#define Rcx Rcx_\n"),
RAW("#define Rdx Rdx_\n"),
RAW("#define Rsi Rsi_\n"),
RAW("#define Rdi Rdi_\n"),
RAW("#define Rbp Rbp_\n"),
RAW("#define Rsp Rsp_\n"),
RAW("#define R8 R8_\n"),
RAW("#define R9 R9_\n"),
RAW("#define R10 R10_\n"),
RAW("#define R11 R11_\n"),
RAW("#define R12 R12_\n"),
RAW("#define R13 R13_\n"),
RAW("#define R14 R14_\n"),
RAW("#define R15 R15_\n"),
RAW("#define Xmm0 Xmm0_\n"),
RAW("#define Xmm1 Xmm1_\n"),
RAW("#define Xmm2 Xmm2_\n"),
RAW("#define Xmm3 Xmm3_\n"),
RAW("#define Xmm4 Xmm4_\n"),
RAW("#define Xmm5 Xmm5_\n"),
RAW("#define Xmm6 Xmm6_\n"),
RAW("#define Xmm7 Xmm7_\n"),
RAW("#define Xmm8 Xmm8_\n"),
RAW("#define Xmm9 Xmm9_\n"),
RAW("#define Xmm10 Xmm10_\n"),
RAW("#define Xmm11 Xmm11_\n"),
RAW("#define Xmm12 Xmm12_\n"),
RAW("#define Xmm13 Xmm13_\n"),
RAW("#define Xmm14 Xmm14_\n"),
RAW("#define Xmm15 Xmm15_\n"),

RAW("#define Dr0 Dr0_\n"),
RAW("#define Dr1 Dr1_\n"),
RAW("#define Dr2 Dr2_\n"),
RAW("#define Dr3 Dr3_\n"),
RAW("#define Dr6 Dr6_\n"),
RAW("#define Dr7 Dr7_\n"),
#endif
RAW("#define sizeof(x) sizeof_##x\n"),
#include "asmconst.template.h"
#endif

    /* End of list */
    {TYPE_END, "", 0}
};

