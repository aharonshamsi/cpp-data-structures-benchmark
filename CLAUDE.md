# C++ Data Structures Performance Benchmark

## 1. Project Overview

**C++ Data Structures Performance Benchmark** is a C++20 benchmarking and performance analysis project designed to investigate how different data structures behave under various workloads and input sizes.

The project aims to go beyond theoretical Big-O complexity by measuring actual execution times, analyzing memory-related behavior, visualizing results, and explaining the underlying reasons for performance differences.

The primary goal is to build a technically rigorous, reproducible, and well-documented project that demonstrates practical C++ programming skills, algorithmic understanding, performance analysis, and systems-level thinking.

The project is intended to serve as a professional portfolio project for junior C++ software engineering, systems programming, and performance-oriented development roles.

## 2. Core Objectives

The project should help answer questions such as:

- How do different data structures perform under different workloads?
- Why can two operations with the same asymptotic complexity have significantly different execution times?
- How do memory layout, cache locality, pointer indirection, and memory allocation affect performance?
- How do input size, access patterns, and data distribution influence execution time?
- How do theoretical complexity and real-world measurements compare?
- How can benchmark results be measured, analyzed, and presented reliably?

The project should produce real experimental evidence rather than relying on assumptions or fabricated benchmark results.

## 3. Data Structures Under Investigation

The initial scope includes the following C++ Standard Library containers:

- `std::vector`
- `std::list`
- `std::map`
- `std::unordered_map`

The project should investigate their internal characteristics and performance implications.

Topics of interest include:

- Contiguous versus node-based memory layouts.
- Random access versus sequential traversal.
- Cache locality and cache misses.
- Memory allocation overhead and per-element metadata.
- Tree-based search and balancing.
- Hash functions, collisions, bucket distribution, load factor, and rehashing.
- Capacity management and reallocation in `std::vector`.
- Iterator behavior and the costs of insertion and deletion.
- Average-case, worst-case, and amortized time complexity.

Implementation-specific claims should be verified against the relevant C++ standard library implementation whenever necessary.

## 4. Benchmark Workloads

The initial workload candidates include:

- Sequential iteration over all elements.
- Searching for existing elements.
- Searching for missing elements.
- Inserting elements.
- Removing elements.
- Measuring the effects of input size and access patterns.

Potential extensions include:

- Comparing reserved and non-reserved container capacity.
- Investigating reallocation and rehashing.
- Comparing sequential and randomized access patterns.
- Exploring memory consumption and allocation behavior.
- Investigating cache-related performance effects.
- Exploring parallel workloads if they become relevant to the project.

The exact workloads, input sizes, and experimental methodology have not yet been finalized. They should be designed deliberately before implementation.

## 5. Performance Analysis

The project should distinguish between theoretical complexity and measured performance.

Relevant metrics may include:

- Execution time.
- Throughput, where meaningful.
- Latency, where the benchmark methodology supports it.
- Memory consumption, using a clearly documented measurement method.
- Performance scaling as input size increases.
- Variability across repeated runs.

Results should be interpreted in the context of the hardware, operating system, compiler, optimization settings, and experimental conditions.

A measured performance difference does not, by itself, prove its underlying cause. Explanations involving cache behavior, branch prediction, allocation overhead, or other hardware effects should be supported by appropriate reasoning and, where possible, additional profiling evidence.

## 6. Measurement Methodology

Benchmark reliability is a core project requirement.

The implementation and documentation should address:

- Consistent and comparable workloads across containers.
- Separation of setup costs from the operation being measured when appropriate.
- Repeated measurements and suitable summary statistics, such as the median.
- Use of an appropriate timing mechanism, such as `std::chrono::steady_clock`.
- Prevention of unwanted compiler optimizations that could eliminate benchmarked work.
- Appropriate compiler optimization settings.
- Recording relevant environment information.
- Clear separation between measurement results and their interpretation.

The benchmark must not present theoretical expectations as measured results.

All reported measurements must originate from actual executions, and the methodology should make it possible to reproduce the experiments.

## 7. Results and Visualization

The intended workflow is to collect benchmark results and export them in a structured format, initially considering CSV.

A Python analysis and visualization script, potentially using Matplotlib, should consume the exported data and generate graphs.

Potential visualizations include:

- Execution time versus input size.
- Side-by-side comparisons of containers for the same workload.
- Performance scaling across different input sizes.
- Memory consumption comparisons, if reliable measurements are available.
- Variability across repeated measurements.

Charts must be generated from actual benchmark output. Their labels, units, legends, and experimental conditions should be explicit.

The purpose of visualization is not merely to display which container is faster, but to help explain when and why performance differences occur.

## 8. Technology and Development Environment

The initial technology direction is:

- **Language:** C++20.
- **Build system:** CMake.
- **Compiler:** Apple Clang on macOS.
- **Development environment:** Visual Studio Code.
- **Version control:** Git.
- **Analysis and visualization:** Python and Matplotlib, subject to final confirmation.
- **Data exchange:** CSV or another appropriate structured format.

The current development machine is an Intel-based MacBook running macOS.

The project may later be tested on Linux to investigate cross-platform behavior. Such comparisons should account for differences in hardware, compiler versions, standard library implementations, and execution environments.

The current repository is an initial project skeleton. The final architecture, interfaces, directory responsibilities, benchmarking framework, and implementation details have not yet been decided.

## 9. Operating System and Hardware Considerations

The project should recognize that measured performance is influenced by more than the data structure itself.

Relevant factors include:

- CPU architecture and microarchitecture.
- Cache hierarchy and cache-line behavior.
- Memory hierarchy and memory latency.
- Compiler optimizations and generated machine code.
- Operating system scheduling and background activity.
- Virtual memory and page behavior.
- Memory allocator behavior.
- Thermal and power-related constraints.

These factors should be introduced progressively according to their relevance to the experiments.

Advanced profiling tools and operating-system-specific measurements are possible future extensions, not mandatory initial requirements.

## 10. Engineering Principles

The project should follow professional software engineering practices:

- Use modern, idiomatic C++20.
- Keep the code modular, readable, and maintainable.
- Separate benchmark execution, result collection, and analysis where appropriate.
- Use clear naming and well-defined responsibilities.
- Handle invalid inputs and measurement failures appropriately.
- Provide a reproducible build and execution workflow.
- Add automated tests where they provide meaningful value.
- Document important design decisions and experimental assumptions.
- Avoid unnecessary dependencies and premature complexity.

The project should prioritize correctness, measurement quality, and explainability over the number of features.

## 11. Current Project Status

The project is in its initial setup and research stage.

The repository skeleton and basic CMake configuration are being established. The project has not yet finalized its architecture, workload definitions, benchmark interfaces, or measurement methodology.

The next step is to develop a sound conceptual understanding of the data structures, memory hierarchy, CPU behavior, and benchmarking principles before making the major design decisions.

Implementation should follow a clearly defined design rather than determining the architecture through ad hoc coding.

## 12. Instructions for Claude Code

Act as a senior C++ engineer and performance-oriented software design mentor.

When working on this project:

1. Read this document and inspect the relevant repository files before making assumptions about the existing implementation.
2. Distinguish between established project decisions, proposed ideas, and unresolved questions.
3. Do not prematurely implement features or make architectural decisions that have not been discussed.
4. When design decisions are needed, explain the available options, trade-offs, performance implications, and recommended approach before implementation.
5. Prefer technically accurate, maintainable, and appropriately simple solutions over unnecessary abstraction.
6. Do not invent benchmark results, profiling evidence, existing files, or successful test executions.
7. When executing commands or changing files, report what was actually changed and which validations were actually performed.
8. Preserve the existing project structure unless a change is justified and agreed upon.
9. Do not stage, commit, or push Git changes unless explicitly instructed.
10. Keep the implementation aligned with the project's primary purpose: understanding and demonstrating real-world C++ data structure performance.

The user wants to understand the engineering reasoning behind the project, not merely receive generated code. Explanations should be technically rigorous, practical, and suitable for preparing for junior C++ and systems programming interviews.

## 13. Long-Term Vision

The intended outcome is a polished, reproducible C++ performance benchmarking project that combines:

- Solid C++ implementation.
- A sound experimental methodology.
- Real measurements and meaningful comparisons.
- Clear data visualization.
- Technical explanations of observed behavior.
- Professional documentation and a reproducible workflow.

The project should demonstrate the ability to connect algorithms and data structures with the behavior of modern hardware and software systems.

Future extensions should be selected according to their educational and engineering value, not added merely to increase the project's size.
