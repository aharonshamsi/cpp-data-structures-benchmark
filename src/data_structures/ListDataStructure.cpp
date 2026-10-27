#include "data_structures/ListDataStructure.hpp"

#include <algorithm>

namespace dsbench {

bool ListDataStructure::insert(int value)
{
    if (contains(value)) {
        return false;
    }
    values_.push_back(value);
    return true;
}

bool ListDataStructure::remove(int value)
{
    // find + erase stops at the first match. std::list::remove(value) would
    // always scan the whole list, because it removes every equal element.
    const auto it = std::find(values_.begin(), values_.end(), value);
    if (it == values_.end()) {
        return false;
    }
    values_.erase(it);
    return true;
}

bool ListDataStructure::contains(int value) const
{
    return std::find(values_.begin(), values_.end(), value) != values_.end();
}

std::size_t ListDataStructure::size() const
{
    return values_.size();
}

void ListDataStructure::clear()
{
    values_.clear();
}

} // namespace dsbench
