
add_library(ntos_ps
    Impersonation.cpp
    Job.cpp
    Misc.cpp
    Module.cpp
    Process.cpp
    Thread.cpp
)

add_dependencies(ntos_ps psdk bugcodes asm)
