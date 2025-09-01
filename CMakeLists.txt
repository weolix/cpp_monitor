cmake_minimum_required(VERSION 3.10)
project(cpp_monitor)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_subdirectory(Crow)

add_executable(cpp_monitor main.cpp)
target_link_libraries(cpp_monitor pthread crow)