cmake_minimum_required (VERSION 3.8)

project(6502EmulatorTests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB PROJECT_SOURCES *.cpp)

# adding the target
add_executable(6502EmulatorTestsRun ${PROJECT_SOURCES})

target_link_libraries(6502EmulatorTestsRun 6502EmulatorLib)
target_link_libraries(6502EmulatorTestsRun gtest gtest_main)