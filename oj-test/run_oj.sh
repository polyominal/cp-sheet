#!/usr/bin/env bash

# Copied: https://github.com/yosupo06/yosupo-library/blob/5b768522ff3a8587ebe40b7bba5258f5ec18ad92/test/run_oj.sh

expected_dir="$(cd "$(dirname "$0")/.." && pwd)"
if [ "$(pwd)" != "$expected_dir" ]; then
  echo "Error: Please run the script from ${expected_dir}."
  exit 1
fi

set -e

competitive-verifier oj-resolve \
    --no-bundle \
    --config .verify-helper/config.toml \
    --include $1 > verify_files.json

competitive-verifier verify --verify-json verify_files.json

rm verify_files.json