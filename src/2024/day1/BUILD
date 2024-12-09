cc_binary(
    name = "day1",
    data = [
        ":input",
    ],
    copts = [
        "-std=c++17",
    ],
    srcs = [
        "day1.cpp",
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
