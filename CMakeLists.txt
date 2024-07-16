cmake_minimum_required(VERSION 3.21)
project(cp-sheet)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

# Catch2 stuff
Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.6.0
)
FetchContent_MakeAvailable(Catch2)

# Library
file(GLOB_RECURSE SRC_FILES "src/*.hpp")
add_library(cp-sheet INTERFACE)
target_include_directories(cp-sheet INTERFACE src)
target_compile_options(
  cp-sheet INTERFACE
  -O2 -Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion -Werror
)

# Cache tests
file(GLOB TEST_SRC_FILES "src/ctest/*.ctest.cpp")
add_executable(tests "${TEST_SRC_FILES}")
target_link_libraries(tests PUBLIC cp-sheet)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE src)

# Compilation check
file(GLOB TEST_COMPILES_SRC_FILES "src/test-compiles.cpp")
add_executable(test_compiles ${TEST_COMPILES_SRC_FILES})
target_link_libraries(test_compiles PUBLIC cp-sheet)
target_include_directories(test_compiles PRIVATE src)

# Reference: https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)
