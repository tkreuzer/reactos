
add_library(ntos_alpc
    Stubs.c
)

add_dependencies(ntos_alpc psdk bugcodes asm)
