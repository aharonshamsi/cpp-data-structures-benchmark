#pragma once

#include "data_structures/DataStructureType.hpp"
#include "data_structures/IDataStructure.hpp"

#include <memory>

namespace dsbench {

// Single place that maps a DataStructureType to its concrete class.
// Only constructs an empty structure; populating it is DataInitializer's job.
class DataStructureFactory {
public:
    // Returns a new, empty structure of the requested type.
    // Throws std::invalid_argument if `type` is not a valid enumerator.
    [[nodiscard]] static std::unique_ptr<IDataStructure> create(DataStructureType type);
};

} // namespace dsbench
