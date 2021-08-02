
list(APPEND SOURCE
    atnat.c
    atnat2.c
    branred.c
    doasin.c
    dosincos.c
    # DPChange.c
    halfulp.c
    mpa.c
    mpatan.c
    mpatan2.c
    mpexp.c
    mplog.c
    mpsqrt.c
    mptan.c
    MSVC_DPChange.c
    sincos32.c
    slowcot.c
    slowexp.c
    slowexp2.c
    slowlog2.c
    slowpow.c
    uasncs.c
    ucot.c
    uexp.c
    uexp2.c
    ulog.c
    ulog2.c
    upow.c
    urem.c
    uroot.c
    usncs.c
    utan.c
)

add_library(apmathlib ${SOURCE})
add_dependencies(apmathlib psdk)

if(MSVC)
    target_compile_options(apmathlib PRIVATE
        /wd4189 # local variable is initialized but not referenced
        /wd4101 # unreferenced local variable
        )
endif()
