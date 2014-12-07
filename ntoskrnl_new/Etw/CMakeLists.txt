
add_library(ntos_etw
    Stubs.c
)

add_dependencies(ntos_etw psdk bugcodes asm)
