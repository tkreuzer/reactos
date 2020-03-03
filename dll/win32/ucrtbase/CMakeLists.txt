
spec2def(ucrtbase.dll ucrtbase.spec)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/ucrtbase_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/ucrtbase.def)

add_library(ucrtbase MODULE ${SOURCE} ucrtbase.rc)
set_module_type(ucrtbase win32dll ENTRYPOINT DllMain 12)
target_link_libraries(ucrtbase crt wine ${PSEH_LIB})
add_importlibs(ucrtbase kernel32 ntdll)
#add_cd_file(TARGET ucrtbase DESTINATION reactos/system32 FOR all)
