
add_executable(desktopfree_test main.c)
set_module_type(desktopfree_test win32cui)
add_importlibs(desktopfree_test msvcrt kernel32 ntdll user32)
