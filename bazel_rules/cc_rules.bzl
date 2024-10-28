# def cc_binary_with_headers(name, srcs, hdrs, includes=[]):
#     native.cc_binary(
#         name = name,
#         srcs = srcs + hdrs,  # Add header files to the srcs attribute
#         includes = includes,  # Pass the include directories to Bazel
#     )

def cc_binary_with_headers(name, srcs, hdrs, includes=[]):
    # Create the binary target
    native.cc_binary(
        name = name,
        srcs = srcs + hdrs,  # Add header files to the srcs attribute
        includes = includes,  # Pass the include directories to Bazel
    )

    # Create a linting target using genrule
    native.genrule(
        name = "{}_lint".format(name),  # Use format method for string formatting
        srcs = srcs + hdrs,  # Lint both source and header files
        outs = ["{}_clang_tidy.out".format(name)],  # Specify the output file for clang-tidy results
        cmd = "clang-tidy $(SRCS) -- -std=c++17 > $@ 2>&1",  # Run clang-tidy and capture output
    )

