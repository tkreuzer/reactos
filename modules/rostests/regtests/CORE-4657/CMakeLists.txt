
add_executable(MetricsTest MetricsTest.cpp)
set_module_type(MetricsTest win32gui)
add_importlibs(MetricsTest msvcrt kernel32 gdi32 user32)
