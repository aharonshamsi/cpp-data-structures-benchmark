# Project Name

> This project is under initial setup.

## Prerequisites

- A C++20-capable compiler (Apple Clang 15+, Clang 16+, or GCC 11+)
- CMake 3.25 or newer

## Building

Using CMake presets:

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

Or manually:

```sh
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build/debug
ctest --test-dir build/debug
```

Use the `release` preset (or `-DCMAKE_BUILD_TYPE=Release`) for optimized builds.
All build output is written to `build/`, which is excluded from version control.

## Directory Structure

```text
.
├── include/          Public headers
├── src/              C++ source files
├── tests/            Unit tests
├── scripts/          Supporting scripts
├── results/          Generated output intended to be kept
├── docs/             Documentation
├── build/            Build artifacts (generated, not tracked)
├── .vscode/          Shared VS Code workspace settings
├── CMakeLists.txt    Top-level build configuration
└── CMakePresets.json Configure/build/test presets
```
