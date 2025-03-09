cc_library(
    name = "rcl_logging_interface",
    srcs = glob(["src/**/*.c"]),
    hdrs = glob(["include/**/*.h"]),
    strip_include_prefix = "include",
    deps = [
        "@ros2_rcutils//:rcutils"
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "rcl_logging_spdlog",
    srcs = glob(["src/*.cpp"]),
    implementation_deps = [
        "@spdlog",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":rcl_logging_interface",
        "@ros2_rcpputils//:rcpputils",
        "@ros2_rcutils//:rcutils",
    ],
)