
message(WARNING "CMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG}")

# Fix up some flags from default CMake setup
foreach(type DEBUG RELWITHDEBINFO RELEASE MINSIZEREL)
    # Remove /INCREMENTAL linker flag
    string(REPLACE "/INCREMENTAL:YES" "" CMAKE_EXE_LINKER_FLAGS_${type} ${CMAKE_EXE_LINKER_FLAGS_${type}})
    string(REPLACE "/INCREMENTAL" "" CMAKE_EXE_LINKER_FLAGS_${type} ${CMAKE_EXE_LINKER_FLAGS_${type}})
    string(REPLACE "/INCREMENTAL:YES" "" CMAKE_SHARED_LINKER_FLAGS_${type} ${CMAKE_SHARED_LINKER_FLAGS_${type}})
    string(REPLACE "/INCREMENTAL" "" CMAKE_SHARED_LINKER_FLAGS_${type} ${CMAKE_SHARED_LINKER_FLAGS_${type}})

    # Remove /Zi
    string(REPLACE "/Zi" "" CMAKE_C_FLAGS_${type} ${CMAKE_C_FLAGS_${type}})
    string(REPLACE "/Zi" "" CMAKE_CXX_FLAGS_${type} ${CMAKE_CXX_FLAGS_${type}})

    # Remove /RTC1
    string(REPLACE "/RTC1" "" CMAKE_C_FLAGS_${type} ${CMAKE_C_FLAGS_${type}})
    string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_${type} ${CMAKE_CXX_FLAGS_${type}})
endforeach()

message(WARNING "CMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG}")

#set(CMAKE_C_LINK_EXECUTABLE
#    "${_CMAKE_VS_LINK_EXE}<CMAKE_LINKER> ${CMAKE_CL_NOLOGO} <OBJECTS> ${CMAKE_START_TEMP_FILE} /out:<TARGET> /pdb:<TARGET_PDB> /version:<TARGET_VERSION_MAJOR>.<TARGET_VERSION_MINOR>${_PLATFORM_LINK_FLAGS} <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES>${CMAKE_END_TEMP_FILE}")
#set(CMAKE_CXX_LINK_EXECUTABLE
#    "${_CMAKE_VS_LINK_EXE}<CMAKE_LINKER> ${CMAKE_CL_NOLOGO} <OBJECTS> ${CMAKE_START_TEMP_FILE} /out:<TARGET> /pdb:<TARGET_PDB> /version:<TARGET_VERSION_MAJOR>.<TARGET_VERSION_MINOR>${_PLATFORM_LINK_FLAGS} <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES>${CMAKE_END_TEMP_FILE}")

#message(WARNING "CMAKE_C_LINK_EXECUTABLE = ${CMAKE_C_LINK_EXECUTABLE}")

function(add_host_tool _tool)
    add_executable(${_tool} ${ARGN})
    if(NEW_STYLE_BUILD)
        set_target_properties(${_tool} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TOOLS_FOLDER})
    endif()
endfunction()

#add_executable(pefixup pefixup.c)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_compile_flags_language("/EHsc" "CXX")
endif()

add_host_tool(bin2c bin2c.c)
add_host_tool(gendib gendib/gendib.c)
add_host_tool(geninc geninc/geninc.c)
add_host_tool(mkshelllink mkshelllink/mkshelllink.c)
add_host_tool(obj2bin obj2bin/obj2bin.c)
add_host_tool(spec2def spec2def/spec2def.c)

add_host_tool(utf16le utf16le/utf16le.cpp)

add_subdirectory(cabman)
add_subdirectory(hhpcomp)
add_subdirectory(hpp)
add_subdirectory(isohybrid)
add_subdirectory(kbdtool)
add_subdirectory(mkhive)
add_subdirectory(mkisofs)
add_subdirectory(unicode)
add_subdirectory(widl)
add_subdirectory(wpp)
add_subdirectory(xml2sdb)

if(NOT MSVC)
    add_subdirectory(log2lines)
    add_subdirectory(rsym)
endif()

add_subdirectory(fatten)
