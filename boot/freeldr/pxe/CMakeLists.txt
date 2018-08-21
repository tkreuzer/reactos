
if (MSVC)

    add_custom_command(
        OUTPUT chain.obj
        COMMAND ${CMAKE_C_COMPILER} /nologo ${_no_std_includes_flag} /I${REACTOS_SOURCE_DIR}/boot/freeldr /D_USE_ML /EP /c chain.c
        DEPENDS chain.c)

#    add_custom_command(
#        OUTPUT ${_binary_file}
#        COMMAND native-obj2bin ${_object_file} ${_binary_file} ${_base_address}
#        DEPENDS ${_object_file} native-obj2bin)

else()

#OBJCOPY  = objcopy
#com32  := $(topdir)/com32
#RELOCS := $(com32)/tools/relocs
#COM32LD	   = $(com32)/lib/com32.ld

#C_LIBS	   = $(com32)/libutil/libutil_com.a $(GPLLIB) \
#	     $(com32)/lib/libcom32.a $(LIBGCC)

#.PRECIOUS: %.elf
#%.elf: %.o $(LIBS) $(C_LIBS) $(COM32LD)
#	$(LD) $(LDFLAGS) -o $@ $(filter-out $(COM32LD),$^)

#%.c32: %.elf
#	$(OBJCOPY) -O binary $< $@
#	$(RELOCS) $< >> $@ || ( rm -f $@ ; false )



    set(GCCOPT 
        -std=gnu99
        -m32
        -fno-stack-protector
        -fwrapv
        -freg-struct-return
        -mregparm=3 -DREGPARM=3 -march=i386 -Os
        #-fPIE #-fPIC
        -fno-exceptions
        -fno-asynchronous-unwind-tables
        -fno-strict-aliasing
        -falign-functions=0 #-malign-functions=0
        -falign-jumps=0 #-malign-jumps=0
        -falign-labels=0 #-malign-labels=0
        -falign-loops=0 #-malign-loops=0
        -mpreferred-stack-boundary=2
        #-incoming-stack-boundary=2
        )

    add_custom_command(
        OUTPUT chain.o
        COMMAND ${CMAKE_C_COMPILER} -W -Wall -Wstrict-prototypes ${GCCOPT} -o chain.o -I${CMAKE_CURRENT_SOURCE_DIR}/include -c ${CMAKE_CURRENT_SOURCE_DIR}/chain.c
        DEPENDS chain.c)

    add_custom_command(
        OUTPUT chain.c32
#        COMMAND native-obj2bin chain.o chain.c32 0x10000
        COMMAND objcopy -O binary chain.o chain.c32
        DEPENDS chain.o native-obj2bin)

        set_source_files_properties(chain.o chain.c32 PROPERTIES GENERATED TRUE)
 
        add_custom_target(chain_c32 ALL DEPENDS chain.c32)

endif()
