#!/usr/bin/env bash

set -e

sudo cp ./.devcontainer/sources.list /etc/apt/sources.list

sudo apt-get update

sudo apt-get install -y clangd cmake python3-pip

pip install -i https://pypi.tuna.tsinghua.edu.cn/simple online-judge-tools online-judge-verify-helper

# Reference: https://www.kenmuse.com/blog/avoiding-dubious-ownership-in-dev-containers/
git config --global --add safe.directory $(pwd)