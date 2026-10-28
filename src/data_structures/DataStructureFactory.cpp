#include "data_structures/DataStructureFactory.hpp"

#include "data_structures/ListDataStructure.hpp"
#include "data_structures/MapDataStructure.hpp"
#include "data_structures/UnorderedMapDataStructure.hpp"
#include "data_structures/VectorDataStructure.hpp"

#include <stdexcept>

namespace dsbench {

std::unique_ptr<IDataStructure> DataStructureFactory::create(DataStructureType type)
{
    // No `default:` label on purpose, so the compiler warns (-Wswitch) when a
    // new enumerator is added without a matching case.
    switch (type) {
    case DataStructureType::Vector:
        return std::make_unique<VectorDataStructure>();
    case DataStructureType::List:
        return std::make_unique<ListDataStructure>();
    case DataStructureType::Map:
        return std::make_unique<MapDataStructure>();
    case DataStructureType::UnorderedMap:
        return std::make_unique<UnorderedMapDataStructure>();
    }
    // Reached only for values outside the enumerators (e.g. a bad static_cast).
    throw std::invalid_argument("DataStructureFactory::create: unsupported DataStructureType");
}

} // namespace dsbench
