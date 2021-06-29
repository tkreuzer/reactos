
if (MSVC)
    # Disable warning C4146: unary minus operator applied to unsigned type, result still unsigned
    # Disable warning C4090: 'function': different 'const' qualifiers
    add_compile_options(/wd4146 /wd4090)
endif()


add_subdirectory(d3d8thk)
#add_subdirectory(bdaplgin) #disabled in trunk
#add_subdirectory(d3d8) #disabled in trunk, see wine subfolder
#add_subdirectory(d3d9) #disabled in trunk, see wine subfolder
#add_subdirectory(ddraw) #disabled in trunk, see wine subfolder
#add_subdirectory(dsound_new) #disabled in trunk
#add_subdirectory(ksproxy) Not needed at the moment
add_subdirectory(ksuser)
#add_subdirectory(msdvbnp) #disabled in trunk
#add_subdirectory(msvidctl) #disabled in trunk
add_subdirectory(wine)
