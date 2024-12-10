cc_binary(
    name = "day3",
    data = [
        ":input",
    ],
    copts = [
        "-std=c++17",
    ],
    srcs = [
        "day3.cpp",
    ],
    deps = [
        "//common/logging",
        "//common/string",
    ],
)

filegroup(
    name = "input",
    srcs = [
        "input.txt",
    ],
)
