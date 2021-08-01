
include_directories(
    ${REACTOS_SOURCE_DIR}/sdk/include/c++)

list(APPEND SOURCE
    AssemblyInfo.cpp
    DoubleDecomposition.cpp
    Helpers.cpp
    Stdafx.cpp
    __float128.cpp
)

add_library(qpfloat MODULE ${SOURCE})
add_dependencies(qpfloat psdk)
add_importlibs(qpfloat msvcrt kernel32 ntdll)
target_link_libraries(qpfloat cpprt)
set_module_type(qpfloat win32dll UNICODE)
