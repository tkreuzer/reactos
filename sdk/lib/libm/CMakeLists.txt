
include_directories(include)

if(WIN32)
    add_definitions(-DWINDOWS=1)
    if (CMAKE_CL_64)
        add_definitions(-DWIN64)
    endif()
endif()

list(APPEND REF_SOURCES
    src/ref/acos.c
    src/ref/acosf.c
    src/ref/acosh.c
    src/ref/acoshf.c
    src/ref/asin.c
    src/ref/asinf.c
    src/ref/asinh.c
    src/ref/asinhf.c
    src/ref/atan.c
    src/ref/atan2.c
    src/ref/atan2f.c
    src/ref/atanf.c
    src/ref/atanh.c
    src/ref/atanhf.c
    src/ref/ceil.c
    src/ref/ceilf.c
    src/ref/cosh.c
    src/ref/coshf.c
    src/ref/cospi.c
    src/ref/cospif.c
    src/ref/exp_tables.c
    src/ref/finite.c
    src/ref/finitef.c
    src/ref/floor.c
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
    src/ref/remainder_piby2.c
    src/ref/remainder_piby2d2f.c
    src/ref/remquo.c
    src/ref/remquof.c
    src/ref/rint.c
    src/ref/rintf.c
    src/ref/roundf.c
    src/ref/scalbln.c
    src/ref/scalblnf.c
    src/ref/scalbn.c
    src/ref/scalbnf.c
    src/ref/sinh.c
    src/ref/sinhf.c
    src/ref/sinpi.c
    src/ref/sinpif.c
    src/ref/sqrt.c
    src/ref/sqrtf.c
    src/ref/tan.c
    src/ref/tanf.c
    src/ref/tanh.c
    src/ref/tanhf.c
    src/ref/tanpi.c
    src/ref/tanpif.c
    src/ref/vrd2_cosh.c
    src/ref/vrd4_expm1.c
)

list(APPEND LIBM_SOURCES
    ${REF_SOURCES}
)

add_library(libm OBJECT
    ${LIBM_SOURCES}
)
