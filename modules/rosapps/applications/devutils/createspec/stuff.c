HRESULT
OpenFileFromName(
    _In_ PCSTR pszDllName,
    _Out_ PHANDLE phFile)
{
	HANDLE hFile;

	/* Try current directory */
	GetCurrentDirectoryA(MAX_PATH, gszModuleFileName);
	strcat_s(gszModuleFileName, sizeof(gszModuleFileName), "\\");
	strcat_s(gszModuleFileName, sizeof(gszModuleFileName), pszDllName);
	hFile = CreateFileA(gszModuleFileName,
                        FILE_READ_DATA,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
	if (hFile != INVALID_HANDLE_VALUE)
    {
        *phFile = hFile;
        return S_OK;
    }

	/* Try system32 directory */
    strcat_s(gszModuleFileName, sizeof(gszModuleFileName), "%systemroot%\\system32\\");
    strcat_s(gszModuleFileName, sizeof(gszModuleFileName), pszDllName);
	hFile = CreateFileA(gszModuleFileName,
                        FILE_READ_DATA,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
	if (hFile != INVALID_HANDLE_VALUE)
    {
        *phFile = hFile;
        return S_OK;
    }

    return HRESULT_FROM_WIN32(GetLastError());
}

HRESULT
GetExportsFromFile(
    _In_ PSTR pszModuleName,
    _Out_ PEXPORT_DATA* ppExportData)
{
    HANDLE hFile, hMap;
    HRESULT hr;
    PBYTE pjImageBase;
    PIMAGE_EXPORT_DIRECTORY pExportDir;
    ULONG i, cjExportSize, cFunctions, cjTableSize;
    PEXPORT_DATA pExportData;
    PULONG pulAddressTable, pulNameTable;
    PUSHORT pusOrdinalTable;
#if 1

    HMODULE hmod;

    hmod = LoadModuleWithSymbols(pszModuleName);
    if (hmod == NULL)
    {
        error("Failed to load module '%s'!", pszModuleName);
        return 0;
    }

    pjImageBase = (PBYTE)hmod;
#else
	/* Open the file */
	hr = OpenFileFromName(pszModuleName, &hFile);
    if (!SUCCEEDED(hr))
    {
        error("Failed to open file: %lx\n", hr);
        return hr;
    }

    /* Create an image file mapping */
	hMap = CreateFileMappingA(hFile, NULL, PAGE_READONLY | SEC_IMAGE, 0, 0, NULL);
	if (!hMap)
	{
		error("CreateFileMapping() failed.");
		return HRESULT_FROM_WIN32(GetLastError());
	}

    /* Close the file handle */
    CloseHandle(hFile);

    /* Map the file */
	pjImageBase = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
	if(pjImageBase == NULL)
	{
		error("MapViewOfFile() failed.");
        CloseHandle(hMap);
		return HRESULT_FROM_WIN32(GetLastError());
	}
#endif
	/* Get the export directory */
	pExportDir = ImageDirectoryEntryToData(pjImageBase,
                                           TRUE,
                                           IMAGE_DIRECTORY_ENTRY_EXPORT,
                                           &cjExportSize);
    // ...
}

typedef struct _ENUM_MODULE_CONTEXT
{
    PCSTR pszDllName;
    DWORD64 dwModuleBase;
} ENUM_MODULE_CONTEXT, *PENUM_MODULE_CONTEXT;

BOOL
CALLBACK
EnumModulesCallback(
    _In_ PCSTR pszModuleName,
    _In_ DWORD64 dwModuleBase,
    _In_opt_ PVOID pvUserContext)
{
    PENUM_MODULE_CONTEXT pemc = pvUserContext;

    if (SymMatchFileName(pszModuleName, pemc->pszDllName, NULL, NULL))
    {
        pemc->dwModuleBase = dwModuleBase;
        return FALSE;
    }

    /* Not found, keep enumerating */
    pemc->dwModuleBase = 0;
    return TRUE;
}

BOOL
SymLoadModuleFromAnywhere(
    _In_ PCSTR pszDllName)
{
    ENUM_MODULE_CONTEXT emc;
    CHAR szModuleFileName[MAX_PATH];
    DWORD64 dwModuleBase;

    /* Enumerate already loaded modules */
    emc.pszDllName = pszDllName;
    emc.dwModuleBase = 0;
    if (SymEnumerateModules64(ghProcess, EnumModulesCallback, &emc))
    {
        /* Check if we found a module base */
        if (emc.dwModuleBase != 0)
        {
            return emc.dwModuleBase;
        }
    }

    /* Try direct */
	dwModuleBase = SymLoadModule64(ghProcess, NULL, pszDllName, NULL, 0, 0);
	if (dwModuleBase != 0)
	{
		return dwModuleBase;
	}

    /* Try from system32 */
    strcpy_s(szModuleFileName, sizeof(szModuleFileName), "%systemroot%\\system32\\");
    strcat_s(szModuleFileName, sizeof(szModuleFileName), pszDllName);
	dwModuleBase = SymLoadModule64(ghProcess, NULL, szModuleFileName, NULL, 0, 0);
	if (dwModuleBase != 0)
	{
		return dwModuleBase;
	}

#ifdef _WIN64
    /* Try from SysWow64 */
    strcpy_s(szModuleFileName, sizeof(szModuleFileName), "%systemroot%\\SysWow64\\");
    strcat_s(szModuleFileName, sizeof(szModuleFileName), pszDllName);
	dwModuleBase = SymLoadModule64(ghProcess, NULL, szModuleFileName, NULL, 0, 0);
	if ((dwModuleBase != 0) || (GetLastError() == ERROR_SUCCESS))
	{
		return dwModuleBase;
	}
#endif

    error("Failed to load '%s'", pszDllName);
    return FALSE;
}
