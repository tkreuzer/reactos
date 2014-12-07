
add_library(ntos_cm
    Stubs.c
)

add_dependencies(ntos_cm psdk bugcodes asm)
