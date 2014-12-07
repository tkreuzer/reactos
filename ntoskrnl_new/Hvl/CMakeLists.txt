
add_library(ntos_hvl
    Stubs.c
)

add_dependencies(ntos_hvl psdk bugcodes asm)
