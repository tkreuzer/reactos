
add_library(ntos_vf
    Stubs.cpp
)

add_dependencies(ntos_vf psdk bugcodes asm)
