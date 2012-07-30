LOCAL_PATH := $(call my-dir)

MYMKBOOTIMG:=device/twm/t1/tools/mkbootimg/mkbootimg

$(INSTALLED_BOOTIMAGE_TARGET): $(MKBOOTIMG) $(INTERNAL_BOOTIMAGE_FILES)
	$(call pretty,"Target boot image: $@")
	$(hide) $(MYMKBOOTIMG) $(INTERNAL_BOOTIMAGE_ARGS) --output $@
	$(hide) $(call assert-max-image-size,$@,$(BOARD_BOOTIMAGE_PARTITION_SIZE),raw)

INSTALLED_RECOVERYIMAGE_TARGET := $(PRODUCT_OUT)/recovery.img
$(INSTALLED_RECOVERYIMAGE_TARGET): $(MKBOOTIMG) \
	$(recovery_ramdisk) \
	$(recovery_kernel)
	@echo ----- Making recovery image ------
	cp device/twm/t1/prebuilt/sdparted $(PRODUCT_OUT)/recovery/root/sbin/
	cp device/twm/t1/prebuilt/parted $(PRODUCT_OUT)/recovery/root/sbin/
	cp device/twm/t1/prebuilt/fat.format $(PRODUCT_OUT)/recovery/root/sbin/
	cp device/twm/t1/prebuilt/tune2fs $(PRODUCT_OUT)/recovery/root/sbin/
	cp device/twm/t1/prebuilt/mke2fs $(PRODUCT_OUT)/recovery/root/sbin/
	cp device/twm/t1/prebuilt/fix_permissions $(PRODUCT_OUT)/recovery/root/sbin/
	cp device/twm/t1/prebuilt/su $(PRODUCT_OUT)/recovery/root/sbin/
	echo "ro.debuggable=1" >> $(PRODUCT_OUT)/recovery/root/default.prop
	echo "persist.service.adb.enable=1" >> $(PRODUCT_OUT)/recovery/root/default.prop
	ln -s /sbin/busybox $(PRODUCT_OUT)/recovery/root//system/bin/sh
	$(MYMKBOOTIMG) $(INTERNAL_RECOVERYIMAGE_ARGS) --output $@
	@echo ----- Made recovery image -------- $@
	$(hide) $(call assert-max-image-size,$@,$(BOARD_RECOVERYIMAGE_PARTITION_SIZE),raw)

