
add_library(ntos_tm
    Stubs.cpp
)

add_dependencies(ntos_tm psdk bugcodes asm)
