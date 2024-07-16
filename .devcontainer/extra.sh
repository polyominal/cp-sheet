#!/usr/bin/env bash

set -e

sudo apt-get update
sudo apt-get install -y cmake

pip install -i https://pypi.tuna.tsinghua.edu.cn/simple online-judge-tools online-judge-verify-helper

# Reference: https://www.kenmuse.com/blog/avoiding-dubious-ownership-in-dev-containers/
git config --global --add safe.directory $(pwd)