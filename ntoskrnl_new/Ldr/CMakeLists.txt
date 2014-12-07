
add_library(ntos_ldr
    Resource.cpp
)

add_dependencies(ntos_ldr psdk bugcodes asm)
