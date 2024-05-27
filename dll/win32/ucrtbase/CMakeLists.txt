
spec2def(ucrtbase.dll ucrtbase.spec)

add_library(ucrtbase SHARED
    stubs.c
    ucrtbase_stubs.c
    ucrtbase.def
)

if(MSVC)
    # Disable default libraries
    target_link_options(ucrtbase PRIVATE "/NODEFAULTLIB:MSVCRTD")

    # Set entrypoint
    target_link_options(ucrtbase PRIVATE "/ENTRY:__acrt_DllMain")
else()
endif()

target_link_libraries(ucrtbase
    ucrt
    ucrtdll
    runtmchk
)

add_importlibs(ucrtbase kernel32 ntdll)
