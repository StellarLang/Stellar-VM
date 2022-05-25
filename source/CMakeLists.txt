set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENABLE_DEBUG_MACRO")

find_library(STELLAR_COMMON_LIB stellar-common)
add_library(stellar-vm SHARED runtime.cpp)
target_link_libraries(stellar-vm ${STELLAR_COMMON_LIB})
set_target_properties(stellar-vm PROPERTIES PUBLIC_HEADER "runtime.hpp")
install(
        TARGETS stellar-vm
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include/stellar
)