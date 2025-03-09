workspace(name = "shunya")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# rules_cuda
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
http_archive(
    name = "rules_cuda",
    sha256 = "2f8c8c8c85f727bec4423efecec12d3b751cb0a98bda99f0f9d351608a23b858",
    strip_prefix = "rules_cuda-v0.2.1",
    urls = ["https://github.com/bazel-contrib/rules_cuda/releases/download/v0.2.1/rules_cuda-v0.2.1.tar.gz"],
)

load("@rules_cuda//cuda:repositories.bzl", "register_detected_cuda_toolchains", "rules_cuda_dependencies")
rules_cuda_dependencies()
register_detected_cuda_toolchains()

http_archive(
    name = "catch2",
    urls = ["https://github.com/catchorg/Catch2/archive/refs/tags/v3.6.0.zip"], 
    strip_prefix = "Catch2-3.6.0",  
)


git_repository(
    name = "ros2_rcutils",
    build_file = "//thirdparty:ros2/rcutils/rcutils.BUILD",
    commit = "2d9d74e72ecd1eea240412be3dacd413dcb5f680",
    remote = "https://github.com/ros2/rcutils.git",
)

git_repository(
    name = "ros2_rcpputils",
    build_file = "//thirdparty:ros2/rcpputils/rcpputils.BUILD",
    commit = "f8e638eb72bfbacea18ca1cf67c4f7d48561d9b2",
    remote = "https://github.com/ros2/rcpputils.git",
)

git_repository(
    name = "ros2_rmw",
    build_file = "//thirdparty:ros2/rmw/rmw.BUILD",
    commit = "2a4ee718d0da004d5629f50afd2896fbd1f4aedd",
    remote = "https://github.com/ros2/rmw.git",
)

git_repository(
    name = "ros2_rcl_logging",
    build_file = "//thirdparty:ros2/rcl_logging/rcl_logging.BUILD",
    commit = "1b7a4e34884005f28eeb04065b5d94565c67b11d",
    remote = "https://github.com/ros2/rcl_logging.git",
)
