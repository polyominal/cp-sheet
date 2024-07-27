# CP Sheet

This repository hosts my competitive programming library,
largely tailored for use in ICPC-style contests.
The aspiration is to provide a set of generic, efficient, and concise
algorithm implementations ready for immediate deployment in competitions.

The KACTL build system
(<https://github.com/kth-competitive-programming/kactl>)
is adapted to generate our team's ICPC team reference document.

## Build and Test

We use Bazel as the build system.

Inside the developer container (<https://code.visualstudio.com/docs/devcontainers/containers>)
provided by this repository, you can build and run tests with

```sh
bazel test //...
```

Check out `src/` and its subdirectories for the library implementations.

In addition, run

```sh
oj-verify run
```

to run tests in `oj-test/`,
which are based on Libray Checker's
(<https://judge.yosupo.jp/>) test cases.

## KACTL Document Generation

Precondition: You have a *properly configured* (TODO: specify this) LaTeX environment,
which is not provided in our container for how space-hungry it is.

Navigate to `kactl/` and build with

```sh
make kactl
```

This produces `kactl.pdf` in `kactl/`.

## Note

Code in this library is designed to maximize
the convenience of usage in fast-paced competitions,
particularly in ICPC contests where you have to
manually type up everything within constrained time.

To this end, evil practices can be applied
to enhance competitive advantage. For example,

- Preferring `int` over `size_t` to avoid complications with unsigned types
- Using short identifiers (e.g., `cnt` instead of `counter`) to minimize code length

## License

Library code in this repository is CC0 licensed unless otherwise specified.
Though original, some implementations may have drawn inspiration from external sources,
which are hopefully acknowledged within the respective files to help trace things back.
