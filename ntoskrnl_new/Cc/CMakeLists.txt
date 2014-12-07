
add_library(ntos_cc
    SharedCacheMap.cpp
    Stubs.c
)

add_dependencies(ntos_cc psdk bugcodes asm)
