#pragma once

#include "data_structures/IDataStructure.hpp"

#include <cstddef>
#include <map>

namespace dsbench {

// Unique-value collection backed by a std::map (a balanced binary search
// tree). The int is stored as the key. The mapped type is an empty
// placeholder because the collection only needs the key.
class MapDataStructure final : public IDataStructure {
public:
    bool insert(int value) override;
    bool remove(int value) override;
    [[nodiscard]] bool contains(int value) const override;
    [[nodiscard]] std::size_t size() const override;
    void clear() override;

private:
    struct Empty {};

    std::map<int, Empty> values_;
};

} // namespace dsbench
