replace_compile_flags("/Ob0 /Od" "/Ox")
add_library(ntos_ob
    DeviceMap.cpp
    Directory.cpp
    FastRef.cpp
    Handle.cpp
    Information.cpp
    Object.cpp
    ObjectType.cpp
    ObjMgr.cpp
    Process.cpp
    Reference.cpp
    Security.cpp
    Wait.cpp
)

add_dependencies(ntos_ob psdk bugcodes asm)
