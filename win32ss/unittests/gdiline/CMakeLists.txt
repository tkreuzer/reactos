
add_executable(LinesTest LinesTest.cpp Line.cpp)
set_module_type(LinesTest win32gui)
add_importlibs(LinesTest msvcrt kernel32 gdi32 user32)
