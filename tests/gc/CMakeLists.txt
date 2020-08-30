set(tests_gc_source_files main.cpp gc.hpp log.hpp)
add_executable(tests_gc ${tests_gc_source_files})
target_link_libraries(tests_gc gc runtime)
add_test(garbage_collector tests_gc)
