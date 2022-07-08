cmake_minimum_required (VERSION 3.8)

project(6502EmulatorLib)

file(GLOB HEADER_FILES *.h)
file(GLOB PROJECT_SOURCES *.cpp)

add_library (${PROJECT_NAME} STATIC  ${PROJECT_SOURCES} ${PROJECT_HEADERS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()
