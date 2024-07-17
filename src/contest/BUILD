load("//:rules.bzl", "my_cc_library")

cc_library(
    name = "base",
    hdrs = ["base.hpp"],
    copts = [
        "-O2",
        "-std=c++20",
        "-Wall",
        "-Wextra",
        "-Wshadow",
        "-Wconversion",
        "-Wno-sign-conversion",
        "-Werror",
    ],
    visibility = ["//visibility:public"],
)
