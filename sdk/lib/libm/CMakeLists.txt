
include_directories(include)

add_definitions(-Disinf=!_finite)

if (MSVC)
    add_definitions(-D__MSVC)
    #add_definitions(-DWINDOWS=1)
else()
    add_definitions(-D__GNUC)
endif()

if(WIN32)
    add_definitions(-DWINDOWS=1)
    if (CMAKE_CL_64)
        add_definitions(-DWIN64)
    endif()
endif()

add_definitions(
    -Damd_ref_ldexp=ldexp
    -Damd_log1p=log1p
)

if (${ARCH} STREQUAL "amd64")
    add_definitions(
        -Damd_ref_atan=atan
        -Damd_ref_atan2=atan2
        -Damd_opt_log=log
        -Damd_opt_pow=pow
        -Damd_ref_tan=tan
    )
else()
    add_definitions(
        #__libm_sse2_acos
        #__libm_sse2_acosf
        #__libm_sse2_asin
        #__libm_sse2_asinf
        -Damd_ref_atan=__libm_sse2_atan
        -Damd_ref_atan2__libm_sse2_atan2
        #__libm_sse2_atanf
        #__libm_sse2_cos
        #__libm_sse2_cosf
        #__libm_sse2_exp
        #__libm_sse2_expf
        -Damd_opt_log=__libm_sse2_log
        #__libm_sse2_log10
        #__libm_sse2_log10f
        #__libm_sse2_logf
        -Damd_opt_pow=__libm_sse2_pow
        #__libm_sse2_powf
        #__libm_sse2_sin
        #__libm_sse2_sinf
        -Damd_ref_tan=__libm_sse2_tan
        #__libm_sse2_tanf
    )
endif()

list(APPEND SOURCES_BASE
    src/libm_special.c
    src/ref/atan.c
    src/ref/ceil.c
    #src/ref/cospi.c
    #src/optmized/cos.c
    src/ref/floor.c
    src/optmized/log.c
    src/optmized/log_tables.c
    src/optmized/pow.c
    src/optmized/pow_data.c
    #src/ref/remainder_piby2.c
    #src/ref/sinpi.c
    #src/optmized/sin.c
    #src/ref/sqrt.c
    src/ref/tan.c
)

if (MSVC)
else()
list(APPEND SOURCES_BASE
    #src/ref/remainder_piby2.c
    #src/ref/remainder_piby2d2f.c
)
endif()

list(APPEND REF_SOURCES
    src/ref/acos.c
    src/ref/acosf.c
    #src/ref/acosh.c
    #src/ref/acoshf.c
    src/ref/asin.c
    src/ref/asinf.c
    #src/ref/asinh.c
    #src/ref/asinhf.c
    src/ref/atan2.c
    src/ref/atan2f.c
    src/ref/atanf.c
    #src/ref/atanh.c
    #src/ref/atanhf.c
    src/ref/ceilf.c
    src/ref/cosh.c
    src/ref/coshf.c
    src/ref/cospif.c
    src/ref/exp_tables.c
    src/ref/finite.c
    src/ref/finitef.c
    src/ref/floorf.c
    src/ref/frexp.c
    src/ref/frexpf.c
    src/ref/hypot.c
    src/ref/hypotf.c
    src/ref/ilogb.c
    src/ref/ilogbf.c
    src/ref/ldexp.c
    src/ref/ldexpf.c
    src/ref/llrint.c
    src/ref/llrintf.c
    src/ref/llround.c
    src/ref/llroundf.c
    src/ref/logb.c
    src/ref/logbf.c
    src/ref/lrint.c
    src/ref/lrintf.c
    src/ref/lround.c
    src/ref/lroundf.c
    src/ref/modf.c
    src/ref/modff.c
    src/ref/nan.c
    src/ref/nanf.c
    src/ref/nearbyintf.c
    src/ref/nextafter.c
    src/ref/nextafterf.c
    src/ref/nexttoward.c
    src/ref/nexttowardf.c
    #src/ref/remainder_piby2d2f.c
    #src/ref/remquo.c
    #src/ref/remquof.c
    src/ref/rint.c
    src/ref/rintf.c
    src/ref/roundf.c
    src/ref/scalbln.c
    src/ref/scalblnf.c
    src/ref/scalbn.c
    src/ref/scalbnf.c
    src/ref/sinh.c
    src/ref/sinhf.c
    src/ref/sinpif.c
    src/ref/sqrtf.c
    src/ref/tanf.c
    src/ref/tanh.c
    src/ref/tanhf.c
    src/ref/tanpi.c
    src/ref/tanpif.c
    #src/ref/vrd2_cosh.c
    #src/ref/vrd4_expm1.c
)

list(APPEND LIBM_ASM_SOURCES
    src/isa/avx/remainder_piby2_new.asm
)

list(APPEND LIBM_SOURCES
    ${REF_SOURCES}
)

add_library(libm_base
    ${SOURCES_BASE}
    ${LIBM_ASM_SOURCES}
)

add_library(libm_atan2 OBJECT
    src/ref/atan2.c
)

if (MSVC)
#add_definitions(-D__SSE__)

else()
    target_compile_options(libm_base PRIVATE -Wno-bool-compare)
    target_compile_options(libm_base PRIVATE -Wno-logical-not-parentheses)
    target_compile_options(libm_base PRIVATE -Wno-psabi)
    target_compile_options(libm_atan2 PRIVATE -Wno-psabi)
endif()
