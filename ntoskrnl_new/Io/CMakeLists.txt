
add_library(ntos_io
    Stubs.cpp
)

add_dependencies(ntos_io psdk bugcodes asm)
