load("@rules_cc//cc:defs.bzl", "cc_test")
load("@rules_cc//cc:defs.bzl", "cc_library")

def my_cc_test(name, srcs, deps=[], **kwargs):
    cc_test(
        name = name,
        srcs = srcs,
        copts = ["-O2", "-std=c++20", "-Wall", "-Wextra", "-Wshadow", "-Wconversion", "-Wno-sign-conversion", "-Werror", "-Isrc"],
        deps = deps + [
            "@googletest//:gtest",
            "@googletest//:gtest_main",
            "//src/contest:base",
            "//src/util:random"
        ],
        **kwargs,
    )

def my_cc_library(name, hdrs, deps=[], **kwargs):
    cc_library(
        visibility = ["//visibility:public"],
        name = name,
        hdrs = hdrs,
        copts = ["-O2", "-std=c++20", "-Wall", "-Wextra", "-Wshadow", "-Wconversion", "-Wno-sign-conversion", "-Werror", "-Isrc"],
        deps = deps + ["//src/contest:base"],
        **kwargs,
    )