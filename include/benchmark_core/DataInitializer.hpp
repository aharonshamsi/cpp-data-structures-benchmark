#pragma once

#include "benchmark_core/BenchmarkConfig.hpp"
#include "data_structures/IDataStructure.hpp"

#include <vector>

namespace dsbench {

// Populates an existing IDataStructure according to a BenchmarkConfig.
// Works only through the IDataStructure interface and never creates the
// structure itself.
//
// Generation policy: the values are the integers 0 .. inputSize-1, in an
// order given by a Fisher-Yates shuffle driven by std::mt19937_64 seeded with
// config.seed. Uniqueness is by construction (a permutation), so no
// duplicates are possible and no retry loop is needed. The same
// (inputSize, seed) gives the same sequence, because mt19937_64 is fully
// specified by the standard and the bounded draw is implemented here rather
// than via std::uniform_int_distribution (whose output is implementation-
// defined). dataStructureType does not affect the values.
//
// Trade-offs: the keys are dense, so "missing" lookups are easy to construct
// (any value >= inputSize) but hash/tree behavior on dense keys may differ
// from sparse real-world keys. The shuffle needs O(inputSize) temporary
// memory, which is acceptable because initialization is outside timed code.
class DataInitializer {
public:
    // The values initialize() inserts, in insertion order.
    // Throws std::invalid_argument if the config fails validate().
    [[nodiscard]] static std::vector<int> generateValues(const BenchmarkConfig& config);

    // Inserts generateValues(config) into `dataStructure`.
    //
    // Policy: the structure must be empty. A non-empty structure is never
    // silently cleared; it is rejected so existing data is not lost.
    //
    // Throws std::invalid_argument if the config is invalid or
    // `dataStructure` is not empty (the structure is left untouched).
    // Throws std::logic_error if an insert is unexpectedly rejected; the
    // structure is cleared first so it is not left half-initialized.
    static void initialize(IDataStructure& dataStructure, const BenchmarkConfig& config);
};

} // namespace dsbench
