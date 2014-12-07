
add_library(ntos_mm
    CopyMemory.cpp
    ContiguousMemory.cpp
    KernelStack.cpp
    Mapping.cpp
    Mdl.cpp
    PageFault.cpp
    PhysicalMemory.cpp
    Prefetch.cpp
    Section.cpp
    Session.cpp
    SysLoader.cpp
    Verifier.cpp
    VirtualMemory.cpp
    WorkingSet.cpp
    Stubs.c
)

add_dependencies(ntos_mm psdk bugcodes asm)
