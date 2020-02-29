
remove_definitions(-D_WIN32_WINNT=0x502 -DWINVER=0x502)
add_definitions(-D_WIN32_WINNT=0x600 -DWINVER=0x600)

add_definitions(-D_KERNEL32_)
include_directories(${REACTOS_SOURCE_DIR}/sdk/include/reactos/subsys)

list(APPEND SOURCE
    GetFileInformationByHandleEx.c
    GetTickCount64.c
    InitOnceExecuteOnce.c
    sync.c
    vista.c)

# Static library with the vista functions
add_library(kernel32_vista_static ${SOURCE})

# The main kernel32_vista is a forwarder to kernel32
spec2def(kernel32_vista.dll kernel32_vista.spec ADD_IMPORTLIB)
add_library(kernel32_vista MODULE
    DllMainStub.c
    ${CMAKE_CURRENT_BINARY_DIR}/kernel32_vista_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/kernel32_vista.def)
set_module_type(kernel32_vista win32dll ENTRYPOINT DllMain 12)
add_importlibs(kernel32_vista kernel32)
add_dependencies(kernel32_vista psdk)
add_cd_file(TARGET kernel32_vista DESTINATION reactos/system32 FOR all)

# Standalone version for testing on win 2003 (rename to kernel32_vista.dll)
spec2def(kernel32_vista_standalone.dll kernel32_vista_standalone.spec ADD_IMPORTLIB)
add_library(kernel32_vista_standalone MODULE
    DllMain.c
    ${CMAKE_CURRENT_BINARY_DIR}/kernel32_vista_standalone.def)
set_module_type(kernel32_vista_standalone win32dll ENTRYPOINT DllMain 12)
target_link_libraries(kernel32_vista_standalone kernel32_vista_static)
add_importlibs(kernel32_vista_standalone kernel32 ntdll)
add_delay_importlibs(kernel32_vista_standalone ntdll_vista)
add_dependencies(kernel32_vista_standalone psdk)
