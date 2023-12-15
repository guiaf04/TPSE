#obj-m += xxx/ yyy/
# 
#subdir-ccflags-y := -I$(src)/include
#subdir-ccflags-y += -Wall -g
 
#ifeq ($(KERNELRELEASE),)
# 
#PWD := $(shell pwd)
# 
#modules:
#        $(MAKE) -C '$(LINUX_DIR)' M='$(PWD)' modules
#clean:
#        $(MAKE) -C '$(LINUX_DIR)' M='$(PWD)' clean

obj-m += $(addsuffix .o, $(notdir $(basename $(wildcard $(BR2_EXTERNAL_KERNEL_MODULE_PATH)/*.c))))
ccflags-y := -DDEBUG -g -std=gnu99 -Wno-declaration-after-statement

.PHONY: all clean

obj-m += $(addsuffix .o, $(notdir $(basename $(wildcard $(BR2_EXTERNAL_KERNEL_MODULE_PATH)/*.c))))
ccflags-y := -DDEBUG -g -std=gnu99 -Wno-declaration-after-statement

.PHONY: all clean

all:
	$(MAKE) -C '$(LINUX_DIR)' M='$(PWD)' modules

clean:
	$(MAKE) -C '$(LINUX_DIR)' M='$(PWD)' clean
