# CP Sheet

This repository hosts my competitive programming library,
largely tailored for use in ICPC-style contests.
The aspiration is to provide a set of generic, efficient, and concise
algorithm implementations ready for immediate deployment in competitions.

The KACTL build system
(https://github.com/kth-competitive-programming/kactl)
is adapted to generate our team's ICPC team reference document.

## Design

Code in this library is designed to maximize
the convenience of usage in fast-paced competitions,
particularly in ICPC contests where you have to
manually type up everything within constrained time.

To this end, evil practices can be applied
to enhance competitive advantage. For example,

- Preferring `int` over `size_t` to avoid complications with unsigned types
- Using short identifiers (e.g., `cnt` instead of `counter`) to minimize code length

## Build and Test

Build with

```sh
cmake -B build/
cmake --build build/
```

Run unit tests in `src/test/` with

```sh
ctest --test-dir build/
```

## KACTL Document Generation

Navigate to `kactl/` and build with

```sh
make kactl
```

This produces `kactl.pdf` in `kactl/`.

## License

Library code in this repository is CC0 licensed unless otherwise specified.
Though original, some implementations may have drawn inspiration from external sources,
which are hopefully acknowledged within the respective files to help trace things back. 