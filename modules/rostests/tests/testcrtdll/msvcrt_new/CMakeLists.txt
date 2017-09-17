
include_directories(${REACTOS_SOURCE_DIR}/lib/sdk/crt/include)
spec2def(msvcrt_new.dll msvcrt_new.spec ADD_IMPORTLIB)

add_definitions(
    -DUSE_MSVCRT_PREFIX
    -D_MSVCRT_
    -D_MSVCRT_LIB_
    -D_MT
    -D_CTYPE_DISABLE_MACROS
    -D_NO_INLINING
    -DCRTDLL
    -D__MINGW_IMPORT="")

set(baseaddress_msvcrt_new 0x2000000)

list(APPEND SOURCE
    dllmain.c
    stubs.c
    msvcrt.rc
    ${CMAKE_CURRENT_BINARY_DIR}/msvcrt_new_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/msvcrt_new.def)

add_library(msvcrt_new SHARED ${SOURCE})

set_module_type(msvcrt_new win32dll ENTRYPOINT 0)
add_dependencies(msvcrt_new psdk)
target_link_libraries(msvcrt_new crt wine ${PSEH_LIB})

if(MSVC)
    # export of deleting destructor "name"
    add_target_link_flags(msvcrt_new "/ignore:4102")
    add_target_property(libmsvcrt_new STATIC_LIBRARY_FLAGS "/ignore:4102")
endif()

add_importlibs(msvcrt_new kernel32 ntdll)
add_cd_file(TARGET msvcrt_new DESTINATION reactos/system32 FOR all)
