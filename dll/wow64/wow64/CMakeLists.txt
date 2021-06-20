
# Preprocess the header file
preprocess_file(${CMAKE_CURRENT_SOURCE_DIR}/ntfunctions.h ${CMAKE_CURRENT_BINARY_DIR}/ntfunctions_pp.h -I${REACTOS_SOURCE_DIR}/sdk/include/ndk)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/wow64stubs.cpp
    COMMAND native-genwow64 ${CMAKE_CURRENT_BINARY_DIR}/ntfunctions_pp.h wow64stubs.cpp
    DEPENDS native-genwow64 ${CMAKE_CURRENT_BINARY_DIR}/ntfunctions_pp.h)

add_library(wow64stubs ${CMAKE_CURRENT_BINARY_DIR}/wow64stubs.cpp)
