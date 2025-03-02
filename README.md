# CP Sheet

This repository hosts my competitive programming library,
largely tailored for use in ICPC-style contests.
The aspiration is to provide a set of generic, efficient, and concise
algorithm implementations ready for immediate deployment in competitions.

The KACTL build system
(<https://github.com/kth-competitive-programming/kactl>)
is adapted to generate our team's ICPC team reference document.

It is recommended to use the provided Docker container
(<https://code.visualstudio.com/docs/devcontainers/containers>)
for development.

## Build and Test

We use Bazel as the build system. Build and run tests with

```sh
bazel test //...
```

In addition, run

```sh
oj-verify run
```

to run tests in `oj-test/`,
which are based on Libray Checker's
(<https://judge.yosupo.jp/>) test cases.

## License

Library code in this repository is CC0 licensed unless otherwise specified.
Though original, some implementations may have drawn inspiration from external sources,
which are hopefully acknowledged within the respective files to help trace things back.
