/*
 * PROJECT:     ReactOS API Tests
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later)
 * PURPOSE:     Test for NtQueryObject
 * COPYRIGHT:   Copyright 2024 Hermès Bélusca-Maïto <hermes.belusca-maito@reactos.org>
 */

#include "precomp.h"

DWORD WINAPI DECLSPEC_HOTPATCH GetFinalPathNameByHandleW( HANDLE file, LPWSTR path,
                                                          DWORD count, DWORD flags );

/* Flags combination allowing all the read, write and delete share modes.
 * Currently similar to FILE_SHARE_VALID_FLAGS. */
#define FILE_SHARE_ALL \
    (FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE)

#define VOLUME_NAME_DOS 0x0
#define VOLUME_NAME_GUID 0x1
#define VOLUME_NAME_NT 0x2
#define VOLUME_NAME_NONE 0x4
#define FILE_NAME_NORMALIZED 0x0
#define FILE_NAME_OPENED 0x8
#define WARN trace
#define TRACE trace

#include <ntstrsafe.h>

DWORD
WINAPI
BaseSetLastNTError(IN NTSTATUS Status)
{
    DWORD dwErrCode;

    /* Convert from NT to Win32, then set */
    dwErrCode = RtlNtStatusToDosError(Status);
    SetLastError(dwErrCode);
    return dwErrCode;
}

DWORD
WINAPI
MyGetFinalPathNameByHandleW(
    _In_ HANDLE hFile,
    _Out_writes_(cchFilePath) LPWSTR lpszFilePath,
    _In_ DWORD cchFilePath,
    _In_ DWORD dwFlags)
{
    WCHAR NameInfoBuffer[sizeof(OBJECT_NAME_INFORMATION) + MAX_PATH + 1];
    POBJECT_NAME_INFORMATION NameInfo = (POBJECT_NAME_INFORMATION)NameInfoBuffer;
    WCHAR VolumeBuffer[MAX_PATH];
    WCHAR DeviceBuffer[MAX_PATH];
    UNICODE_STRING DeviceName, RelativePath;
    ULONG VolumeType;
    NTSTATUS Status;
    ULONG FinalLength;
    BOOL Success;

    /* Validate flags */
    if (dwFlags & ~(FILE_NAME_OPENED | VOLUME_NAME_GUID | VOLUME_NAME_NONE | VOLUME_NAME_NT))
    {
        WARN("Unknown flags: %lx\n", dwFlags);
        SetLastError( ERROR_INVALID_PARAMETER);
        return 0;
    }

    /* Query the object name */
    Status = NtQueryObject(hFile,
                           ObjectNameInformation,
                           &NameInfoBuffer,
                           sizeof(NameInfoBuffer) - sizeof(WCHAR),
                           NULL);
    if (!NT_SUCCESS(Status))
    {
        BaseSetLastNTError(Status);
        return 0;
    }

    /* Make sure the object name is valid */
    if ((NameInfo->Name.Buffer == NULL) ||
        (NameInfo->Name.Length < sizeof("\\Device\\")))
    {
        /* The object name is not valid */
        WARN("Invalid object name: %wZ\n", &NameInfo->Name);
        SetLastError(ERROR_INVALID_HANDLE);
        return 0;
    }

    /* Null terminate the name */
    NameInfo->Name.Buffer[NameInfo->Name.Length / sizeof(WCHAR)] = UNICODE_NULL;

    /* Extract the requested volume type */
    VolumeType = dwFlags & (VOLUME_NAME_GUID | VOLUME_NAME_NONE | VOLUME_NAME_NT);

    /* If the NT path was requested, we can return the name as it is */
    if (VolumeType == VOLUME_NAME_NT)
    {
        if (cchFilePath < NameInfo->Name.Length / sizeof(WCHAR) + 1)
        {
            SetLastError(ERROR_INSUFFICIENT_BUFFER);
            return 0;
        }

        /* Copy the name to the caller's buffer */
        RtlCopyMemory(lpszFilePath, NameInfo->Name.Buffer, NameInfo->Name.Length);
        lpszFilePath[NameInfo->Name.Length / sizeof(WCHAR)] = UNICODE_NULL;

        /* Return the length of the name */
        return NameInfo->Name.Length / sizeof(WCHAR);
    }

    /* Query the volume path name */
    Success = GetVolumePathNameW(NameInfo->Name.Buffer, VolumeBuffer, MAX_PATH);
    if (!Success)
    {
        WARN("GetVolumePathNameW failed: %d\n", GetLastError());
        return 0;
    }

    /* Remove the trailing backslash */
    SIZE_T VolumeLength = wcslen(VolumeBuffer);
    if (VolumeBuffer[VolumeLength - 1] == '\\')
    {
        VolumeBuffer[VolumeLength - 1] = UNICODE_NULL;
        VolumeLength--;
    }

    /* Query the device name of the volume */
    Success = QueryDosDeviceW(VolumeBuffer, DeviceBuffer, MAX_PATH);
    if (!Success)
    {
        WARN("QueryDosDeviceW failed: %d\n", GetLastError());
        return 0;
    }

    /* Check if the volume device path matches */
    RtlInitUnicodeString(&DeviceName, DeviceBuffer);
    if (!RtlPrefixUnicodeString(&DeviceName, &NameInfo->Name, TRUE))
    {
        WARN("Volume name '%wZ' not found in object name '%wZ'\n", &DeviceName, &NameInfo->Name);
        SetLastError(ERROR_INVALID_HANDLE);
        return 0;
    }

    /* Set up the relative path name by skipping the volume part */
    SIZE_T DeviceNameLength = wcslen(DeviceBuffer);
    RelativePath.Buffer = NameInfo->Name.Buffer + DeviceNameLength;
    RelativePath.Length = NameInfo->Name.Length + DeviceNameLength * sizeof(WCHAR);
    RelativePath.MaximumLength = RelativePath.Length;

    /* If no volume was requested, return the relative path */
    if (VolumeType == VOLUME_NAME_NONE)
    {
        if (cchFilePath < RelativePath.Length / sizeof(WCHAR) + 1)
        {
            SetLastError(ERROR_INSUFFICIENT_BUFFER);
            return 0;
        }

        /* Copy the name to the caller's buffer */
        RtlCopyMemory(lpszFilePath, RelativePath.Buffer, RelativePath.Length);
        lpszFilePath[RelativePath.Length / sizeof(WCHAR)] = UNICODE_NULL;

        /* Return the length of the name */
        return RelativePath.Length / sizeof(WCHAR);
    }


    if (VolumeType == VOLUME_NAME_DOS)
    {
        static const PrefixLength = sizeof("\\??\\") - 1;
        FinalLength = PrefixLength +
                      VolumeLength +
                      (RelativePath.Length / sizeof(WCHAR));

        if (cchFilePath < FinalLength + 1)
        {
            SetLastError(ERROR_INSUFFICIENT_BUFFER);
            return 0;
        }

        /* Construct the final name */
        RtlCopyMemory(lpszFilePath, L"\\\\?\\", PrefixLength);
        RtlCopyMemory(lpszFilePath + PrefixLength,
                      VolumeBuffer,
                      VolumeLength * sizeof(WCHAR));
        RtlCopyMemory(lpszFilePath + PrefixLength + VolumeLength,
                      RelativePath.Buffer,
                      RelativePath.Length);
        lpszFilePath[FinalLength] = UNICODE_NULL;

        /* Return the length of the name */
        return FinalLength;
    }

    if (VolumeType == VOLUME_NAME_GUID)
    {
        __debugbreak();
        wcscat(VolumeBuffer, L"\\");
        Success = GetVolumeNameForVolumeMountPointW(VolumeBuffer, DeviceBuffer, MAX_PATH);
        if (!Success)
        {
            WARN("GetVolumeNameForVolumeMountPointW failed: %d\n", GetLastError());
            return 0;
        }

        SIZE_T PrefixLength = wcslen(DeviceBuffer);
        FinalLength = PrefixLength +
                      (RelativePath.Length / sizeof(WCHAR));
    }

    return 0;
}

/* Adapted from kmtests/ntos_ob/ObQuery.c!ObjectNameInformationTests().
 * Please sync both tests in case you add or remove new features. */
START_TEST(NtQueryObject)
{
    ULONG g_OsVersion =
        SharedUserData->NtMajorVersion << 8 | SharedUserData->NtMinorVersion;

    NTSTATUS Status;
    HANDLE DeviceHandle;
    UNICODE_STRING DeviceName;
    OBJECT_ATTRIBUTES ObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;

    ULONG BufferSize1, BufferSize2, BufferSize3;
    struct { OBJECT_NAME_INFORMATION; WCHAR Buffer[MAX_PATH]; } ObjectNameBuffer;
    PUNICODE_STRING ObjectName = &ObjectNameBuffer.Name;

    /* Test the drive containing SystemRoot */
    WCHAR NtDeviceName[] = L"\\DosDevices\\?:";
    NtDeviceName[sizeof("\\DosDevices\\")-1] = SharedUserData->NtSystemRoot[0];

    /* Open a handle to the device */
    RtlInitUnicodeString(&DeviceName, NtDeviceName);
    InitializeObjectAttributes(&ObjectAttributes,
                               &DeviceName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
    Status = NtOpenFile(&DeviceHandle,
                        FILE_READ_ATTRIBUTES | SYNCHRONIZE,
                        &ObjectAttributes,
                        &IoStatusBlock,
                        FILE_SHARE_ALL,
                        FILE_SYNCHRONOUS_IO_NONALERT);
    ok_ntstatus(Status, STATUS_SUCCESS);
    if (!NT_SUCCESS(Status))
    {
        skip("Device '%S': Opening failed\n", NtDeviceName);
        return;
    }

    /* Invoke ObjectNameInformation that retrieves the canonical device name */
    Status = NtQueryObject(DeviceHandle,
                           ObjectNameInformation,
                           &ObjectNameBuffer,
                           0,
                           &BufferSize1);
    ok_ntstatus(Status, STATUS_INFO_LENGTH_MISMATCH);

    Status = NtQueryObject(DeviceHandle,
                           ObjectNameInformation,
                           &ObjectNameBuffer,
                           sizeof(OBJECT_NAME_INFORMATION),
                           &BufferSize2);
    ok_ntstatus(Status, STATUS_BUFFER_OVERFLOW);

    Status = NtQueryObject(DeviceHandle,
                           ObjectNameInformation,
                           &ObjectNameBuffer,
                           sizeof(ObjectNameBuffer),
                           &BufferSize3);
    ok_ntstatus(Status, STATUS_SUCCESS);

    NtClose(DeviceHandle);

    /* Compare the returned buffer sizes */

    /* The returned size behaviour changed (when NtQueryObject()'s
     * input Length is zero) between Windows <= 2003 and Vista+ */
    if (g_OsVersion < _WIN32_WINNT_VISTA)
        ok_eq_ulong(BufferSize1, (ULONG)sizeof(OBJECT_NAME_INFORMATION));
    else
        ok_eq_ulong(BufferSize1, (ULONG)sizeof(OBJECT_NAME_INFORMATION) + ObjectName->MaximumLength);

    ok_eq_ulong(BufferSize2, BufferSize3);
    ok_eq_ulong(BufferSize3, (ULONG)sizeof(OBJECT_NAME_INFORMATION) + ObjectName->MaximumLength);

    /* Test the name buffer */
    ok(ObjectName->Length > 0, "ObjectName->Length == %hu, expected > 0\n", ObjectName->Length);
    ok_eq_uint(ObjectName->MaximumLength, ObjectName->Length + sizeof(WCHAR));
    ok(ObjectName->Buffer[ObjectName->Length / sizeof(WCHAR)] == UNICODE_NULL,
       "UNICODE_NULL not found at end of ObjectName->Buffer\n");
    if (ObjectName->Buffer[ObjectName->Length / sizeof(WCHAR)] != UNICODE_NULL)
    {
        skip("ObjectName->Buffer string length check skipped\n");
        return;
    }

    /* Verify that ObjectName->Length doesn't count extra NUL-terminators */
    SIZE_T strLen = wcslen(ObjectName->Buffer) * sizeof(WCHAR);
    ok_eq_size(strLen, (SIZE_T)ObjectName->Length);

    /* Get the full path name of the current executable */
    WCHAR ExecutablePath[MAX_PATH];
    GetModuleFileNameW(NULL, ExecutablePath, MAX_PATH);

    /* Open the executable file */
    HANDLE FileHandle;
    FileHandle = CreateFileW(ExecutablePath,
                             GENERIC_READ,
                             FILE_SHARE_READ | FILE_SHARE_WRITE,
                             NULL,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL);
    ok(FileHandle != INVALID_HANDLE_VALUE,
       "File '%S': Opening failed\n", ExecutablePath);
    if (FileHandle == INVALID_HANDLE_VALUE)
    {
        skip("File '%S': Opening failed\n", ExecutablePath);
        return;
    }

    WCHAR FinalName[MAX_PATH] = { 0 };
    BOOL r = MyGetFinalPathNameByHandleW(
        FileHandle,
        FinalName,
        MAX_PATH,
        VOLUME_NAME_GUID);
    ok( r, "GetFinalPathNameByHandleW failed: %d\n", GetLastError());

    // VOLUME_NAME_DOS (0): L"\\\\?\\C:\\ReactOS\\build-vs-x64\\modules\\rostests\\apitests\\ntdll\\Debug\\ntdll_apitest.exe"
    // VOLUME_NAME_GUID (1): L"\\\\?\\Volume{c556c154-971a-4864-b10e-897494e24909}\\ReactOS\\build-vs-x64\\modules\\rostests\\apitests\\ntdll\\Debug\\ntdll_apitest.exe"
    // VOLUME_NAME_NT (2): L"\\Device\\HarddiskVolume3\\ReactOS\\build-vs-x64\\modules\\rostests\\apitests\\ntdll\\Debug\\ntdll_apitest.exe"
    // VOLUME_NAME_NONE (4): L"\\ReactOS\\build-vs-x64\\modules\\rostests\\apitests\\ntdll\\Debug\\ntdll_apitest.exe"

    /* Query the name of the file */
    Status = NtQueryObject(FileHandle,
                           ObjectNameInformation,
                           &ObjectNameBuffer,
                           sizeof(ObjectNameBuffer),
                           &BufferSize3);
    ok_ntstatus(Status, STATUS_SUCCESS);

    /* Validate that the name starts with "\\Device" */
    ok(wcsncmp(ObjectName->Buffer, L"\\Device", 7) == 0,
       "ObjectName->Buffer: '%S' does not start with '\\Device'\n",
       ObjectName->Buffer);

    RtlZeroMemory(ExecutablePath, sizeof(ExecutablePath));
    BOOL ret = GetVolumePathNameW(ObjectName->Buffer, ExecutablePath, MAX_PATH);
    ok(ret, "GetVolumePathNameW failed: %d\n", GetLastError());

    ExecutablePath[2] = L'\0';
    ret = QueryDosDeviceW(ExecutablePath, ExecutablePath, MAX_PATH);
    ok(ret, "GetVolumePathNameW failed: %d\n", GetLastError());
}
