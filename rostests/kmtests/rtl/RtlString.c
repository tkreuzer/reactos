/*
 * PROJECT:         ReactOS kernel-mode tests
 * LICENSE:         GPLv2+ - See COPYING in the top level directory
 * PURPOSE:         Kernel-Mode Test Suite Runtime library memory functions test
 * PROGRAMMER:      Thomas Faber <thfabba@gmx.de>
 */

#include <stddef.h>
__declspec(dllimport) void __stdcall RtlMoveMemory(void *, const void *, size_t);
__declspec(dllimport) void __stdcall RtlFillMemory(void *, size_t, unsigned char);

#define KMT_EMULATE_KERNEL
#include <kmt_test.h>

#define ok_eq_short ok_eq_long

#ifdef __VISTA_
void
Test_RtlFindCharInUnicodeString(void)
{
    UNICODE_STRING SearchString = RTL_CONSTANT_STRING(L"abcdef ABCDEF abcdef \0 p abcdef");
    UNICODE_STRING CharString1 = RTL_CONSTANT_STRING(L"abc");
    UNICODE_STRING CharString2 = RTL_CONSTANT_STRING(L"xyzabc");
    UNICODE_STRING CharString3 = RTL_CONSTANT_STRING(L"xyzcba");
    //UNICODE_STRING CharString4 = RTL_CONSTANT_STRING(L"xyz");
    //UNICODE_STRING CharString5 = RTL_CONSTANT_STRING(L"xy\0ab");
    //UNICODE_STRING CharString6 = RTL_CONSTANT_STRING(L"");
    //UNICODE_STRING CharString7 = RTL_CONSTANT_STRING(L"p");
    NTSTATUS Status;
    USHORT Position;
    ULONG PosTest;

    /* Check if the return size is USHORT */
    PosTest = 0x12345678;
    Status = RtlFindCharInUnicodeString(0, &SearchString, &CharString1, (PUSHORT)&PosTest);
    ok_eq_hex(Status, STATUS_SUCCESS);
    ok_eq_hex(PosTest, 0x12340000);

    Status = RtlFindCharInUnicodeString(0, &SearchString, &CharString1, &Position);
    ok_eq_hex(Status, STATUS_SUCCESS);
    ok_eq_short(Position, 0);

    Status = RtlFindCharInUnicodeString(0, &SearchString, &CharString2, &Position);
    ok_eq_hex(Status, STATUS_SUCCESS);
    ok_eq_short(Position, 0);

    Status = RtlFindCharInUnicodeString(0, &SearchString, &CharString3, &Position);
    ok_eq_hex(Status, STATUS_SUCCESS);
    ok_eq_short(Position, 0);

}
#endif

START_TEST(RtlString)
{
    //Test_RtlFindCharInUnicodeString();
}
