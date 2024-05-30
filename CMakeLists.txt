cmake_minimum_required(VERSION 3.27)
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
target_compile_options(cp-sheet INTERFACE
  -O2 -Wall -Wextra -pedantic -Wshadow -Wformat=2
  -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2
  -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-unused-result
  -Wno-sign-conversion
  -g -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
  -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all
  -fstack-protector -D_FORTIFY_SOURCE=2)
target_link_options(cp-sheet INTERFACE -O2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector)

# Switch for generating code coverage measures
# option(COVERAGE "Enable coverage reporting" OFF)
# set(COVERAGE_FLAGS "--coverage")
# if(COVERAGE)
#     message(STATUS "Enabled coverage reporting")
# endif()

# Unit tests
file(GLOB TEST_SRC_FILES "src/test/*.test.cpp")
add_executable(tests "${TEST_SRC_FILES}")
target_link_libraries(tests PUBLIC cp-sheet)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE src)
# if(COVERAGE)
#     target_compile_options(tests PRIVATE ${COVERAGE_FLAGS})
#     target_link_options(tests PRIVATE ${COVERAGE_FLAGS})
# endif()

# Compilation check
file(GLOB TEST_COMPILES_SRC_FILES "src/test-compiles.cpp")
add_executable(test_compiles ${TEST_COMPILES_SRC_FILES})
target_link_libraries(test_compiles PUBLIC cp-sheet)
target_include_directories(test_compiles PRIVATE src)
# if(COVERAGE)
#     target_compile_options(test_compiles PRIVATE ${COVERAGE_FLAGS})
#     target_link_options(test_compiles PRIVATE ${COVERAGE_FLAGS})
# endif()

# Testing with Catch2
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)
