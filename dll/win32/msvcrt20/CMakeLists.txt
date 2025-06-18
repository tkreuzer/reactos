
spec2def(msvcrt20.dll msvcrt20.spec)

add_definitions(
    -D_CRTIMP=
)

add_library(msvcrt20 MODULE
    msvcrt20.c
    ${CMAKE_CURRENT_BINARY_DIR}/msvcrt20_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/msvcrt20.def)

target_compile_definitions(msvcrt20 PRIVATE _MSVCR_VER=0)
set_module_type(msvcrt20 win32dll ENTRYPOINT DllMain 12)
target_link_libraries(msvcrt20 msvcrt_static crtmath vcruntime wine chkstk ${PSEH_LIB})
add_importlibs(msvcrt20 kernel32 kernel32_vista ntdll)
add_delay_importlibs(msvcrt20 user32 advapi32)

if(MSVC)
    # export of deleting destructor "name"
    target_link_options(msvcrt20 PRIVATE "/ignore:4102")
endif()

add_cd_file(TARGET msvcrt20 DESTINATION reactos/system32 FOR all)
