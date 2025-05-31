#include <catch2/catch_test_macros.hpp>

TEST_CASE("Framework integration test", "[integration]") {
  REQUIRE(1 + 1 == 2);
  REQUIRE(std::string("Hello") + " World" == "Hello World");
}