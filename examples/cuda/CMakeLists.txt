find_package(CUDA REQUIRED)

add_executable(cuda_simple_example
    simple_example.cc
    simple_example.cu
)
add_clang_format(cuda_simple_example)

target_include_directories(cuda_simple_example PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}        # for simple_example.h
    ${CUDA_INCLUDE_DIRS}               # for cuda_runtime.h
)