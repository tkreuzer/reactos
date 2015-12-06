
typedef struct _KSEC_BUILTIN_PACKAGE
{
  PSECPKG_KERNEL_FUNCTION_TABLE FunctionTable;
  PUNICODE_STRING PackageName;
  ULONG PackageIndex;
} KSEC_BUILTIN_PACKAGE, *PKSEC_BUILTIN_PACKAGE;

UNICODE_STRING NegotiateName = RTL_CONSTANT_STRING(L"Negotiate");
SECPKG_KERNEL_FUNCTION_TABLE NegFunctionTable = {};

UNICODE_STRING KerberosName = RTL_CONSTANT_STRING(L"Kerberos");
SECPKG_KERNEL_FUNCTION_TABLE KerberosFunctionTable = {};

UNICODE_STRING NtlmName = RTL_CONSTANT_STRING(L"NTLM");
SECPKG_KERNEL_FUNCTION_TABLE NtLmFunctionTable = {};

UNICODE_STRING WDigestName = RTL_CONSTANT_STRING(L"WDigest");
SECPKG_KERNEL_FUNCTION_TABLE WDigestFunctionTable = {};

UNICODE_STRING SchannelName = RTL_CONSTANT_STRING(L"Schannel");
SECPKG_KERNEL_FUNCTION_TABLE SchannelFunctionTable = {};

KSEC_BUILTIN_PACKAGE
KsecBuiltinPackages[] =
{
    {&NegFunctionTable, &NegotiateName, 0},
    {&KerberosFunctionTable, &KerberosName, 0},
    {&NtLmFunctionTable, &NtlmName, 0},
    {&WDigestFunctionTable, &WDigestName, 0},
    {&SchannelFunctionTable, &SchannelName, 0}
};

PSECPKG_KERNEL_FUNCTION_TABLE *Packages;

NTSTATUS
NTAPI
InitializePackages(ULONG cPackages)
{
    ULONG PackageIndex, i;
    NTSTATUS Status;
    PAGED_CODE();

    if (PackagesInitialized)
        return STATUS_SUCCESS;

    ExAcquireFastMutex(&KsecPackageLock);

    if (PackagesInitialized)
    {
        ExReleaseFastMutex(&KsecPackageLock);
        return STATUS_SUCCESS;
    }

    if (KsecConnectionIndicator)
    {
        ExReleaseFastMutex(&KsecPackageLock);
        KeWaitForSingleObject(&KsecConnectEvent, UserRequest, 0, 0, 0);
        return PackagesInitialized ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL;
    }

    KsecConnectionIndicator = 1;
    ExReleaseFastMutex(&KsecPackageLock);
    PackagesSize = cPackages * sizeof(PVOID);

    Packages = ExAllocatePoolWithTag(0, cPackages * sizeof(PVOID), 'cesK');
    if (Packages == NULL)
    {
        return 0x80090300u;
    }

    RtlZeroMemory(Packages, cPackages * sizeof(PVOID));

    /* Loop all builtin packages */
    for (i = 0; i < RTL_NUMBER_OF(KsecBuiltinPackages); i++)
    {
        Status = SecpFindPackage(KsecBuiltinPackages[i].PackageName,
                                 &PackageIndex);

        if (!NT_SUCCESS(Status) || (Packages[PackageIndex] != NULL))
        {
            DPRINT1("Could not find builtin package %wZ\n",
                    &KsecBuiltinPackages[i_].PackageName);
        }
        else
        {
            DPRINT("Assigning package %wZ index %d\n",
                   &KsecBuiltinPackages[i_].PackageName->Buffer,
                   PackageIndex);
            Packages[PackageIndex] = KsecBuiltinPackages[i].FunctionTable;
            KsecBuiltinPackages[i].PackageIndex = PackageIndex;
        }
    }

    for (i = 0; i < KsecDeferredPackageCount; i++)
    {
        Status = SecpFindPackage(KsecDeferredPackages[i].PackageName,
                                 &PackageIndex);
        if (!NT_SUCCESS(Status) || (Packages[PackageIndex] != NULL))
        {
            DPRINT1("Could not find deferred package %wZ\n",
                    &KsecDeferredPackages[i].PackageName);
        }
        else
        {
            DPRINT1("Assigning package %wZ index %d\n",
                    &KsecDeferredPackages[i].PackageName,
                    PackageIndex);
            Packages[PackageIndex] = KsecDeferredPackages[i].FunctionTable;
            KsecDeferredPackages[i].PackageIndex = PackageIndex;
        }
    }

    /* Now loop all packages we got */
    for (i = 0; i < cPackages; i++)
    {
        if (Packages[i])
        {
            Packages[i].Initialize(KspKernelFunctions);
            PackagesInitialized = 1;
        }
    }

    cKernelPackages = cPackages;
    KsecConnectionIndicator = 0;
    KeSetEvent(&KsecConnectEvent, 1, 0);

    return Status;
}
