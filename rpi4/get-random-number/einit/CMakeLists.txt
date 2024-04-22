project (einit)

# Tools for using NK parser.
include (platform/image)

# KasperskyOS image for target hardware platform.
build_kos_hw_image (kos-image
                    EINIT_ENTITY EinitHw
                    CONNECTIONS_CFG "init_hw.yaml.in"
                    SECURITY_PSL "security.psl.in"
                    IMAGE_FILES client_hw)

# KasperskyOS image for QEMU with simulation targets (sim, gdbsim, gdb).
build_kos_qemu_image (kos-qemu-image
                      EINIT_ENTITY EinitQemu
                      CONNECTIONS_CFG "init_qemu.yaml.in"
                      SECURITY_PSL "security.psl.in"
                      IMAGE_FILES client_qemu)

#set_target_properties (EinitQemu PROPERTIES LINK_FLAGS "-no-pie -Ttext 0x00200000")
