#pragma once

#include <cstddef>

namespace dsbench {

// Common runtime-polymorphic interface for a collection of unique int values.
//
// Every implementation must provide the same observable behavior:
//   - Values are unique. Inserting a value that is already present does not
//     modify the collection.
//   - Removing a value that is not present does not modify the collection.
//   - Element order is not part of the contract.
//
// Every call through this interface is a virtual call, so the interface is
// not free to use inside a tight, timed loop.
class IDataStructure {
public:
    virtual ~IDataStructure() = default;

    // Inserts `value` if it is not already present.
    // Returns true if the value was inserted, or false if it was already
    // present (the collection is unchanged).
    virtual bool insert(int value) = 0;

    // Removes `value` if it is present.
    // Returns true if an element was removed, or false if the value was not
    // present (the collection is unchanged).
    virtual bool remove(int value) = 0;

    // Returns true if `value` is present.
    [[nodiscard]] virtual bool contains(int value) const = 0;

    // Returns the number of stored values.
    [[nodiscard]] virtual std::size_t size() const = 0;

    // Removes all values. Postcondition: size() == 0.
    virtual void clear() = 0;

protected:
    // Copy and move are protected to prevent slicing through a base-class
    // reference, while still letting derived classes be copied and moved.
    IDataStructure() = default;
    IDataStructure(const IDataStructure&) = default;
    IDataStructure(IDataStructure&&) = default;
    IDataStructure& operator=(const IDataStructure&) = default;
    IDataStructure& operator=(IDataStructure&&) = default;
};

} // namespace dsbench
