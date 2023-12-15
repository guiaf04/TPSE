HELLO_PARAM_MODULE_VERSION = 1.0.1
HELLO_PARAM_SITE = /home/guilherme/UFC/TPSEII/drivers/driver_hello_param
HELLO_PARAM_SITE_METHOD = local
HELLO_PARAM_LICENSE = GPLv2
HELLO_PARAM_LICENSE_FILES = COPYING
HELLO_PARAM_MODULE_MAKE_OPTS = \
        CONFIG_DUMMY1= \
        CONFIG_DUMMY2=y
 
define KERNEL_MODULE_BUILD_CMDS
        $(MAKE) -C '$(@D)' LINUX_DIR='$(LINUX_DIR)' CC='$(TARGET_CC)' LD='$(TARGET_LD)' modules
endef
 
$(eval $(kernel-module))
$(eval $(generic-package))
