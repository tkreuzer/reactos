
include_directories(include)

add_definitions(-D_CRTBLD)

include(except/except.cmake)
include(float/float.cmake)
include(math/math.cmake)
include(mem/mem.cmake)
include(misc/misc.cmake)
include(printf/printf.cmake)
include(search/search.cmake)
include(startup/startup.cmake)
include(stdlib/stdlib.cmake)
include(string/string.cmake)
include(wstring/wstring.cmake)

include(crtmath.cmake)
include(libcntpr.cmake)
include(msvcrtex.cmake)
include(oldnames.cmake)

if(MSVC AND ARCH STREQUAL "i386")
    add_asm_files(ftol2_asm
        math/i386/ftol2_asm.s
        math/i386/ftoul2_legacy_asm.s
    )
    add_library(ftol2 ${ftol2_asm})
    set_target_properties(ftol2 PROPERTIES LINKER_LANGUAGE "C")
    add_dependencies(ftol2 asm)
endif()

add_library(dbgrpt misc/dbgrpt.cpp)
target_link_libraries(dbgrpt chkstk ${PSEH_LIB})
target_compile_definitions(dbgrpt PRIVATE
    _MT
    _DEBUG)
add_dependencies(dbgrpt psdk asm)
