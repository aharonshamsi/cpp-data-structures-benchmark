# Data Structures Performance Benchmark

A C++20 project that measures how standard library containers perform under
different workloads and input sizes. It compares measured execution time with
theoretical Big-O complexity and explains the differences.

> **Status: early development.** The data structure layer is implemented.
> The benchmark harness, workloads, result export, analysis scripts, and unit
> tests have not been built yet. This repository does not contain any
> benchmark results yet.

## Table of Contents

- [Motivation](#motivation)
- [Containers Under Test](#containers-under-test)
- [Architecture](#architecture)
  - [Class Hierarchy](#class-hierarchy)
  - [The `IDataStructure` Contract](#the-idatastructure-contract)
  - [Implementations](#implementations)
  - [Design Notes](#design-notes)
- [Prerequisites](#prerequisites)
- [Building](#building)
- [Project Structure](#project-structure)
- [Roadmap](#roadmap)
- [Methodology Principles](#methodology-principles)

## Motivation

Two operations with the same asymptotic complexity can take very different
amounts of time on real hardware. Memory layout, cache locality, pointer
indirection, allocation overhead, and hashing behavior all affect the result.
This project investigates those effects with reproducible measurements rather
than assumptions.

## Containers Under Test

| Container            | Underlying structure          | Memory layout      |
| -------------------- | ----------------------------- | ------------------ |
| `std::vector`        | Dynamic array                 | Contiguous         |
| `std::list`          | Doubly linked list            | Node-based         |
| `std::map`           | Balanced binary search tree   | Node-based         |
| `std::unordered_map` | Hash table with buckets       | Node-based buckets |

## Architecture

### Class Hierarchy

All containers sit behind one abstract interface. A benchmark can then run
the same workload against each container. All types live in the `dsbench`
namespace.

```text
                         dsbench::IDataStructure
                          (abstract interface)
                                   │
       ┌───────────────────┬───────┴───────────┬─────────────────────────────┐
       │                   │                   │                             │
VectorDataStructure  ListDataStructure  MapDataStructure  UnorderedMapDataStructure
 std::vector<int>     std::list<int>   std::map<int,Empty> std::unordered_map<int,Empty>
```

Each concrete class is marked `final`.

### The `IDataStructure` Contract

`IDataStructure` models a **collection of unique `int` values**:

| Member                                 | Behavior                                                                  |
| -------------------------------------- | ------------------------------------------------------------------------- |
| `bool insert(int value)`               | Inserts `value` if it is absent. Returns `false` if it was already there. |
| `bool remove(int value)`               | Removes `value` if it is present. Returns `false` if it was absent.       |
| `bool contains(int value) const`       | Returns whether `value` is present. `[[nodiscard]]`.                      |
| `std::size_t size() const`             | Returns the number of stored values. `[[nodiscard]]`.                     |
| `void clear()`                         | Removes all values. Postcondition: `size() == 0`.                         |

Element order is **not** part of the contract. Implementations may reorder
elements when that makes an operation cheaper.

### Implementations

| Class                       | Backing container               | `insert`                         | `remove`                          | `contains`        |
| --------------------------- | ------------------------------- | -------------------------------- | --------------------------------- | ----------------- |
| `VectorDataStructure`       | `std::vector<int>` (unsorted)   | Linear search, then `push_back`  | Linear search, then swap-and-pop  | Linear search     |
| `ListDataStructure`         | `std::list<int>`                | Linear search, then `push_back`  | Linear search, then `erase`       | Linear search     |
| `MapDataStructure`          | `std::map<int, Empty>`          | `try_emplace`                    | `erase(key)`                      | `map::contains`   |
| `UnorderedMapDataStructure` | `std::unordered_map<int, Empty>`| `try_emplace`                    | `erase(key)`                      | `unordered_map::contains` |

The theoretical complexities follow from these choices: linear for
`vector`/`list`, logarithmic for `map`, and average-case constant for
`unordered_map`. These are expectations to test, not measured results.

### Design Notes

- **Runtime polymorphism has a cost.** Every call through `IDataStructure` is
  a virtual call. The interface is meant to keep workloads uniform. It is not
  free inside a tight timed loop, and the benchmark harness must account for
  this when it is designed.
- **Slicing protection.** `IDataStructure`'s copy and move operations are
  `protected`. This prevents slicing through a base reference while still
  allowing derived classes to be copied and moved.
- **Swap-and-pop removal in `VectorDataStructure`.** The element is
  overwritten with the last element, and then the last element is popped.
  After the search, removal is O(1) instead of shifting every later element.
  The contract does not promise order, so this is allowed.
- **`find` + `erase` in `ListDataStructure`.** `std::list::remove(value)`
  always scans the whole list because it removes every matching element. The
  values are unique, so stopping at the first match is correct and cheaper.
- **Empty mapped type for the maps.** `std::map` and `std::unordered_map`
  store the `int` as the key with an empty placeholder value. This keeps the
  comparison focused on the tree and hash-table structures.

## Prerequisites

- A C++20-capable compiler (Apple Clang 15+, Clang 16+, or GCC 11+)
- CMake 3.25 or newer

The primary development environment is Apple Clang on an Intel-based macOS
machine.

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

Use the `release` preset (or `-DCMAKE_BUILD_TYPE=Release`) for optimized
builds. Any performance measurement must use an optimized build. All build
output goes to `build/`, which is excluded from version control.

### Build Targets

| Target            | Type           | Description                                                     |
| ----------------- | -------------- | --------------------------------------------------------------- |
| `data_structures` | Static library | The `IDataStructure` hierarchy. Compiled with `-Wall -Wextra -Wpedantic`. |

Unit tests are enabled by the `PROJECT_BUILD_TESTS` option (default `ON`).
`tests/CMakeLists.txt` does not define any tests yet, so `ctest` currently
reports no tests. `src/main.cpp` is a placeholder and is not yet part of any
build target.

## Project Structure

```text
.
├── include/
│   └── data_structures/
│       ├── IDataStructure.hpp             Abstract interface (unique-int collection contract)
│       ├── VectorDataStructure.hpp        std::vector-backed implementation
│       ├── ListDataStructure.hpp          std::list-backed implementation
│       ├── MapDataStructure.hpp           std::map-backed implementation
│       └── UnorderedMapDataStructure.hpp  std::unordered_map-backed implementation
├── src/
│   ├── data_structures/
│   │   ├── VectorDataStructure.cpp
│   │   ├── ListDataStructure.cpp
│   │   ├── MapDataStructure.cpp
│   │   └── UnorderedMapDataStructure.cpp
│   └── main.cpp                           Placeholder entry point (not yet built)
├── tests/
│   └── CMakeLists.txt                     Unit test registration (no tests yet)
├── scripts/                               Analysis and visualization scripts (planned)
├── results/                               Recorded benchmark output kept under version control
├── docs/                                  Design and methodology documentation
├── .vscode/                               Shared VS Code settings and recommended extensions
├── CMakeLists.txt                         Top-level build configuration
├── CMakePresets.json                      Debug/release configure, build, and test presets
├── CLAUDE.md                              Project goals and contributor guidance
└── README.md
```

`build/` is generated locally and is not tracked.

## Roadmap

- [x] Project skeleton, CMake configuration, and presets
- [x] `IDataStructure` interface and four container implementations
- [ ] Unit tests for the `IDataStructure` contract
- [ ] Workload definitions and input-size selection
- [ ] Benchmark harness and measurement methodology
- [ ] CSV export of results
- [ ] Python/Matplotlib analysis and visualization
- [ ] Documented results and interpretation

Planned workloads include sequential iteration, searches for present and
missing values, insertion, and removal. Possible extensions include reserved
vs. non-reserved capacity, rehashing, and sequential vs. randomized access
patterns. These are not final.

## Methodology Principles

The benchmark harness will follow these principles once it is built:

- Use identical workloads across all containers.
- Separate setup cost from the measured operation.
- Repeat measurements and report robust statistics such as the median.
- Time with `std::chrono::steady_clock`.
- Prevent the compiler from removing the measured work.
- Record the compiler, flags, OS, and hardware with every result set.
- Keep raw measurements separate from interpretation.

All reported results will come from real executions on documented hardware.
