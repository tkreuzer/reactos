
add_library(ntos_wmi
    Stubs.c
)

add_dependencies(ntos_wmi psdk bugcodes asm)
