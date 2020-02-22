
add_definitions(
    -DOPT_I386
    -DREAL_IS_FLOAT
    -DNOXFERMEM
    -DHAVE_CONFIG_H
    -DEOVERFLOW=75
    -Dlseek=_lseek
    -Dread=_read
    -Dstrdup=_strdup
    -D_CRT_NONSTDC_NO_DEPRECATE
    -D_DLL -D__USE_CRTIMP
    -D_CRT_NO_POSIX_ERROR_CODES)

include_directories(BEFORE ${REACTOS_SOURCE_DIR}/sdk/include/reactos/libs/libmpg123)

list(APPEND SOURCE
    compat/compat.c
    compat/compat_str.c
    dct64.c
    dct64_i386.c
    equalizer.c
    feature.c
    format.c
    frame.c
    icy.c
    icy2utf8.c
    id3.c
    index.c
    layer1.c
    layer2.c
    layer3.c
    libmpg123.c
    ntom.c
    parse.c
    readers.c
    stringbuf.c
    synth.c
    synth_8bit.c
    synth_real.c
    synth_s32.c
    tabinit.c)

list(APPEND PCH_SKIP_SOURCE
    optimize.c)

add_library(libmpg123
    ${SOURCE}
    ${PCH_SKIP_SOURCE})

if (MSVC)
    if (ARCH STREQUAL "amd64")
        # Disable warning C4267: '=': conversion from 'size_t' to 'int', possible loss of data
        # Disable warning C4334: '<<': result of 32-bit shift implicitly converted to 64 bits (was 64-bit shift intended?)
        target_compile_options(libmpg123 PRIVATE /wd4267 /wd4334)
    endif()
endif()

add_dependencies(libmpg123 psdk)
add_pch(libmpg123 precomp.h "${PCH_SKIP_SOURCE}")
