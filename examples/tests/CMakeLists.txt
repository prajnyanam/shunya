find_package(Catch2 3 REQUIRED)

add_executable(tests_simple_test simple_test.cc)
add_clang_format(tests_simple_test)

target_link_libraries(tests_simple_test PRIVATE Catch2::Catch2WithMain)