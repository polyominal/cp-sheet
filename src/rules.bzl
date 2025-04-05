load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

def my_cc_test(name, srcs, deps = [], size = "small", **kwargs):
    cc_test(
        name = name,
        srcs = srcs,
        deps = deps + [
            "@googletest//:gtest",
            "@googletest//:gtest_main",
            "//contest:base",
            "//util:random",
        ],
        size = size,
        **kwargs
    )

def my_cc_library(name, hdrs, deps = [], **kwargs):
    cc_library(
        visibility = ["//visibility:public"],
        name = name,
        hdrs = hdrs,
        deps = deps + ["//contest:base"],
        **kwargs
    )

def my_cc_binary(name, srcs, deps = [], **kwargs):
    cc_binary(
        name = name,
        srcs = srcs,
        deps = deps + ["//contest:base"],
        **kwargs
    )
