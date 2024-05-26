
if(MSVC)
    # Disable warning C4083: expected ')'; found identifier '<warning identifier>'
    add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:/wd4083>)

    # Disable warning C4189: 'cvt': local variable is initialized but not referenced
    add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:/wd4189>)
endif()

# Internal includes
include_directories(BEFORE inc)

if(${ARCH} STREQUAL "i386")
    include_directories(inc/i386)
endif()

# Make sure we have the required architecture macros defined
if(${ARCH} STREQUAL "i386")
    add_compile_definitions(_M_IX86 _X86_)
    set(UCRT_ARCH "x86")
elseif(${ARCH} STREQUAL "amd64")
    add_compile_definitions(_M_X64 _AMD64_)
    set(UCRT_ARCH "x64")
elseif(${ARCH} STREQUAL "arm")
    add_compile_definitions(_M_ARM _ARM_)
    set(UCRT_ARCH "arm")
elseif(${ARCH} STREQUAL "arm64")
    add_compile_definitions(_M_ARM64 _ARM64_)
    set(UCRT_ARCH "arm64")
elseif(${ARCH} STREQUAL "ia64")
    add_compile_definitions(_M_IA64 _IA64_)
    set(UCRT_ARCH "ia64")
endif()

add_compile_definitions(
    WINVER=0x600
    _WIN32_WINNT=0x600
    _UCRT
    _CORECRT_BUILD
    _CRT_DECLARE_GLOBAL_VARIABLES_DIRECTLY
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_DEBUG)
endif()

include(conio/conio.cmake)
include(convert/convert.cmake)
include(dll/dll.cmake)
include(env/env.cmake)
include(exec/exec.cmake)
include(filesystem/filesystem.cmake)
include(heap/heap.cmake)
include(initializers/initializers.cmake)
include(internal/internal.cmake)
include(locale/locale.cmake)
include(lowio/lowio.cmake)
include(math/math.cmake)
include(mbstring/mbstring.cmake)
include(misc/misc.cmake)
include(startup/startup.cmake)
include(stdio/stdio.cmake)
include(stdlib/stdlib.cmake)
include(string/string.cmake)
include(time/time.cmake)
include(vcruntime/vcruntime.cmake)

add_library(ucrt
    ${CRT_CONIO_SOURCES}
    ${CRT_CONVERT_SOURCES}
    ${CRT_DLL_SOURCES}
    ${CRT_ENV_SOURCES}
    ${CRT_EXEC_SOURCES}
    ${CRT_FILESYSTEM_SOURCES}
    ${CRT_HEAP_SOURCES}
    ${CRT_INITIALIZERS_SOURCES}
    ${CRT_INTERNAL_SOURCES}
    ${CRT_LOCALE_SOURCES}
    ${CRT_LOWIO_SOURCES}
    ${CRT_MATH_SOURCES}
    ${CRT_MBSTRING_SOURCES}
    ${CRT_MISC_SOURCES}
    ${CRT_STARTUP_SOURCES}
    ${CRT_STDIO_SOURCES}
    ${CRT_STDLIB_SOURCES}
    ${CRT_STRING_SOURCES}
    ${CRT_TIME_SOURCES}
    ${CRT_VCRUNTIME_SOURCES}
)

add_library(liboucrtdll
    ${CRTDLL_DLL_SOURCES}
)
target_compile_definitions(liboucrtdll PRIVATE CRTDLL)

add_dependencies(ucrt psdk asm)
