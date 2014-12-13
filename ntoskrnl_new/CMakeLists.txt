
PROJECT(NTOSNEW)

if (NOT MSVC)
    add_compile_flags_language("-std=c++11" "CXX")
    #add_compile_flags("-fno-exceptions")
    #add_compile_flags("-fno-rtti")
endif()

add_definitions(
    -D__NTOSKRNL__
    -D_NTOSKRNL_
    -D_NTSYSTEM_
    -D_IN_KERNEL_
    -DNTDDI_VERSION=0x05020400)

include_directories(BEFORE
    .
    ./include
    ${REACTOS_SOURCE_DIR}
    ${REACTOS_SOURCE_DIR}/lib/cmlib
    ${REACTOS_SOURCE_DIR}/include/reactos/drivers)

add_subdirectory(Alpc)
add_subdirectory(Cc)
add_subdirectory(Cm)
add_subdirectory(Cpp)
add_subdirectory(Dbg)
add_subdirectory(Em)
add_subdirectory(Etw)
add_subdirectory(Ex)
add_subdirectory(FsRtl)
add_subdirectory(Inbv)
add_subdirectory(Io)
add_subdirectory(Kd)
add_subdirectory(Ke)
add_subdirectory(Ldr)
add_subdirectory(Lsa)
add_subdirectory(Mm)
add_subdirectory(NtApi)
add_subdirectory(Ob)
add_subdirectory(Pcw)
add_subdirectory(Po)
add_subdirectory(Ps)
add_subdirectory(Rtl)
add_subdirectory(Se)
add_subdirectory(Tm)
add_subdirectory(Vf)
add_subdirectory(Wmi)

#spec2def(ntoskrnl.exe ntoskrnl.spec ADD_IMPORTLIB)
spec2def(ntoskrnl.exe ntoskrnl.spec)

add_executable(ntoskrnl_new
    ${CMAKE_CURRENT_BINARY_DIR}/ntoskrnl_stubs.c
    #guid.c
    stubs.c
    ntoskrnl.rc
    ${CMAKE_CURRENT_BINARY_DIR}/ntoskrnl.def)

set_entrypoint(ntoskrnl_new KiSystemStartup 4)
set_subsystem(ntoskrnl_new native)

if(MSVC)
    set_image_base(ntoskrnl_new 0x00400000)
else()
    if(GDB)
        set_image_base(ntoskrnl_new 0x00800000)
    else()
        set_image_base(ntoskrnl_new 0x80800000)
    endif()
endif()

target_link_libraries(ntoskrnl_new
    ntos_alpc
    ntos_cc
    ntos_cm
    ntos_cpp
    ntos_dbg
    ntos_em
    ntos_etw
    ntos_ex
    ntos_fsrtl
    ntos_inbv
    ntos_io
    ntos_kd
    ntos_ke
    ntos_ldr
    ntos_lsa
    ntos_mm
    ntos_ntapi
    ntos_ob
    ntos_pcw
    ntos_po
    ntos_ps
    ntos_rtl
    ntos_se
    ntos_tm
    ntos_vf
    ntos_wmi
    cportlib
    csq
    ${PSEH_LIB}
    cmlib
    rtl
    ${ROSSYM_LIB}
    libcntpr
    wdmguid
    ioevent)

if(NOT MSVC)
   # target_link_libraries(ntoskrnl -lgcc)
endif()

if(STACK_PROTECTOR)
    target_link_libraries(ntoskrnl_new gcc_ssp)
#elseif(RUNTIME_CHECKS)
#    target_link_libraries(ntoskrnl_new runtmchk)
endif()

add_importlibs(ntoskrnl_new hal kdcom bootvid)
#add_pch(ntoskrnl_new ${REACTOS_SOURCE_DIR}/ntoskrnl/include/ntoskrnl.h NTOSKRNL_SOURCE)
add_dependencies(ntoskrnl_new psdk bugcodes asm)
#add_cd_file(TARGET ntoskrnl_new DESTINATION reactos/system32 NO_CAB FOR all)

#add_asm_files(ntdllsys_asm ntdll.S)
#add_library(ntdllsys ${ntdllsys_asm})
#set_target_properties(ntdllsys PROPERTIES LINKER_LANGUAGE "C")
