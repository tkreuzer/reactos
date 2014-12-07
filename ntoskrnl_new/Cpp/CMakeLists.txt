

add_library(ntos_cpp
    CppSupport.cpp)

add_dependencies(ntos_cpp psdk bugcodes asm)
