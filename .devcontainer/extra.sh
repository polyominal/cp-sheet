#!/usr/bin/env bash

set -e

sudo apt-get update
sudo apt-get install -y cmake clangd

# Reference: https://www.kenmuse.com/blog/avoiding-dubious-ownership-in-dev-containers/
git config --global --add safe.directory $(pwd)