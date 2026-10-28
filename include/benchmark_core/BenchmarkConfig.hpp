#pragma once

#include "benchmark_core/BenchmarkDefaults.hpp"
#include "data_structures/DataStructureType.hpp"

#include <cstddef>
#include <cstdint>
#include <limits>

namespace dsbench {

// Plain configuration data for preparing a benchmark input.
// It creates and initializes nothing; see DataStructureFactory and
// DataInitializer. Later phases can add fields (workload, repetitions, ...).
struct BenchmarkConfig {
    // Placeholder default so a default-constructed config is never
    // uninitialized; callers are expected to choose a type explicitly.
    DataStructureType dataStructureType = DataStructureType::Vector;

    // Number of unique values to store.
    std::size_t inputSize = defaults::inputSize;

    // Seed for the deterministic input generator (see DataInitializer).
    std::uint64_t seed = defaults::seed;
};

// Largest supported inputSize. Values are ints in [0, inputSize), so the
// largest value, inputSize - 1, must fit in an int.
inline constexpr std::size_t maxInputSize =
    static_cast<std::size_t>(std::numeric_limits<int>::max());

// Throws std::invalid_argument if `config` is not usable
// (currently: inputSize > maxInputSize).
void validate(const BenchmarkConfig& config);

} // namespace dsbench
