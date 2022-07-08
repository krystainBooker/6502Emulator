cmake_minimum_required(VERSION 3.0)
project("6502EmulatorTest")

# GTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Unit Tests
# Add test cpp file
add_executable( runUnitTests 6502Tests.cpp)
# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests ${GTEST_BOTH_LIBRARIES})
add_test( runUnitTests runUnitTests )