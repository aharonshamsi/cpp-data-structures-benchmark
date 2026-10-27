#include "data_structures/UnorderedMapDataStructure.hpp"

namespace dsbench {

bool UnorderedMapDataStructure::insert(int value)
{
    // try_emplace does nothing if the key exists; .second reports insertion.
    return values_.try_emplace(value).second;
}

bool UnorderedMapDataStructure::remove(int value)
{
    return values_.erase(value) > 0;
}

bool UnorderedMapDataStructure::contains(int value) const
{
    return values_.contains(value);
}

std::size_t UnorderedMapDataStructure::size() const
{
    return values_.size();
}

void UnorderedMapDataStructure::clear()
{
    values_.clear();
}

} // namespace dsbench
