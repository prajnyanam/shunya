def cc_binary_with_headers(name, srcs, hdrs, includes=[]):
    native.cc_binary(
        name = name,
        srcs = srcs + hdrs,  # Add header files to the srcs attribute
        includes = includes,  # Pass the include directories to Bazel
    )
