
add_definitions(
    -D__NTDLL__
    -D_NTOSKRNL_
    -DCRTDLL)

include_directories(
    BEFORE include
    ${REACTOS_SOURCE_DIR}/sdk/include/reactos/subsys)

# The main ntdll_vista is a forwarder to ntdll
spec2def(ntdll_vista.dll ntdll_vista.spec ADD_IMPORTLIB)
add_library(ntdll_vista MODULE
    DllMainStub.c
    ${CMAKE_CURRENT_BINARY_DIR}/ntdll_vista_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/ntdll_vista.def)
set_module_type(ntdll_vista win32dll ENTRYPOINT DllMain 12)
#if(ARCH STREQUAL "arm")
#    target_link_libraries(ntdll_vista chkstk)
#endif()
add_importlibs(ntdll_vista ntdll)
add_dependencies(ntdll_vista psdk)
add_cd_file(TARGET ntdll_vista DESTINATION reactos/system32 FOR all)

# This is a standalone version for testing on win 2003 (rename to ntdll_vista.dll)
spec2def(ntdll_vista_standalone.dll ntdll_vista_standalone.spec)
add_library(ntdll_vista_standalone MODULE
    DllMain.c
    ${CMAKE_CURRENT_BINARY_DIR}/ntdll_vista_standalone.def)
set_module_type(ntdll_vista_standalone win32dll ENTRYPOINT DllMain 12)
target_link_libraries(ntdll_vista_standalone rtl_vista)
if(ARCH STREQUAL "arm")
    target_link_libraries(ntdll_vista_standalone chkstk)
endif()
add_importlibs(ntdll_vista_standalone ntdll)
add_dependencies(ntdll_vista_standalone psdk)
