
add_library(ntos_dbg
    Stubs.c
)

add_dependencies(ntos_dbg psdk bugcodes asm)
