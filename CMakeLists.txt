cmake_minimum_required(VERSION 3.17)

project(ale)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(src)
add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)

    if(BUILD_TESTING)
        set(catch_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/extern/catch)
        include_directories(${catch_include_dir})
        include_directories(tests)
        add_subdirectory(tests)
    endif()
endif()
