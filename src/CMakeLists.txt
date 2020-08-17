cmake_minimum_required(VERSION 3.17)
project(ale_bin)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(gc)
add_subdirectory(runtime)

set(ale_source_files main.c)
add_executable(ale ${ale_source_files})
target_link_libraries(ale gc runtime)
