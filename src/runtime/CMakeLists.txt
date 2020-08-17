cmake_minimum_required(VERSION 3.17)
set(runtime_source_files runtime.c runtime.h)
add_library(runtime ${runtime_source_files})
target_link_libraries(runtime gc)
