
add_definitions(
    -D_SHDOCVW_)

add_library(shdocvw_test MODULE
    CExplorerBand.cpp
    objects.cpp
)
target_link_libraries(shdocvw_test atl_classes)
add_dependencies(shdocvw_test psdk)

set_module_type(shdocvw_test win32dll UNICODE)
target_link_libraries(shdocvw_test uuid)
add_delay_importlibs(shdocvw_test shell32 user32 gdi32 ole32 oleaut32 ieframe)
add_importlibs(shdocvw_test advapi32 msvcrt comctl32 kernel32 ntdll)
add_dependencies(shdocvw_test stdole2)
