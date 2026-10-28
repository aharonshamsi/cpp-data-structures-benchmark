#include "benchmark_core/DataInitializer.hpp"

#include <cstdint>
#include <numeric>
#include <random>
#include <stdexcept>
#include <utility>

namespace dsbench {

namespace {

// Uniform value in [0, bound), bound > 0, by rejection sampling so there is
// no modulo bias. mt19937_64 yields uniformly distributed 64-bit values.
std::uint64_t boundedRandom(std::mt19937_64& rng, std::uint64_t bound)
{
    // Reject the first (2^64 mod bound) values so the rest split evenly.
    const std::uint64_t threshold = (0 - bound) % bound;
    std::uint64_t r = rng();
    while (r < threshold) {
        r = rng();
    }
    return r % bound;
}

} // namespace

std::vector<int> DataInitializer::generateValues(const BenchmarkConfig& config)
{
    validate(config);

    std::vector<int> values(config.inputSize);
    std::iota(values.begin(), values.end(), 0);

    std::mt19937_64 rng(config.seed);
    for (std::size_t i = values.size(); i > 1; --i) {
        const auto j = static_cast<std::size_t>(boundedRandom(rng, i));
        std::swap(values[i - 1], values[j]);
    }
    return values;
}

void DataInitializer::initialize(IDataStructure& dataStructure, const BenchmarkConfig& config)
{
    if (dataStructure.size() != 0) {
        throw std::invalid_argument(
            "DataInitializer::initialize: the data structure must be empty");
    }

    for (const int value : generateValues(config)) {
        if (!dataStructure.insert(value)) {
            dataStructure.clear();
            throw std::logic_error(
                "DataInitializer::initialize: insert unexpectedly rejected a generated value");
        }
    }
}

} // namespace dsbench
