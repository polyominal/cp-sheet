load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

def my_cc_test(name, srcs, deps = [], **kwargs):
    cc_test(
        name = name,
        srcs = srcs,
        copts = ["-Isrc"],
        deps = deps + [
            "@googletest//:gtest",
            "@googletest//:gtest_main",
            "//src/contest:base",
            "//src/util:random",
        ],
        **kwargs
    )

def my_cc_library(name, hdrs, deps = [], **kwargs):
    cc_library(
        visibility = ["//visibility:public"],
        name = name,
        hdrs = hdrs,
        copts = ["-Isrc"],
        deps = deps + ["//src/contest:base"],
        **kwargs
    )
