add_definitions(-D__WINESRC__ -D_KERNEL32_ -DWINVER=0x601 -D_WIN32_WINNT=0x601)
include_directories(BEFORE ${REACTOS_SOURCE_DIR}/sdk/include/reactos/wine)

list(APPEND SOURCE
    locale.c
)

#if(DLL_EXPORT_VERSION GREATER_EQUAL 0x600)
add_library(kernelbase_static
    ${SOURCE}
)

add_dependencies(kernelbase_static psdk)
target_link_libraries(kernelbase_static PRIVATE win32_registry)
#endif()
