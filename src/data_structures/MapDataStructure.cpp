#include "data_structures/MapDataStructure.hpp"

namespace dsbench {

bool MapDataStructure::insert(int value)
{
    // try_emplace does nothing if the key exists; .second reports insertion.
    return values_.try_emplace(value).second;
}

bool MapDataStructure::remove(int value)
{
    return values_.erase(value) > 0;
}

bool MapDataStructure::contains(int value) const
{
    return values_.contains(value);
}

std::size_t MapDataStructure::size() const
{
    return values_.size();
}

void MapDataStructure::clear()
{
    values_.clear();
}

} // namespace dsbench
