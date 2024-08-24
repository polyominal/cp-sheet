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

pip install online-judge-tools online-judge-verify-helper

echo "Configuring Git..."

# Reference: https://www.kenmuse.com/blog/avoiding-dubious-ownership-in-dev-containers/
git config --global --add safe.directory $(pwd)

echo "Setting up Bazel..."

bazel_url() {
    # Example: https://github.com/bazelbuild/bazel/releases/download/7.2.1/bazel-7.2.1-linux-x86_64
    ARCH_NAME=${ARCHITECTURE}
    if [ "${ARCHITECTURE}" = "amd64" ]; then
        ARCH_NAME="x86_64"
    fi
    echo "https://github.com/bazelbuild/bazel/releases/download/${BAZEL_VERSION}/bazel-${BAZEL_VERSION}-${PLATFORM}-${ARCH_NAME}"
}

buildifier_url() {
    # Example: https://github.com/bazelbuild/buildtools/releases/download/7.1.2/buildifier-7.1.2-linux-amd64
    echo "https://github.com/bazelbuild/buildtools/releases/download/${BUILDIFIER_VERSION}/buildifier-${PLATFORM}-${ARCHITECTURE}"
}

curl -fSsL "$(bazel_url)" -o "./bazel"
chmod +x "./bazel"
sudo mv ./bazel "${LOCAL_BIN}/bazel"

curl -fSsL "$(buildifier_url)" -o "./buildifier"
chmod +x "./buildifier"
sudo mv ./buildifier "${LOCAL_BIN}/buildifier"

echo "Setting up TexLive..."

sudo apt-get update
sudo apt-get install -y texlive-latex-base texlive-latex-recommended texlive-latex-extra