
add_library(ntos_po
    Callback.cpp
    Device.cpp
    Misc.cpp
    Notify.cpp
    PoFx.cpp
    PowerRequest.cpp
    Shutdown.cpp
    SystemState.cpp
    Wake.cpp
)

add_dependencies(ntos_po psdk bugcodes asm)
