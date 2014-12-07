
add_library(ntos_inbv
    Stubs.c
)

add_dependencies(ntos_inbv psdk bugcodes asm)
