cmake_minimum_required(VERSION 3.25)

project(ProjectName
    VERSION 0.1.0
    LANGUAGES CXX
)

# ---------------------------------------------------------------------------
# Language standard
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Emit compile_commands.json for editor tooling (IntelliSense / clangd).
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------------------
# Guard against in-source builds
# ---------------------------------------------------------------------------
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR
        "In-source builds are not allowed. "
        "Use a separate build directory, e.g.: cmake -S . -B build")
endif()

# ---------------------------------------------------------------------------
# Default build type for single-config generators
# ---------------------------------------------------------------------------
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# ---------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------
option(PROJECT_BUILD_TESTS "Build unit tests" ON)

# ---------------------------------------------------------------------------
# Targets
# ---------------------------------------------------------------------------
add_library(data_structures STATIC
    src/data_structures/VectorDataStructure.cpp
    src/data_structures/ListDataStructure.cpp
    src/data_structures/MapDataStructure.cpp
    src/data_structures/UnorderedMapDataStructure.cpp
)
target_include_directories(data_structures PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(data_structures PRIVATE -Wall -Wextra -Wpedantic)

if(PROJECT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
