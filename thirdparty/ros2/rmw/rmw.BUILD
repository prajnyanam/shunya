cc_library(
    name = "rmw",
    srcs = glob(["src/**/*.c"]),
    hdrs = glob([
        "include/**/*.h",
        "include/**/*.hpp",
    ]),
    strip_include_prefix = "include",
    deps = ["@ros2_rcutils//:rcutils"],
    visibility = ["//visibility:public"],
)