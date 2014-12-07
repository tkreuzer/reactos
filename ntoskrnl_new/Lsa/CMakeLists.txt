
add_library(ntos_lsa
    Stubs.cpp
)

add_dependencies(ntos_lsa psdk bugcodes asm)
