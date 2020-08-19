cmake_minimum_required(VERSION 3.17)
project(ale)
include_directories(src)
add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    # Prepare "Catch" library for test executables
    set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/catch)
    include_directories(${CATCH_INCLUDE_DIR})
    add_subdirectory(src/gc/__tests__)
endif()
