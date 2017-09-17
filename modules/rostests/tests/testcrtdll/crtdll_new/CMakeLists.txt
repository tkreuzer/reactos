
spec2def(crtdll_new.dll crtdll_new.spec ADD_IMPORTLIB)

set(baseaddress_crtdll_new 0x1000000)

add_library(crtdll_new SHARED
    dllmain.c
    ${CMAKE_CURRENT_BINARY_DIR}/crtdll_new.def)

set_module_type(crtdll_new win32dll ENTRYPOINT 0)
add_importlibs(crtdll_new msvcrt_new)

