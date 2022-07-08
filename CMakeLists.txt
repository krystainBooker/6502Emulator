cmake_minimum_required (VERSION 3.8)

project (6502Emulator)
set(CMAKE_CXX_STANDARD 14)

set(PROJECT_SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Include sub-projects.
include_directories(6502EmulatorLib)
add_subdirectory(6502EmulatorLib)

target_link_libraries(${PROJECT_NAME} 6502EmulatorLib)

add_subdirectory(6502EmulatorTests)