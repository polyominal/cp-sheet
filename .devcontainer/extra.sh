#!/usr/bin/env bash

set -e

LOCAL_BIN="/usr/local/bin"

arch="$(uname -m)"
case "${arch}" in
x86_64) ARCHITECTURE=amd64 ;;
aarch64 | arm64 | armv8*) ARCHITECTURE=arm64 ;;
*)
    echo -e "Unsupported '$arch' architecture"
    exit 1
    ;;
esac

platf="$(uname -s)"
case "${platf}" in
Linux) PLATFORM=linux ;;
Darwin) PLATFORM=darwin ;;
*)
    echo -e "Unsupported '$platf' platform"
    exit 1
    ;;
esac

github_download() {
    repo=$1
    version=$2
    artifact=$3
    output=$4
    if [ "${version}" = "latest" ]; then
        URL="https://github.com/${repo}/releases/latest/download/${artifact}"
    else
        URL="https://github.com/${repo}/releases/download/${version}/${artifact}"
    fi
    curl -fSsL "${URL}" -o "${output}"
}

echo "Installing essential tools..."

sudo apt-get update

sudo apt-get install -y clangd cmake python3-pip
pip install online-judge-tools online-judge-verify-helper

echo "Configuring Git..."

# Reference: https://www.kenmuse.com/blog/avoiding-dubious-ownership-in-dev-containers/
git config --global --add safe.directory $(pwd)

echo "Setting up Bazel..."

github_download "bazelbuild/bazelisk" "${BAZELISK_VERSION}" "bazelisk-${PLATFORM}-${ARCHITECTURE}" "./bazelisk"
chmod +x "./bazelisk"
sudo mv ./bazelisk "${LOCAL_BIN}/bazelisk"
sudo ln -s "${LOCAL_BIN}/bazelisk" "${LOCAL_BIN}/bazel"

github_download "bazelbuild/buildtools" "${BUILDIFIER_VERSION}" "buildifier-${PLATFORM}-${ARCHITECTURE}" "./buildifier"
chmod +x "./buildifier"
sudo mv ./buildifier "${LOCAL_BIN}/buildifier"
