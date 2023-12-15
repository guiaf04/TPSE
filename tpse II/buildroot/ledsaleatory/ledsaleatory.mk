#LEDSALEATORY_VERSION = 1.0.0
LEDSALEATORY_SITE = /home/guilherme/UFC/TPSEII/codigos/ledsaleatory
LEDSALEATORY_SITE_METHOD = local


define LEDSALEATORY_BUILD_CMDS
	$(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) all
endef

define LEDSALEATORY_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/ledsaleatory $(TARGET_DIR)/usr/bin/ledsaleatory
endef

$(eval $(generic-package))
