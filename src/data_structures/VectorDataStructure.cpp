#include "data_structures/VectorDataStructure.hpp"

#include <algorithm>

namespace dsbench {

bool VectorDataStructure::insert(int value)
{
    if (contains(value)) {
        return false;
    }
    values_.push_back(value);
    return true;
}

bool VectorDataStructure::remove(int value)
{
    const auto it = std::find(values_.begin(), values_.end(), value);
    if (it == values_.end()) {
        return false;
    }
    // Swap-and-pop: O(1) after the search, instead of shifting every later
    // element. Order is not part of the contract, so this is allowed.
    *it = values_.back();
    values_.pop_back();
    return true;
}

bool VectorDataStructure::contains(int value) const
{
    return std::find(values_.begin(), values_.end(), value) != values_.end();
}

std::size_t VectorDataStructure::size() const
{
    return values_.size();
}

void VectorDataStructure::clear()
{
    values_.clear();
}

} // namespace dsbench
