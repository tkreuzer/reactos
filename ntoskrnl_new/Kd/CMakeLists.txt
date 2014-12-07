
add_library(ntos_kd
    Stubs.c
)

add_dependencies(ntos_kd psdk bugcodes asm)
