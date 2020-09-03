set(runtime_src runtime.c runtime.h)
add_library(runtime ${runtime_src})
target_link_libraries(runtime gc)
