#pragma once

#include "data_structures/IDataStructure.hpp"

#include <cstddef>
#include <unordered_map>

namespace dsbench {

// Unique-value collection backed by a std::unordered_map (a hash table).
// The int is stored as the key. The mapped type is an empty placeholder
// because the collection only needs the key.
class UnorderedMapDataStructure final : public IDataStructure {
public:
    bool insert(int value) override;
    bool remove(int value) override;
    [[nodiscard]] bool contains(int value) const override;
    [[nodiscard]] std::size_t size() const override;
    void clear() override;

private:
    struct Empty {};

    std::unordered_map<int, Empty> values_;
};

} // namespace dsbench
