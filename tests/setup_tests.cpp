// Correctness tests for DataStructureFactory, BenchmarkConfig and
// DataInitializer. Dependency-free: each check records a failure and the
// process exits non-zero if any check failed.

#include "benchmark_core/BenchmarkConfig.hpp"
#include "benchmark_core/DataInitializer.hpp"
#include "data_structures/DataStructureFactory.hpp"
#include "data_structures/ListDataStructure.hpp"
#include "data_structures/MapDataStructure.hpp"
#include "data_structures/UnorderedMapDataStructure.hpp"
#include "data_structures/VectorDataStructure.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace dsbench;

namespace {

int failures = 0;

#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            ++failures;                                                          \
            std::cerr << __FILE__ << ':' << __LINE__ << ": CHECK failed: " #cond \
                      << '\n';                                                   \
        }                                                                        \
    } while (false)

#define CHECK_THROWS_AS(expr, ExceptionType)                                     \
    do {                                                                         \
        bool caught_ = false;                                                    \
        try {                                                                    \
            (void)(expr);                                                        \
        } catch (const ExceptionType&) {                                         \
            caught_ = true;                                                      \
        } catch (...) {                                                          \
        }                                                                        \
        CHECK(caught_);                                                          \
    } while (false)

constexpr std::array<DataStructureType, 4> allTypes = {
    DataStructureType::Vector,
    DataStructureType::List,
    DataStructureType::Map,
    DataStructureType::UnorderedMap,
};

BenchmarkConfig makeConfig(DataStructureType type, std::size_t size, std::uint64_t seed = 7)
{
    BenchmarkConfig config;
    config.dataStructureType = type;
    config.inputSize = size;
    config.seed = seed;
    return config;
}

void testFactoryCreatesCorrectConcreteType()
{
    const auto vector = DataStructureFactory::create(DataStructureType::Vector);
    const auto list = DataStructureFactory::create(DataStructureType::List);
    const auto map = DataStructureFactory::create(DataStructureType::Map);
    const auto unorderedMap = DataStructureFactory::create(DataStructureType::UnorderedMap);

    CHECK(dynamic_cast<VectorDataStructure*>(vector.get()) != nullptr);
    CHECK(dynamic_cast<ListDataStructure*>(list.get()) != nullptr);
    CHECK(dynamic_cast<MapDataStructure*>(map.get()) != nullptr);
    CHECK(dynamic_cast<UnorderedMapDataStructure*>(unorderedMap.get()) != nullptr);
}

void testFactoryRejectsInvalidEnumValue()
{
    CHECK_THROWS_AS(DataStructureFactory::create(static_cast<DataStructureType>(999)),
                    std::invalid_argument);
}

// Also covers requirement 8: existing insert/remove/contains/size/clear
// behavior, exercised through the factory-created interface.
void testStructureUsableThroughInterface()
{
    for (const auto type : allTypes) {
        const std::unique_ptr<IDataStructure> ds = DataStructureFactory::create(type);
        CHECK(ds != nullptr);
        CHECK(ds->size() == 0);

        CHECK(ds->insert(5));
        CHECK(!ds->insert(5)); // duplicate rejected
        CHECK(ds->size() == 1);
        CHECK(ds->contains(5));
        CHECK(!ds->contains(6));

        CHECK(!ds->remove(6)); // missing value: no change
        CHECK(ds->size() == 1);
        CHECK(ds->remove(5));
        CHECK(!ds->contains(5));
        CHECK(ds->size() == 0);

        ds->insert(1);
        ds->insert(2);
        ds->clear();
        CHECK(ds->size() == 0);
        CHECK(!ds->contains(1));
    }
}

void testInitializerPopulatesUniqueValues()
{
    constexpr std::size_t n = 500;
    for (const auto type : allTypes) {
        const auto config = makeConfig(type, n);
        const auto ds = DataStructureFactory::create(type);
        DataInitializer::initialize(*ds, config);

        CHECK(ds->size() == n);
        // The generated values are exactly 0..n-1; all must be present.
        bool allPresent = true;
        for (std::size_t v = 0; v < n; ++v) {
            allPresent = allPresent && ds->contains(static_cast<int>(v));
        }
        CHECK(allPresent);
        CHECK(!ds->contains(static_cast<int>(n)));
        CHECK(!ds->contains(-1));
    }
}

void testGeneratedValuesAreUnique()
{
    auto values = DataInitializer::generateValues(makeConfig(DataStructureType::Vector, 2000));
    CHECK(values.size() == 2000);
    std::sort(values.begin(), values.end());
    CHECK(std::adjacent_find(values.begin(), values.end()) == values.end());
}

void testZeroSizedInput()
{
    for (const auto type : allTypes) {
        const auto ds = DataStructureFactory::create(type);
        DataInitializer::initialize(*ds, makeConfig(type, 0));
        CHECK(ds->size() == 0);
    }
    CHECK(DataInitializer::generateValues(makeConfig(DataStructureType::Vector, 0)).empty());
}

void testDeterminism()
{
    const auto a = DataInitializer::generateValues(makeConfig(DataStructureType::Vector, 300, 123));
    const auto b = DataInitializer::generateValues(makeConfig(DataStructureType::Vector, 300, 123));
    const auto otherSeed =
        DataInitializer::generateValues(makeConfig(DataStructureType::Vector, 300, 124));
    const auto otherType =
        DataInitializer::generateValues(makeConfig(DataStructureType::Map, 300, 123));

    CHECK(a == b);
    CHECK(a != otherSeed); // a different seed gives a different order
    CHECK(a == otherType); // the container type does not affect the values
}

void testInvalidConfig()
{
    BenchmarkConfig tooLarge = makeConfig(DataStructureType::Vector, maxInputSize + 1);
    CHECK_THROWS_AS(validate(tooLarge), std::invalid_argument);
    CHECK_THROWS_AS(DataInitializer::generateValues(tooLarge), std::invalid_argument);

    const auto ds = DataStructureFactory::create(DataStructureType::Vector);
    CHECK_THROWS_AS(DataInitializer::initialize(*ds, tooLarge), std::invalid_argument);
    CHECK(ds->size() == 0);
}

void testNonEmptyStructureIsRejectedUntouched()
{
    for (const auto type : allTypes) {
        const auto ds = DataStructureFactory::create(type);
        ds->insert(-42);

        CHECK_THROWS_AS(DataInitializer::initialize(*ds, makeConfig(type, 10)),
                        std::invalid_argument);
        CHECK(ds->size() == 1); // existing data was not discarded
        CHECK(ds->contains(-42));
    }
}

// A structure that reports empty but rejects every insert, to exercise the
// "unexpected insert failure" path.
class RejectingStructure final : public IDataStructure {
public:
    bool insert(int) override { return false; }
    bool remove(int) override { return false; }
    [[nodiscard]] bool contains(int) const override { return false; }
    [[nodiscard]] std::size_t size() const override { return 0; }
    void clear() override { clearCalled = true; }

    bool clearCalled = false;
};

void testUnexpectedInsertFailureIsReported()
{
    RejectingStructure ds;
    CHECK_THROWS_AS(DataInitializer::initialize(ds, makeConfig(DataStructureType::Vector, 5)),
                    std::logic_error);
    CHECK(ds.clearCalled);
}

} // namespace

int main()
{
    testFactoryCreatesCorrectConcreteType();
    testFactoryRejectsInvalidEnumValue();
    testStructureUsableThroughInterface();
    testInitializerPopulatesUniqueValues();
    testGeneratedValuesAreUnique();
    testZeroSizedInput();
    testDeterminism();
    testInvalidConfig();
    testNonEmptyStructureIsRejectedUntouched();
    testUnexpectedInsertFailureIsReported();

    if (failures != 0) {
        std::cerr << failures << " check(s) failed\n";
        return 1;
    }
    std::cout << "All checks passed\n";
    return 0;
}
