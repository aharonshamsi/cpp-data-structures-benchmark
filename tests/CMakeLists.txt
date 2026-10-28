# Unit test targets will be defined here.
# Register each test executable with add_test() so it runs under CTest.

add_executable(setup_tests setup_tests.cpp)
target_link_libraries(setup_tests PRIVATE benchmark_core)
target_compile_options(setup_tests PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME setup_tests COMMAND setup_tests)
