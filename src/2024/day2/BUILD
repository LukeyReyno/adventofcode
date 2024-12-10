cc_binary(
    name = "day2",
    data = [
        ":input",
    ],
    copts = [
        "-std=c++17",
    ],
    srcs = [
        "day2.cpp",
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
