obj-m += $(addsuffix .o, $(notdir $(basename $(wildcard $(BR2_EXTERNAL_KERNEL_MODULE_PATH)/*.c))))
ccflags-y := -DDEBUG -g -std=gnu99 -Wno-declaration-after-statement

.PHONY: all clean

obj-m += $(addsuffix .o, $(notdir $(basename $(wildcard $(BR2_EXTERNAL_KERNEL_MODULE_PATH)/*.c))))
ccflags-y := -DDEBUG -g -std=gnu99 -Wno-declaration-after-statement

# Define the directory where the .ko files will be copied
PASTE_DIR := $(TARGET_DIR)/lib/modules/5.10.162/kernel/drivers/hello/

.PHONY: all clean

all:
	$(MAKE) -C '$(LINUX_DIR)' M='$(PWD)' modules
	# Create the paste directory if it doesn't exist
	mkdir -p $(PASTE_DIR)
	# Copy the .ko files to the paste directory
	cp *.ko $(PASTE_DIR)

clean:
	$(MAKE) -C '$(LINUX_DIR)' M='$(PWD)' clean
	# Remove the paste directory and its contents
	rm -rf $(PASTE_DIR)

