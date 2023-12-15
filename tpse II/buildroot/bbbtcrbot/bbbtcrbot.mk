BBBTCRBOT_VERSION = 1.0.3
BBBTCRBOT_SITE = /home/guilherme/UFC/TPSEII/codigos/bbbtcrbot
BBBTCRBOT_SITE_METHOD = local


define BBBTCRBOT_BUILD_CMDS
	$(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) all
endef

define BBBTCRBOT_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/bbbtcrbot $(TARGET_DIR)/usr/bin/bbbtcrbot
endef

$(eval $(generic-package))
