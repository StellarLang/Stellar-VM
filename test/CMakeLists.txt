set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENABLE_DEBUG_MACRO")

add_executable(runtimeTest runtime/main.cpp)
target_link_libraries(runtimeTest PRIVATE stellar-vm)
target_include_directories(runtimeTest PRIVATE ../source)