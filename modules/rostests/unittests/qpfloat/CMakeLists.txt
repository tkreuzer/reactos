
include_directories(${REACTOS_SOURCE_DIR}/sdk/lib/3rdparty/qpfloat)
include_directories(${REACTOS_SOURCE_DIR}/sdk/include/c++)

list(APPEND SOURCE
    BasicOperations.cpp
    testlist.c)

add_executable(qpfloat_unittest ${SOURCE})
set_module_type(qpfloat_unittest win32cui)
target_link_libraries(qpfloat_unittest qpfloat)
add_importlibs(qpfloat_unittest msvcrt kernel32 ntdll)
