find_package(Catch2 3 REQUIRED)

add_executable(tests_simple_test simple_test.cc)

target_link_libraries(tests_simple_test PRIVATE Catch2::Catch2WithMain)