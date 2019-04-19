
include_directories(
    ${REACTOS_SOURCE_DIR}
    ${REACTOS_SOURCE_DIR}/NUKE/include)

list(APPEND SOURCE
    Kd_common.c)

list(APPEND SOURCE
    Kd_amd64.c)

add_library(WinDbgKd SHARED ${SOURCE})
set_target_properties(WinDbgKd PROPERTIES SUFFIX ".sys")
set_subsystem(WinDbgKd native)

target_link_libraries(WinDbgKd
    ${PSEH_LIB}
    libcntpr
    wdmguid)

add_cd_file(TARGET WinDbgKd DESTINATION reactos/system32 NO_CAB FOR all)
add_importlib_target(WinDbgKd.spec)

