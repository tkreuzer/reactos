

list(APPEND SOURCE
    RtlIntSafe.c
)

if(ARCH STREQUAL "i386")
    list(APPEND SOURCE
        # To be filled
    )
elseif(ARCH STREQUAL "amd64")
    list(APPEND ASM_SOURCE
        amd64/RtlCaptureContext-asm.s
    )
    list(APPEND SOURCE
        amd64/RtlCaptureContext.c
    )
elseif(ARCH STREQUAL "arm")
    list(APPEND SOURCE
        # To be filled
    )
endif()

add_asm_files(ntdll_apitest_asm ${ASM_SOURCE})

add_library(rtl_apitest_lib
    ${SOURCE}
    ${ntdll_apitest_asm}
    testlist.c)

add_dependencies(rtl_apitest_lib asm)

if(NOT MSVC)
    set_source_files_properties(RtlGetFullPathName_UstrEx.c PROPERTIES COMPILE_FLAGS "-Wno-format")

    # Avoid "universal character names are only valid in C++ and C99" error.
    set_property(TARGET rtl_apitest_lib PROPERTY C_STANDARD 99)
endif()

# RTL tests with static linkage
add_executable(rtl_apitest
    ${SOURCE}
    ${ntdll_apitest_asm}
    testlist.c
    ${REACTOS_SOURCE_DIR}/sdk/lib/rtl/um/libsupp.c
    ldrstubs.c)
target_compile_definitions(rtl_apitest PRIVATE _RTL_TEST _NTSYSTEM_)
target_link_libraries(rtl_apitest wine uuid ${PSEH_LIB} rtl)
set_module_type(rtl_apitest win32cui)
add_importlibs(rtl_apitest msvcrt advapi32 kernel32 ntdll ntdll_vista)
target_compile_definitions(rtl_apitest PRIVATE KMT_USER_MODE NTDDI_VERSION=NTDDI_WS03SP1)
add_dependencies(rtl_apitest asm)

add_rostests_file(TARGET rtl_apitest)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(rtl_apitest PRIVATE -Wno-format)
endif()
