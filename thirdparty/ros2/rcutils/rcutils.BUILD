load("@shunya//bazel_utils:template_expansion.bzl", "cc_library_from_template")

_GENERATE_LOGGING_MACROS_PY = "@shunya//thirdparty:logging_macros"

cc_library(
    name = "rcutils",
    srcs = glob([
        "src/*.c",
        "src/*.h",
        ],
        exclude = ["src/time_*.c"],
    ) +select({
        "@bazel_tools//src/conditions:windows": ["src/time_win32.c"],
        "//conditions:default": ["src/time_unix.c"],
    }),
    hdrs = glob(["include/**/*.h"]),
    strip_include_prefix = "include",
    local_defines = ['ROS_PACKAGE_NAME=\\\"rcutils\\\"', "_GNU_SOURCE"],
    deps = [
        ":rcutils_logging_macros",
    ],
    visibility = ["//visibility:public"],
)

py_library(
    name = "logging",
    srcs = [
        "rcutils/__init__.py",
        "rcutils/logging.py",
    ],
    imports = ["rcutils"],
    visibility = ["//visibility:public"],
)

py_binary(
    name = "build_logging_macros",
    srcs = [_GENERATE_LOGGING_MACROS_PY],
    deps = [
        ":logging",
    ],
)

cc_library_from_template(
    name = "rcutils_logging_macros",
    generator_script = ":build_logging_macros",
    template = "resource/logging_macros.h.em",
    package_name = "rcutils",
)