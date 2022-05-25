set(CMAKE_CXX_STANDARD 20)

add_executable(runtimeTest runtime/main.cpp)
target_link_libraries(runtimeTest PRIVATE stellar-vm)
target_include_directories(runtimeTest PRIVATE ../source)