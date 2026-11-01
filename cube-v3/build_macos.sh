#!/bin/zsh
# Build cube-v3 with qmake, bundle Qt into the app, and copy it to the Desktop.
# Usage: ./build_macos.sh   (Qt path can be overridden with QT_DIR)
set -e

QT_DIR="${QT_DIR:-$HOME/Qt/6.10.2/macos}"
SRC_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="${TMPDIR:-/tmp}/cube-v3-build"

rm -rf "$BUILD_DIR" && mkdir -p "$BUILD_DIR" && cd "$BUILD_DIR"
"$QT_DIR/bin/qmake" "$SRC_DIR/cube.pro" CONFIG+=release
make -j"$(sysctl -n hw.ncpu)"

"$QT_DIR/bin/macdeployqt" cube-v3.app
codesign --force --deep -s - cube-v3.app   # re-sign after bundling (required on Apple Silicon)

rm -rf "$HOME/Desktop/cube-v3.app"
cp -R cube-v3.app "$HOME/Desktop/"
echo "Done: $HOME/Desktop/cube-v3.app"
