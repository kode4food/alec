set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(project ${PROJECT_SOURCE_DIR})
set(project_src ${project}/src)
set(project_extern ${project}/extern)

set(catch_include_dir ${project_extern}/catch)
include_directories(${catch_include_dir})

set(content "#define CATCH_CONFIG_MAIN" "#include \"catch.hpp\"")
file(GLOB_RECURSE children ${project_src} ${project_src}/*)
foreach(child ${children})
    if(child MATCHES "__tests__/[a-zA-Z]+.hpp$")
        get_filename_component(path "${child}" ABSOLUTE)
        list(APPEND content "#include \"${path}\"")
    endif()
endforeach()

string(REPLACE ";" "\n" content "${content}")

set(test_src ${CMAKE_CURRENT_BINARY_DIR}/main_gen.cpp)
file(GENERATE OUTPUT ${test_src} CONTENT "${content}\n")
add_executable(ale_tests ${test_src})
target_link_libraries(ale_tests gc runtime)
add_test(All_Ale_Tests ale_tests)
