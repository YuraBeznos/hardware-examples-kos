cmake_minimum_required(VERSION 3.2)

set (CMAKE_CXX_STANDARD 17)

# Set up project.
project(nmea
        VERSION 1.0
        DESCRIPTION "A library for NMEA 0183 messages.")

# Add source files.
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Create library.
add_library(nmea STATIC ${sources})

# Set include directories for internal/external use.
target_include_directories(nmea PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
