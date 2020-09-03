set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(module)

set(test_src main.cpp)
add_executable(ale_tests ${test_src})
target_link_libraries(ale_tests gc runtime)
add_test(All_Ale_Tests ale_tests)
