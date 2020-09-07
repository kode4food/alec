set(runtime_src runtime.c runtime.h)
add_library(runtime ${runtime_src})
target_link_libraries(runtime gc)

if(BUILD_TESTING)
    add_subdirectory(__tests__)
endif()
