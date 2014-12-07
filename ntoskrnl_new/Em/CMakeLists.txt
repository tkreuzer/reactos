
add_library(ntos_em
    Stubs.c
)

add_dependencies(ntos_em psdk bugcodes asm)
