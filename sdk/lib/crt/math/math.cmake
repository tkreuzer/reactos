
include_directories(libm-sse)

list(APPEND LIBCNTPR_MATH_SOURCE
    math/abs.c
    math/div.c
    math/labs.c
    math/usermatherr.c
    math/_handle_error.c
)

if(ARCH STREQUAL "i386")
    list(APPEND LIBCNTPR_MATH_SOURCE
        math/i386/ci.c
        math/i386/cicos.c
        math/i386/cilog.c
        math/i386/cipow.c
        math/i386/cisin.c
        math/i386/cisqrt.c
        math/i386/ldexp.c
    )
    list(APPEND LIBCNTPR_MATH_ASM_SOURCE
        math/i386/alldiv_asm.s
        math/i386/alldvrm_asm.s
        math/i386/allmul_asm.s
        math/i386/allrem_asm.s
        math/i386/allshl_asm.s
        math/i386/allshr_asm.s
        math/i386/atan_asm.s
        math/i386/atan2_asm.s
        math/i386/aulldiv_asm.s
        math/i386/aulldvrm_asm.s
        math/i386/aullrem_asm.s
        math/i386/aullshr_asm.s
        math/i386/ceil_asm.s
        math/i386/cos_asm.s
        math/i386/fabs_asm.s
        math/i386/floor_asm.s
        math/i386/ftol_asm.s
        math/i386/ftol2_asm.s
        math/i386/log_asm.s
        math/i386/log10_asm.s
        math/i386/pow_asm.s
        math/i386/sin_asm.s
        math/i386/sqrt_asm.s
        math/i386/tan_asm.s
    )
    list(APPEND CRT_MATH_ASM_SOURCE
        math/i386/ceilf.S
        math/i386/floorf.S
        math/i386/exp_asm.s
        math/i386/fmod_asm.s
        math/i386/fmodf_asm.s
    )
elseif(ARCH STREQUAL "amd64")
    list(APPEND LIBCNTPR_MATH_SOURCE
        # math/libm-sse/_chgsign.c
        # math/libm-sse/_chgsignf.c
        # math/libm-sse/_copysign.c
        # math/libm-sse/_copysignf.c
        math/libm-sse/atan.c
        math/libm-sse/atan2.c
        #math/libm-sse/cos.c
        # FIXME: make these portable
        math/libm-sse/cos.asm
        math/libm-sse/cosf.asm
        math/libm-sse/fma3_available.c
        math/libm-sse/remainder_piby2_forAsm.asm
        math/libm-sse/remainder_piby2_forFMA3.asm
        math/libm-sse/sin.asm
        math/libm-sse/sinf.asm
        math/libm-sse/sincos_special.c
        math/libm-sse/L2_by_pi_bits.asm
        math/libm-sse/Lsincos_array.asm
    )
    list(APPEND LIBCNTPR_MATH_ASM_SOURCE
        math/amd64/ceil.S
        math/amd64/fabs.S
        math/amd64/floor.S
        math/amd64/floorf.S
        math/amd64/fmod.S
        math/amd64/ldexp.S
        math/amd64/log.S
        math/amd64/log10.S
        math/amd64/pow.S
        math/amd64/sqrt.S
        math/amd64/tan.S
    )
    list(APPEND CRT_MATH_SOURCE
        math/libm-sse/acos.c
        math/libm-sse/acosf.c
        math/libm-sse/asin.c
        math/libm-sse/asinf.c
        math/libm-sse/atan2f.c
        math/libm-sse/atanf.c
        math/libm-sse/exp.asm
        math/libm-sse/exp_special.c
        math/libm-sse/remainder_piby2f_forAsm.asm
        math/libm-sse/Lsincosf_array.asm
        math/libm-sse/two_to_jby64_table.asm
        math/libm-sse/two_to_jby64_head_tail_table.asm
        math/libm-sse/remainder_piby2f_forC.asm
    )
elseif(ARCH STREQUAL "arm")
    list(APPEND LIBCNTPR_MATH_SOURCE
        math/cos.c
        math/floorf.c
        math/sin.c
        math/sqrt.c
        math/arm/__rt_sdiv.c
        math/arm/__rt_sdiv64_worker.c
        math/arm/__rt_udiv.c
        math/arm/__rt_udiv64_worker.c
        math/arm/__rt_div_worker.h
        math/arm/__dtoi64.c
        math/arm/__dtou64.c
        math/arm/__stoi64.c
        math/arm/__stou64.c
        math/arm/__fto64.h
        math/arm/__i64tod.c
        math/arm/__u64tod.c
        math/arm/__i64tos.c
        math/arm/__u64tos.c
        math/arm/__64tof.h
    )
    list(APPEND CRT_MATH_SOURCE
        math/acosf.c
        math/asinf.c
        math/atan2f.c
        math/atanf.c
        math/fabsf.c
        math/sinf.c
    )
    list(APPEND LIBCNTPR_MATH_ASM_SOURCE
        math/arm/atan.s
        math/arm/atan2.s
        math/arm/ceil.s
        math/arm/exp.s
        math/arm/fabs.s
        math/arm/fmod.s
        math/arm/floor.s
        math/arm/ldexp.s
        math/arm/log.s
        math/arm/log10.s
        math/arm/pow.s
        math/arm/tan.s
        math/arm/__rt_sdiv64.s
        math/arm/__rt_srsh.s
        math/arm/__rt_udiv64.s
    )
    list(APPEND CRT_MATH_ASM_SOURCE
        math/arm/_logb.s
    )
endif()

if(NOT ARCH STREQUAL "i386")
    list(APPEND CRT_MATH_SOURCE
        math/_chgsignf.c
        math/_copysignf.c
        math/_hypotf.c
        math/ceilf.c
        math/coshf.c
        math/expf.c
        math/fmodf.c
        math/log10f.c
        math/modff.c
        math/sinhf.c
        math/sqrtf.c
        math/tanf.c
        math/tanhf.c
        math/stubs.c
    )
endif()

list(APPEND CRT_MATH_SOURCE
    ${LIBCNTPR_MATH_SOURCE}
    math/adjust.c
    math/cabs.c
    math/cosh.c
    math/fdivbug.c
    math/frexp.c
    math/huge_val.c
    math/hypot.c
    math/ieee754/j0_y0.c
    math/ieee754/j1_y1.c
    math/ieee754/jn_yn.c
    math/j0_y0.c
    math/j1_y1.c
    math/jn_yn.c
    math/ldiv.c
    math/logf.c
    math/modf.c
    math/powf.c
    math/rand.c
    math/s_modf.c
    math/sinh.c
    math/tanh.c
)

if(NOT ARCH STREQUAL "amd64")
    list(APPEND CRT_MATH_SOURCE
        math/acos.c
        math/asin.c
        math/cosf.c
    )
endif()

list(APPEND CRT_MATH_ASM_SOURCE
    ${LIBCNTPR_MATH_ASM_SOURCE}
)

list(APPEND LIBCNTPR_MATH_SOURCE
    math/rand_nt.c
)

if(ARCH STREQUAL "i386")
    list(APPEND ATAN2_ASM_SOURCE math/i386/atan2_asm.s)
elseif(ARCH STREQUAL "amd64")
    list(APPEND ATAN2_ASM_SOURCE math/amd64/atan2.S)
elseif(ARCH STREQUAL "arm")
    list(APPEND ATAN2_ASM_SOURCE math/arm/atan2.s)
elseif(ARCH STREQUAL "arm64")
    list(APPEND ATAN2_ASM_SOURCE math/arm64/atan2.s)
endif()

add_asm_files(atan2_asm ${ATAN2_ASM_SOURCE})
add_library(atan2 ${atan2_asm})
set_target_properties(atan2 PROPERTIES LINKER_LANGUAGE "C")
add_dependencies(atan2 asm)
