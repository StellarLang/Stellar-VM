set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENABLE_DEBUG_MACRO")

find_library(STELLAR_COMMON_LIB stellar-common)
add_library(stellar-vm runtime.cpp runtime.hpp debug.hpp)
target_link_libraries(stellar-vm ${STELLAR_COMMON_LIB})