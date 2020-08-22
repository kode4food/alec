cmake_minimum_required(VERSION 3.17)

add_subdirectory(gc)
add_subdirectory(runtime)

set(ale_source_files main.c)
add_executable(ale ${ale_source_files})
target_link_libraries(ale gc runtime)
