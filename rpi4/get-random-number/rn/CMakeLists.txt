project (client)

# Tools for using NK parser.
include (platform/nk)

# Set compiler flags.
project_header_default ("STANDARD_GNU_11:YES" "STRICT_WARNINGS:NO")

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wextra -Wpedantic -Werror")

nk_build_edl_files (client_edl_files NK_MODULE "client" EDL "${CMAKE_SOURCE_DIR}/resources/edl/RN.edl")

add_executable (client_qemu "main.cpp")
add_dependencies (client_qemu client_edl_files)
target_compile_definitions (client_qemu PRIVATE "-DPORT_NAME=\"${PORT_QEMU}\"")
target_link_libraries (client_qemu)
#set_target_properties (client_qemu PROPERTIES LINK_FLAGS "-no-pie -Ttext 0x00800000")

add_executable (client_hw "main.cpp")
add_dependencies (client_hw client_edl_files)
target_compile_definitions (client_hw PRIVATE "-DPORT_NAME=\"${PORT_HW}\"")
target_link_libraries (client_hw ${bsp_CLIENT_LIB})
#set_target_properties (client_hw PROPERTIES LINK_FLAGS "-no-pie -Ttext 0x00800000")


