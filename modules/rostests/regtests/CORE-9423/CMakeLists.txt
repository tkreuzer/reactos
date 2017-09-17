
list(APPEND SOURCE
    CORE-9423-test.c)

add_executable(CORE-9423-test ${SOURCE})

set_module_type(CORE-9423-test win32gui)
add_importlibs(CORE-9423-test gdi32 user32 msvcrt kernel32 ntdll)
add_cd_file(TARGET CORE-9423-test DESTINATION reactos/bin FOR all)
