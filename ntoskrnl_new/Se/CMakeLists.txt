
add_library(ntos_se
    Stubs.c
)

add_dependencies(ntos_se psdk bugcodes asm)
