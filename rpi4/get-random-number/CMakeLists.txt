cmake_minimum_required(VERSION 3.12)
# Set up project.
project(client
        VERSION 1.0
        DESCRIPTION "An example how to get a random number on RPI4.")

# Initialize CMake library for KasperskyOS SDK.
include (platform)
initialize_platform (FORCE_STATIC)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory (rn)
add_subdirectory (einit)
