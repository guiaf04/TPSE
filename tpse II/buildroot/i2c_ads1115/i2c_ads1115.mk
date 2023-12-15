I2C_ADS1115_VERSION = 1.0.2
I2C_ADS1115_SITE = /home/guilherme/UFC/TPSEII/codigos/i2c_ads1115
I2C_ADS1115_SITE_METHOD = local


define I2C_ADS1115_BUILD_CMDS
	$(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) all
endef

define I2C_ADS1115_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/i2c_ads1115 $(TARGET_DIR)/usr/bin/i2c_ads1115
endef

$(eval $(generic-package))
