#include "rcutils/logging_macros.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("RCUtils Logging Initialization", "[rcutils]") {
    REQUIRE(rcutils_logging_initialize() == RCUTILS_RET_OK);
    RCUTILS_LOG_INFO("RCUTILS logging initialized successfully.");
    REQUIRE(rcutils_logging_shutdown() == RCUTILS_RET_OK);
}