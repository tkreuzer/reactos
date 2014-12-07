
add_library(ntos_pcw
    Pcw.cpp
)

add_dependencies(ntos_pcw psdk bugcodes asm)
