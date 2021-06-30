
include_directories(${REACTOS_SOURCE_DIR}/sdk/include/reactos/wine)

list(APPEND SOURCE
    config.c
    debug_ros.c
    isinf.c
    isfinite.c
    isnan.c
    loader.c
    ${REACTOS_SOURCE_DIR}/sdk/lib/crt/string/wctype.c
    path.c
    register.c
#    string.c implements _stricmp, already shipped with crt
)

add_library(wine ${SOURCE})
add_dependencies(wine psdk)
target_compile_definitions(wine PRIVATE __WINESRC__ _WINE)

if(MSVC AND ARCH STREQUAL "amd64")
    # Disable warning C4267: '=': conversion from 'size_t' to 'int', possible loss of data
    target_compile_options(wine PRIVATE /wd4267)
endif()

add_library(wineldr loader.c)
add_dependencies(wineldr xdk)
target_compile_definitions(wineldr PRIVATE __WINESRC__)

add_library(wine_dll_register dll_register.c ${SOURCE})
add_dependencies(wine_dll_register psdk)
target_compile_definitions(wine_dll_register PRIVATE __WINESRC__ _WINE)
