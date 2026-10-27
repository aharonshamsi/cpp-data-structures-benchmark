#pragma once

#include "data_structures/IDataStructure.hpp"

#include <cstddef>
#include <list>

namespace dsbench {

// Unique-value collection backed by a doubly linked std::list<int>.
// Lookups use linear search. New values are appended at the back.
class ListDataStructure final : public IDataStructure {
public:
    bool insert(int value) override;
    bool remove(int value) override;
    [[nodiscard]] bool contains(int value) const override;
    [[nodiscard]] std::size_t size() const override;
    void clear() override;

private:
    std::list<int> values_;
};

} // namespace dsbench
