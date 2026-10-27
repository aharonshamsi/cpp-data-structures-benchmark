#pragma once

#include "data_structures/IDataStructure.hpp"

#include <cstddef>
#include <vector>

namespace dsbench {

// Unique-value collection backed by an unsorted std::vector<int>.
// Lookups use linear search. Removal swaps the found element with the last
// element and pops the back, so element order is not preserved.
class VectorDataStructure final : public IDataStructure {
public:
    bool insert(int value) override;
    bool remove(int value) override;
    [[nodiscard]] bool contains(int value) const override;
    [[nodiscard]] std::size_t size() const override;
    void clear() override;

private:
    std::vector<int> values_;
};

} // namespace dsbench
