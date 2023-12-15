LEDS_VERSION = 1.0.0
LEDS_SITE = /home/guilherme/UFC/TPSEII/codigos/leds
LEDS_SITE_METHOD = local


define LEDS_BUILD_CMDS
	$(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) all
endef

define LEDS_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/leds $(TARGET_DIR)/usr/bin/leds
endef

$(eval $(generic-package))
