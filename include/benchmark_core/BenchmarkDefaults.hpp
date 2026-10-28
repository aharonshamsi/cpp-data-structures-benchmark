#pragma once

#include <cstddef>
#include <cstdint>

namespace dsbench::defaults {

// Defaults for BenchmarkConfig fields. Sized for local development and
// correctness checks, not for long benchmark runs. Callers may override any
// of them by setting the corresponding BenchmarkConfig field.

inline constexpr std::size_t inputSize = 1'000;

// Fixed so that runs are reproducible unless a caller picks another seed.
inline constexpr std::uint64_t seed = 42;

} // namespace dsbench::defaults
