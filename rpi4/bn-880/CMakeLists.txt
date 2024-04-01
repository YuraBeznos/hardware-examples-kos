cmake_minimum_required(VERSION 3.12)
# Set up project.
project(bn-880
        VERSION 1.0
        DESCRIPTION "An example to get and parse NMEA 0183 messages via UART on RPI4.")

# Initialize CMake library for KasperskyOS SDK.
include (platform)
initialize_platform (FORCE_STATIC)

set (CMAKE_CXX_STANDARD 17)

find_package (uart REQUIRED)
if ("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "arm|aarch64")
    # This command will find the BSP package components
    # (BSP_HW_ENTITY, BSP_QEMU_ENTITY and BSP_CLIENT_LIB)
    find_package (bsp REQUIRED)
    include_directories (${bsp_INCLUDE})
endif ()

include_directories (${uart_INCLUDE})
add_subdirectory (nmea)
add_subdirectory (gps)
add_subdirectory (einit)
