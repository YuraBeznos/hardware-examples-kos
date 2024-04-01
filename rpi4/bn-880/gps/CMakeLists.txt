project (client)

# Tools for using NK parser.
include (platform/nk)

# Set compiler flags.
project_header_default ("STANDARD_GNU_11:YES" "STRICT_WARNINGS:NO")

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wextra -Wpedantic -Werror")

nk_build_edl_files (client_edl_files NK_MODULE "client" EDL "${CMAKE_SOURCE_DIR}/resources/edl/GPS.edl")

add_executable (client_qemu "gps.cpp")
add_dependencies (client_qemu client_edl_files)
target_compile_definitions (client_qemu PRIVATE "-DPORT_NAME=\"${PORT_QEMU}\"")
target_link_libraries (client_qemu ${uart_CLIENT_LIB} nmea)
#set_target_properties (client_qemu PROPERTIES LINK_FLAGS "-no-pie -Ttext 0x00800000")

add_executable (client_hw "gps.cpp")
add_dependencies (client_hw client_edl_files)
target_compile_definitions (client_hw PRIVATE "-DPORT_NAME=\"${PORT_HW}\"")
target_link_libraries (client_hw ${uart_CLIENT_LIB} ${bsp_CLIENT_LIB} nmea)
#set_target_properties (client_hw PROPERTIES LINK_FLAGS "-no-pie -Ttext 0x00800000")


#find_library(libnmea NAMES nmea libnmea HINTS ${CMAKE_CURRENT_SOURCE_DIR}/nmea/build)

# Set include directories for internal/external use.
#target_include_directories(parse-nmea PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/nmea/include)
#target_include_directories(parse-nmea PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(parse-nmea ${libnmea})

