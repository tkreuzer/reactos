
#include "precomp.h"
#include <ntndk.h>
#include <winreg.h>
#include <pseh/pseh2.h>

#define ok_eq_hex ok_hex
#define ok_eq_int ok_int
#define ok_eq_uint ok_hex
#define ok_eq_ulong ok_hex
#define ok_eq_pointer ok_ptr
#define ok_eq_size ok_size_t
#define ok_eq_longlong ok_int64
#define ok_bool_true(value, desc)           ok((value) == TRUE, desc " FALSE, expected TRUE\n")
#define ok_bool_false(value, desc)          ok((value) == FALSE, desc " TRUE, expected FALSE\n")
#define ok_eq_bool(value, expected)         ok((value) == (expected), #value " = %s, expected %s\n",    \
                                                (value) ? "TRUE" : "FALSE",                             \
                                                (expected) ? "TRUE" : "FALSE")
#define ok_eq_str(value, expected)          ok(!strcmp(value, expected), #value " = \"%s\", expected \"%s\"\n", value, expected)
#define ok_eq_wstr(value, expected)         ok(!wcscmp(value, expected), #value " = \"%ls\", expected \"%ls\"\n", value, expected)

#undef skip
#define skip(test, ...)              skip_(__FILE__, __LINE__), 0

#define KmtStartSeh()                               \
{                                                   \
    NTSTATUS ExceptionStatus = STATUS_SUCCESS;      \
    _SEH2_TRY                                       \
    {

#define KmtEndSeh(ExpectedStatus)                   \
    }                                               \
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)         \
    {                                               \
        ExceptionStatus = _SEH2_GetExceptionCode(); \
    }                                               \
    _SEH2_END;                                      \
    ok_eq_hex(ExceptionStatus, (ExpectedStatus));   \
}

#ifdef KMT_EMULATE_KERNEL
#define ok_irql(i)
#define KIRQL int
typedef const UCHAR CUCHAR, * PCUCHAR;
typedef ULONG LOGICAL, * PLOGICAL;

#undef KeRaiseIrql
#define KeRaiseIrql(new, old) *(old) = 123
#undef KeLowerIrql
#define KeLowerIrql(i) (void)(i)
#define ExAllocatePool(type, size)              HeapAlloc(GetProcessHeap(), 0, size)
#define ExAllocatePoolWithTag(type, size, tag)  HeapAlloc(GetProcessHeap(), 0, size)
#define ExFreePool(p)                           HeapFree(GetProcessHeap(), 0, p)
#define ExFreePoolWithTag(p, tag)               HeapFree(GetProcessHeap(), 0, p)
#define RtlCopyMemoryNonTemporal                RtlCopyMemory
#define RtlPrefetchMemoryNonTemporal(s, l)
#define ExRaiseStatus                           RtlRaiseStatus
#define KmtIsCheckedBuild                       FALSE
#endif /* defined KMT_EMULATE_KERNEL */

static
PVOID KmtAllocateGuarded(SIZE_T SizeRequested)
{
    NTSTATUS Status;
    SIZE_T Size = PAGE_ROUND_UP(SizeRequested + PAGE_SIZE);
    PVOID VirtualMemory = NULL;
    PCHAR StartOfBuffer;

    Status = ZwAllocateVirtualMemory(ZwCurrentProcess(), &VirtualMemory, 0, &Size, MEM_RESERVE, PAGE_NOACCESS);

    if (!NT_SUCCESS(Status))
        return NULL;

    Size -= PAGE_SIZE;
    Status = ZwAllocateVirtualMemory(ZwCurrentProcess(), &VirtualMemory, 0, &Size, MEM_COMMIT, PAGE_READWRITE);
    if (!NT_SUCCESS(Status))
    {
        Size = 0;
        Status = ZwFreeVirtualMemory(ZwCurrentProcess(), &VirtualMemory, &Size, MEM_RELEASE);
        ok_eq_hex(Status, STATUS_SUCCESS);
        return NULL;
    }

    StartOfBuffer = VirtualMemory;
    StartOfBuffer += Size - SizeRequested;

    return StartOfBuffer;
}

static
VOID KmtFreeGuarded(PVOID Pointer)
{
    NTSTATUS Status;
    PVOID VirtualMemory = (PVOID)PAGE_ROUND_DOWN((SIZE_T)Pointer);
    SIZE_T Size = 0;

    Status = ZwFreeVirtualMemory(ZwCurrentProcess(), &VirtualMemory, &Size, MEM_RELEASE);
    ok_eq_hex(Status, STATUS_SUCCESS);
}
