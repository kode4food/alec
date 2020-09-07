set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(content "#define CATCH_CONFIG_MAIN" "#include \"catch.hpp\"")
file(GLOB_RECURSE children ../src ../src/*)
foreach(child ${children})
    if(child MATCHES "__tests__/[a-zA-Z]+.hpp$")
        get_filename_component(path "${child}" ABSOLUTE)
        list(APPEND content "#include \"${path}\"")
    endif()
endforeach()

string(REPLACE ";" "\n" content "${content}")
file(WRITE main_gen.cpp "${content}\n")

set(test_src main_gen.cpp)
add_executable(ale_tests ${test_src})
target_link_libraries(ale_tests gc runtime)
add_test(All_Ale_Tests ale_tests)
