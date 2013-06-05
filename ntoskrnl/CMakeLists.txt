
PROJECT(NTOS)

if (GCC)
    # Enable this again. CORE-17637
    add_compile_options(-Wunused-result)
endif()

include(ntos.cmake)

if(NOT MSVC)
    # Make sure we don't duplicate some symbols
    add_compile_options(-fno-common)
endif()

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-exceptions -fno-rtti")
endif()

include_directories(
    ${REACTOS_SOURCE_DIR}
    ${REACTOS_SOURCE_DIR}/lib/cmlib
    include
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include/internal
    ${REACTOS_SOURCE_DIR}/include/reactos/drivers)

set(NTKRNLMP_SOURCE ${SOURCE})
set(NTKRNLMP_ASM_SOURCE ${ASM_SOURCE})

spec2def(ntoskrnl.exe ntoskrnl.spec ADD_IMPORTLIB)

# Embed RTC libs
if (STACK_PROTECTOR)
    target_sources(libntoskrnl PRIVATE $<TARGET_OBJECTS:gcc_ssp_nt>)
endif()

add_asm_files(ntoskrnl_asm ${NTOSKRNL_ASM_SOURCE})

set(NEWCC TRUE)

if(NEWCC)
    add_definitions(-DNEWCC)
    list(APPEND SOURCE
        #cache/cachesub.c
        #cache/copysup.c
        #cache/fssup.c
        #cache/lazyrite.c
        #cache/logsup.c
        #cache/mdlsup.c
        #cache/pinsup.c
)
else()
    list(APPEND SOURCE
        cc/cacheman.c
        cc/copy.c
        cc/fs.c
        cc/mdl.c
        cc/pin.c
        cc/view.c)
endif()

list(APPEND SOURCE
    #cache/section/io.c
    #cache/section/data.c
    #cache/section/fault.c
    #cache/section/reqtools.c
    #cache/section/sptab.c
    #cache/section/swapout.c
    config/cmalloc.c
    config/cmapi.c
    config/cmboot.c
    config/cmcheck.c
    config/cmconfig.c
    config/cmcontrl.c
    config/cmdata.c
    config/cmdelay.c
    config/cmhook.c
    config/cmhvlist.c
    config/cmindex.c
    config/cminit.c
    config/cmkcbncb.c
    config/cmkeydel.c
    config/cmlazy.c
    config/cmmapvw.c
    config/cmname.c
    config/cmnotify.c
    config/cmparse.c
    config/cmquota.c
    config/cmse.c
    config/cmsecach.c
    config/cmsysini.c
    config/cmvalche.c
    config/cmvalue.c
    config/cmwraprs.c
    config/ntapi.c
    dbgk/dbgkobj.c
    dbgk/dbgkutil.c
    ex/atom.c
    ex/callback.c
    ex/dbgctrl.c
    ex/efi.c
    ex/event.c
    ex/evtpair.c
    ex/exintrin.c
    ex/fmutex.c
    ex/handle.c
    ex/harderr.c
    ex/hdlsterm.c
    ex/init.c
    ex/interlocked.c
    ex/keyedevt.c
    ex/locale.c
    ex/lookas.c
    ex/mutant.c
    ex/profile.c
    ex/pushlock.c
    ex/resource.c
    ex/rundown.c
    ex/sem.c
    ex/shutdown.c
    ex/sysinfo.c
    ex/time.c
    ex/timer.c
    ex/uuid.c
    ex/win32k.c
    ex/work.c
    ex/xipdisp.c
    ex/zone.c
    fsrtl/dbcsname.c
    fsrtl/fastio.c
    fsrtl/faulttol.c
    fsrtl/filelock.c
    fsrtl/filter.c
    fsrtl/filtrctx.c
    fsrtl/fsfilter.c
    fsrtl/fsrtlpc.c
    fsrtl/largemcb.c
    fsrtl/mcb.c
    fsrtl/name.c
    fsrtl/notify.c
    fsrtl/oplock.c
    fsrtl/pnp.c
    fsrtl/stackovf.c
    fsrtl/tunnel.c
    fsrtl/unc.c
    fstub/disksup.c
    fstub/fstubex.c
    fstub/halstub.c
    fstub/translate.c
    inbv/inbv.c
    inbv/inbvport.c
    io/iomgr/adapter.c
    io/iomgr/arcname.c
    io/iomgr/bootlog.c
    io/iomgr/controller.c
    io/iomgr/device.c
    io/iomgr/deviface.c
    io/iomgr/driver.c
    io/iomgr/error.c
    io/iomgr/file.c
    io/iomgr/iocomp.c
    io/iomgr/ioevent.c
    io/iomgr/iofunc.c
    io/iomgr/iomdl.c
    io/iomgr/iomgr.c
    io/iomgr/iorsrce.c
    io/iomgr/iotimer.c
    io/iomgr/iowork.c
    io/iomgr/irp.c
    io/iomgr/irq.c
    io/iomgr/ramdisk.c
    io/iomgr/rawfs.c
    io/iomgr/remlock.c
    io/iomgr/symlink.c
    io/iomgr/util.c
    io/iomgr/volume.c
    io/pnpmgr/plugplay.c
    io/pnpmgr/pnpdma.c
    io/pnpmgr/pnpinit.c
    io/pnpmgr/pnpmgr.c
    io/pnpmgr/pnpnotify.c
    io/pnpmgr/pnpreport.c
    io/pnpmgr/pnpres.c
    io/pnpmgr/pnproot.c
    io/pnpmgr/pnputil.c
    ke/apc.c
    ke/balmgr.c
    ke/bug.c
    ke/clock.c
    ke/config.c
    ke/devqueue.c
    ke/dpc.c
    ke/eventobj.c
    ke/except.c
    ke/freeze.c
    ke/gate.c
    ke/gmutex.c
    ke/ipi.c
    ke/krnlinit.c
    ke/mutex.c
    ke/procobj.c
    ke/profobj.c
    ke/queue.c
    ke/semphobj.c
    ke/spinlock.c
    ke/thrdobj.c
    ke/thrdschd.c
    ke/time.c
    ke/timerobj.c
    ke/wait.c
    lpc/close.c
    lpc/complete.c
    lpc/connect.c
    lpc/create.c
    lpc/listen.c
    lpc/port.c
    lpc/reply.c
    lpc/send.c
#    mm/ARM3/contmem.c
#    mm/ARM3/drvmgmt.c
#    mm/ARM3/dynamic.c
    mm/ARM3/expool.c
#    mm/ARM3/hypermap.c
#    mm/ARM3/iosup.c
#    mm/ARM3/largepag.c
#    mm/ARM3/mdlsup.c
#    mm/ARM3/mmdbg.c
#    mm/ARM3/mminit.c
#    mm/ARM3/mmsup.c
#    mm/ARM3/ncache.c
#    mm/ARM3/pagfault.c
#    mm/ARM3/pfnlist.c
#    mm/ARM3/pool.c
#    mm/ARM3/procsup.c
#    mm/ARM3/section.c
#    mm/ARM3/session.c
#    mm/ARM3/special.c
#    mm/ARM3/sysldr.c
#    mm/ARM3/syspte.c
#    mm/ARM3/vadnode.c
#    mm/ARM3/virtual.c
#    mm/ARM3/zeropage.c
#    mm/balance.c
#    mm/freelist.c
#    mm/marea.c
#    mm/mmfault.c
#    mm/mminit.c
#    mm/pagefile.c
#    mm/region.c
#    mm/rmap.c
#    mm/section.c
#########################
    Mm_new/SectionObject.cpp
    Mm_new/VadTable.cpp
    Mm_new/ControlArea.cpp
    Mm_new/Segment.cpp
    Mm_New/PageFault.cpp
    Mm_New/MmData.cpp
    Mm_New/PoolSupport.cpp
    Mm_New/Init.cpp
    Mm_New/Mdl.cpp
    Mm_New/ContiguousMemory.cpp
    Mm_New/SectionView.cpp
    Mm_New/VirtualMemory.cpp
    Mm_New/PhysicalMemory.cpp
    Mm_New/Mapping.cpp
    Mm_New/KernelStack.cpp
    Mm_New/Session.cpp
    Mm_New/ProcessSupport.cpp
    Mm_New/DriverSupport.cpp
    Mm_New/PfnDatabase.cpp
    Mm_New/DebugSupport.cpp
    Mm_New/PhysicalSection.cpp
    Mm_New/ImageSection.cpp
    Mm_New/CommitCharge.cpp
    Mm_New/KernelVad.cpp
    Mm_New/AddressSpace.cpp
    Mm_New/PageTables.cpp
    Mm_New/Paging.cpp
    Mm_New/Stubs.cpp
    Mm_New/Cc/Stubs.cpp
#########################
    ob/obdir.c
    ob/obhandle.c
    ob/obinit.c
    ob/oblife.c
    ob/oblink.c
    ob/obname.c
    ob/obref.c
    ob/obsdcach.c
    ob/obsecure.c
    ob/obwait.c
    po/events.c
    po/guid.c
    po/poshtdwn.c
    po/povolume.c
    po/power.c
    ps/debug.c
    ps/job.c
    ps/kill.c
    ps/process.c
    ps/psmgr.c
    ps/psnotify.c
    ps/query.c
    ps/quota.c
    ps/security.c
    ps/state.c
    ps/thread.c
    ps/win32.c
    rtl/libsupp.c
    rtl/misc.c
    se/access.c
    se/acl.c
    se/audit.c
    se/lsa.c
    se/priv.c
    se/sd.c
    se/semgr.c
    se/sid.c
    se/token.c
    vf/driver.c
    wmi/wmi.c
    ntoskrnl.rc)

list(APPEND ASM_SOURCE ex/zw.S)

if(ARCH STREQUAL "i386")
    list(APPEND ASM_SOURCE
        ex/i386/fastinterlck_asm.S
        ex/i386/ioport.S
        ke/i386/ctxswitch.S
        ke/i386/trap.s
        ke/i386/usercall_asm.S
        rtl/i386/stack.S)
    list(APPEND SOURCE
        config/i386/cmhardwr.c
        ke/i386/abios.c
        ke/i386/cpu.c
        ke/i386/context.c
        ke/i386/exp.c
        ke/i386/irqobj.c
        ke/i386/kiinit.c
        ke/i386/ldt.c
        ke/i386/mtrr.c
        ke/i386/patpge.c
        ke/i386/thrdini.c
        ke/i386/traphdlr.c
        ke/i386/usercall.c
        ke/i386/v86vdm.c
        Mm_New/i386/MachineDependent.cpp
#        mm/i386/page.c
#        mm/ARM3/i386/init.c
        ps/i386/psctx.c
        ps/i386/psldt.c
        vdm/vdmmain.c
        vdm/vdmexec.c)
elseif(ARCH STREQUAL "amd64")
    list(APPEND ASM_SOURCE
        ke/amd64/boot.S
        ke/amd64/ctxswitch.S
        ke/amd64/trap.S)
    list(APPEND SOURCE
        config/i386/cmhardwr.c
        ke/amd64/context.c
        ke/amd64/cpu.c
        ke/amd64/except.c
        ke/amd64/interrupt.c
        ke/amd64/irql.c
        ke/amd64/kiinit.c
        ke/amd64/krnlinit.c
        ke/amd64/spinlock.c
        ke/amd64/stubs.c
        ke/amd64/thrdini.c
        Mm_New/amd64/MachineDependent.cpp
#        mm/amd64/init.c
#        mm/amd64/page.c
        ps/amd64/psctx.c)
elseif(ARCH STREQUAL "arm")
    list(APPEND ASM_SOURCE
        ke/arm/boot.s
        ke/arm/ctxswtch.s
        ke/arm/stubs_asm.s
        ke/arm/trap.s)
    list(APPEND SOURCE
        config/arm/cmhardwr.c
        ke/arm/cpu.c
        ke/arm/exp.c
        ke/arm/kiinit.c
        ke/arm/thrdini.c
        ke/arm/trapc.c
        ke/arm/usercall.c
        mm/arm/page.c
        mm/ARM3/arm/init.c
        ps/arm/psctx.c
        rtl/arm/rtlexcpt.c)
elseif(ARCH STREQUAL "powerpc")
    list(APPEND ASM_SOURCE
        ke/powerpc/main_asm.S
        ke/powerpc/ctxhelp.S)
    list(APPEND SOURCE
        config/powerpc/cmhardwr.c
        ke/powerpc/cpu.c
        ke/powerpc/exp.c
        ke/powerpc/kiinit.c
        ke/powerpc/ppc_irq.c
        ke/powerpc/stubs.c
        ke/powerpc/systimer.c
        ke/powerpc/thrdini.c
        ke/powerpc/ctxswitch.c
        mm/powerpc/pfault.c
        mm/powerpc/page.c)
endif()

if(NOT _WINKD_)
    if(ARCH STREQUAL "i386")
        list(APPEND SOURCE
            kd/i386/kdbg.c
            kd/i386/kdmemsup.c
            kd/wrappers/gdbstub.c)
        if(KDBG)
            list(APPEND ASM_SOURCE kdbg/i386/kdb_help.S)
            list(APPEND SOURCE kdbg/i386/i386-dis.c)
        endif()
    elseif(ARCH STREQUAL "amd64")
        list(APPEND SOURCE
            kd/amd64/kd.c
            kd/i386/kdbg.c  # Use the x86 file
            kd/amd64/kdmemsup.c)
        if(KDBG)
            list(APPEND ASM_SOURCE kdbg/amd64/kdb_help.S)
            list(APPEND SOURCE
                kdbg/amd64/i386-dis.c
                kdbg/amd64/kdb.c)
        endif()
    elseif(ARCH STREQUAL "arm")
        list(APPEND SOURCE kd/arm/kdbg.c)
    elseif(ARCH STREQUAL "powerpc")
        list(APPEND SOURCE kd/wrappers/gdbstub_powerpc.c)
    endif()

    if(KDBG)
        list(APPEND SOURCE
            kdbg/kdb.c
            kdbg/kdb_cli.c
            kdbg/kdb_expr.c
            kdbg/kdb_keyboard.c
            kdbg/kdb_serial.c
            kdbg/kdb_symbols.c)
    endif()

    list(APPEND SOURCE
        kd/wrappers/bochs.c
        kd/wrappers/kdbg.c
        kd/kdinit.c
        kd/kdio.c
        kd/kdmain.c)

else() # _WINKD_

    list(APPEND SOURCE
        kd64/kdapi.c
        kd64/kdbreak.c
        kd64/kddata.c
        kd64/kdinit.c
        kd64/kdlock.c
        kd64/kdprint.c
        kd64/kdtrap.c)

    if(ARCH STREQUAL "i386")
        list(APPEND SOURCE kd64/i386/kdx86.c)
    elseif(ARCH STREQUAL "amd64")
        list(APPEND SOURCE kd64/amd64/kdx64.c)
    elseif(ARCH STREQUAL "arm")
        list(APPEND SOURCE kd64/arm/kdarm.c)
    endif()

endif()

add_asm_files(ntoskrnl_asm ${ASM_SOURCE})

if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    # Clang optimises strcmp calls to memcmp.
    target_sources(libntoskrnl PRIVATE $<TARGET_OBJECTS:memcmp>)
endif()

list(APPEND PCH_SKIP_SOURCE
    guid.c)

add_executable(ntoskrnl
    ${ntoskrnl_asm}
    ${NTOSKRNL_SOURCE}
    ${PCH_SKIP_SOURCE}
    ntoskrnl.rc
    ${CMAKE_CURRENT_BINARY_DIR}/ntoskrnl.def)
set_module_type(ntoskrnl kernel)

source_group(TREE ${REACTOS_SOURCE_DIR}/ntoskrnl PREFIX "Source Files" FILES ${NTOSKRNL_SOURCE})

target_link_libraries(ntoskrnl cportlib csq ${PSEH_LIB} arbiter cmlib ntlsalib rtl ${ROSSYM_LIB} libcntpr wdmguid ioevent)

if(STACK_PROTECTOR)
    target_sources(ntoskrnl PRIVATE $<TARGET_OBJECTS:gcc_ssp_nt>)
endif()

if(NOT MSVC)
    target_link_libraries(ntoskrnl -lgcc)
endif()

add_importlibs(ntoskrnl hal kdcom bootvid)
add_pch(ntoskrnl ${REACTOS_SOURCE_DIR}/ntoskrnl/include/ntoskrnl.h "${PCH_SKIP_SOURCE}")
add_dependencies(ntoskrnl psdk asm)
add_cd_file(TARGET ntoskrnl DESTINATION reactos/system32 NO_CAB FOR all)

if(BUILD_MP)
    add_subdirectory(ntkrnlmp)
    endif()

    add_asm_files(ntkrnlmp_asm ${ASM_SOURCE})

    add_executable(ntkrnlmp
        ${ntkrnlmp_asm}
        ${SOURCE}
        ${CMAKE_CURRENT_BINARY_DIR}/ntkrnlmp.def)

    add_target_compile_definitions(ntkrnlmp CONFIG_SMP)

    if(ARCH STREQUAL "i386")
        set_entrypoint(ntkrnlmp KiSystemStartup 4)
    else()
        set_entrypoint(ntkrnlmp KiSystemStartup)
    endif()
    set_subsystem(ntkrnlmp native)

    if(MSVC)
        set_image_base(ntkrnlmp 0x00400000)
    else()
        set_image_base(ntkrnlmp 0x80800000)
    endif()

    # Linker bug
    if(NOT MSVC AND LTCG)
        add_target_link_flags(ntkrnlmp "-shared")
    endif()

    target_link_libraries(ntkrnlmp cportlib csq ${PSEH_LIB} cmlib rtl ${ROSSYM_LIB} libcntpr wdmguid ioevent)
    if(NOT MSVC)
        target_link_libraries(ntkrnlmp -lgcc)
    endif()
    add_importlibs(ntkrnlmp hal kdcom bootvid)
    add_dependencies(ntkrnlmp psdk bugcodes asm)
    add_cd_file(TARGET ntkrnlmp DESTINATION reactos/system32 NO_CAB FOR all)
endif()

add_asm_files(ntdllsys_asm ntdll.S)
add_library(ntdllsys ${ntdllsys_asm})
set_target_properties(ntdllsys PROPERTIES LINKER_LANGUAGE "C")
add_dependencies(ntdllsys asm)
