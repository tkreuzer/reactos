
list(APPEND CRT_INITIALIZERS_SOURCES
    initializers/clock_initializer.cpp
    initializers/console_input_initializer.cpp
    initializers/console_output_initializer.cpp
    initializers/fma3_initializer.cpp
    initializers/fmode_initializer.cpp
    initializers/isa_available.c
    initializers/locale_initializer.cpp
    initializers/multibyte_initializer.cpp
    initializers/section_markers.c
    initializers/stdio_initializer.cpp
    initializers/timeset_initializer.cpp
    initializers/tmpfile_initializer.cpp
)

if(${UCRT_ARCH} STREQUAL "x86" OR ${UCRT_ARCH} STREQUAL "x64")
    list(APPEND CRT_INITIALIZERS_SOURCES
        initializers/i386/sse2_initializer.cpp
    )
endif()
