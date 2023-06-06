export V ?= 0

OUTPUT_DIR := $(CURDIR)/out

APP_LIST := $(subst /,,$(dir $(wildcard */Makefile)))

.PHONY: all
all: my_apps 
#prepare-for-rootfs

.PHONY: clean
clean: my_apps-clean 
#prepare-for-rootfs-clean

my_apps:
	@for app in $(APP_LIST); do \
		$(MAKE) -C $$app CROSS_COMPILE="$(HOST_CROSS_COMPILE)" || exit 1; \
	done

my_apps-clean:
	@for app in $(APP_LIST); do \
		$(MAKE) -C $$app clean || exit 1; \
	done

# TODO: fill this one later
# prepare-for-rootfs: my_apps
# 	@echo "Copying app CA and TA binaries to $(OUTPUT_DIR)..."
# 	@mkdir -p $(OUTPUT_DIR)
# 	@mkdir -p $(OUTPUT_DIR)/ta
# 	@mkdir -p $(OUTPUT_DIR)/ca
# 	@mkdir -p $(OUTPUT_DIR)/plugins
# 	@for app in $(APP_LIST); do \
# 		if [ -e $$app/host/optee_app_$$app ]; then \
# 			cp -p $$app/host/optee_app_$$app $(OUTPUT_DIR)/ca/; \
# 		fi; \
# 		cp -pr $$app/ta/*.ta $(OUTPUT_DIR)/ta/; \
# 		if [ $$app = plugins ]; then \
# 			cp -p plugins/syslog/*.plugin $(OUTPUT_DIR)/plugins/; \
# 		fi; \
# 	done

