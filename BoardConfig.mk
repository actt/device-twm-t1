# Copyright (C) 2007 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# config.mk
#
# Product-specific compile-time definitions.
#

LOCAL_PATH:= $(call my-dir)

# WARNING: This line must come *before* including the proprietary
# variant, so that it gets overwritten by the parent (which goes
# against the traditional rules of inheritance).
#USE_CAMERA_STUB := false
USE_CAMERA_STUB := true

BOARD_HAS_FLIPPED_SCREEN := true
BOARD_NO_RGBX_8888 := true
TARGET_NO_BOOTLOADER := true
#BOARD_USE_FROYO_LIBCAMERA := true
TARGET_PREBUILT_RECOVERY_KERNEL := device/twm/t1/recovery_kernel

BOARD_KERNEL_CMDLINE := mem=201M console=ttyMSM2,115200n8 no_console_suspend androidboot.hardware=qcom hw_id=3

TARGET_BOARD_PLATFORM := msm7k
TARGET_ARCH_VARIANT := armv6-vfp
TARGET_CPU_ABI := armeabi
TARGET_CPU_ABI := armeabi-v6l
TARGET_CPU_ABI2 := armeabi

TARGET_BOARD_PLATFORM_GPU := qcom-adreno200
TARGET_BOOTLOADER_BOARD_NAME := t1

BOARD_HAVE_BLUETOOTH := true
BOARD_HAS_LARGE_FILESYSTEM := true
#BOARD_HAVE_FM_RADIO := true
#BOARD_GLOBAL_CFLAGS += -DHAVE_FM_RADIO
#BOARD_FM_DEVICE := si4708

# Wifi related defines
BOARD_WPA_SUPPLICANT_DRIVER := AWEXT
WIFI_DRIVER_MODULE_PATH     := /system/wifi/ar6000.ko
WIFI_DRIVER_MODULE_NAME     := ar6000

WITH_JIT := true
ENABLE_JSC_JIT := true

TARGET_LIBAGL_USE_GRALLOC_COPYBITS := true
TARGET_USES_16BPPSURFACE_FOR_OPAQUE := true

JS_ENGINE := v8

# OpenGL drivers config file path
BOARD_EGL_CFG := device/twm/t1/files/egl.cfg

# No fallback font by default (space savings)
#NO_FALLBACK_FONT:=true

BOARD_GPS_LIBRARIES := libloc_api

BOARD_USES_QCOM_HARDWARE := true
BOARD_USES_QCOM_LIBS := true
#BOARD_USES_QCOM_GPS := true
#BOARD_VENDOR_QCOM_GPS_LOC_API_HARDWARE := t1
#BOARD_VENDOR_QCOM_GPS_LOC_API_AMSS_VERSION := 1240
#BOARD_GPS_LIBRARIES := libgps librpc
BOARD_USES_GPSSHIM := true
BOARD_GPS_NEEDS_XTRA := true


#BOARD_KERNEL_BASE := 0x208000
#BOARD_PAGE_SIZE := 0x00000800
#BOARD_FORCE_RAMDISK_ADDRESS := 0x1200000

TARGET_PROVIDES_LIBRIL := true
TARGET_PROVIDES_LIBAUDIO := true

BOARD_UMS_LUNFILE := "/sys/devices/platform/msm_hsusb/gadget/lun0/file"

#reating 7 MTD partitions on "msm_nand":
# 0x000004560000-0x000004a60000 : "boot"
# 0x000004a60000-0x000005160000 : "cache"
# 0x000005160000-0x000005660000 : "recovery"
# 0x000005660000-0x0000056c0000 : "splash"
# 0x0000056c0000-0x00000ae40000 : "system"
# 0x00000ae40000-0x00000ff60000 : "userdata"
# 0x0000002c0000-0x000001d40000 : "modem"


BOARD_BOOTIMAGE_PARTITION_SIZE     := 0x00500000
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 0x00500000
#BOARD_SYSTEMIMAGE_PARTITION_SIZE   := 0x0cf80000
BOARD_SYSTEMIMAGE_PARTITION_SIZE   := 0x5780000
BOARD_USERDATAIMAGE_PARTITION_SIZE := 0x5120000
BOARD_FLASH_BLOCK_SIZE := 131072

BOARD_CUSTOM_GRAPHICS := ../../../device/twm/t1/recovery/graphics.c
BOARD_CUSTOM_RECOVERY_KEYMAPPING:= ../../device/twm/t1/recovery/recovery_ui.c
TARGET_RECOVERY_INITRC := device/twm/t1/recovery/recovery.rc
BOARD_CUSTOM_BOOTIMG_MK := device/twm/t1/custombootimg.mk
PRODUCT_LOCALES := en_US zh_TW ldpi mdpi 

