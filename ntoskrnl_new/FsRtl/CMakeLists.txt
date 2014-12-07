
add_library(ntos_fsrtl
    Stubs.c
)

add_dependencies(ntos_fsrtl psdk bugcodes asm)
