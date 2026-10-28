#include "benchmark_core/BenchmarkConfig.hpp"

#include <stdexcept>
#include <string>

namespace dsbench {

void validate(const BenchmarkConfig& config)
{
    if (config.inputSize > maxInputSize) {
        throw std::invalid_argument(
            "BenchmarkConfig: inputSize " + std::to_string(config.inputSize) +
            " exceeds the maximum of " + std::to_string(maxInputSize));
    }
}

} // namespace dsbench
