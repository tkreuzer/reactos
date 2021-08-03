
include_directories(
    ${REACTOS_SOURCE_DIR}/sdk/lib/3rdparty/apmathlib)

list(APPEND SOURCE
	main.c
)

add_executable(math_test_table_gen ${SOURCE})
set_module_type(math_test_table_gen win32cui)
add_importlibs(math_test_table_gen user32 comctl32 psapi msvcrt kernel32 ntdll)
target_link_libraries(math_test_table_gen apmathlib)
