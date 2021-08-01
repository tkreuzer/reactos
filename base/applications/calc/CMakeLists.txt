
include_directories(${REACTOS_SOURCE_DIR}/sdk/lib/3rdparty/qpfloat)
include_directories(${REACTOS_SOURCE_DIR}/sdk/include/c++)

add_definitions(-DENABLE_QPFLOAT)

list(APPEND SOURCE
    convert.c
    #fun_ieee.c
    #rpn_ieee.c
    #utl_ieee.c
    fun_qpfloat.cpp
    winmain.c
    htmlhelp.c
    theme.c
    calc.h)

file(GLOB calc_rc_deps res/*.*)
add_rc_deps(resource.rc ${calc_rc_deps})
add_executable(calc ${SOURCE} resource.rc)
set_module_type(calc win32gui UNICODE)
add_importlibs(calc advapi32 comctl32 user32 shell32 gdi32 msvcrt kernel32)

if(MSVC)
    add_importlibs(calc ntdll)
endif()

#add_pch(calc calc.h SOURCE)
add_cd_file(TARGET calc DESTINATION reactos/system32 FOR all)
