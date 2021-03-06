# config.mk
#
# Product-specific compile-time definitions.
#
TARGET_BOARD_PLATFORM := exynos4
TARGET_SOC := exynos4x12

# CPU options
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_ARCH := arm
TARGET_ARCH_VARIANT := armv7-a-neon
TARGET_CPU_VARIANT := cortex-a9
TARGET_CPU_SMP := true
ARCH_ARM_HAVE_TLS_REGISTER := true

TARGET_NO_BOOTLOADER := true
TARGET_NO_KERNEL := true
TARGET_NO_RADIOIMAGE := true
TARGET_PROVIDES_INIT_TARGET_RC := true
TARGET_BOOTLOADER_BOARD_NAME := smdk4x12

BOARD_USES_GENERIC_AUDIO := false
BOARD_USES_I2S_AUDIO := true
BOARD_USES_PCM_AUDIO := false
BOARD_USES_SPDIF_AUDIO := false

#BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := device/samsung/smdk4x12/bluetooth
#BOARD_BLUETOOTH_DOES_NOT_USE_RFKILL := true
#BOARD_BLUETOOTH_USES_HCIATTACH_PROPERTY := true
#BOARD_HAVE_BLUETOOTH := true
#BOARD_HAVE_BLUETOOTH_BCM := true

# ULP Audio
USE_ULP_AUDIO := false

# ALP Audio
BOARD_USE_ALP_AUDIO := true

# SEC Camera
USE_SEC_CAMERA := false
CAMERA_USE_DIGITALZOOM := true
BOARD_USE_S5K3H2 := false
BOARD_USE_USBCAM := false
BOARD_USE_S5K4H5 := false

#BOARD_USES_CAMERA_LIB 	:= odroid
#BOARD_USES_CAMERA_IF 	:= uvc_video

# Enable JIT
WITH_JIT := true

BOARD_HAS_TWOSTORAGES := true
TARGET_USERIMAGES_USE_EXT4 := true
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 402653184
BOARD_USERDATAIMAGE_PARTITION_SIZE := 1610612736
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_CACHEIMAGE_PARTITION_SIZE := 402653184
BOARD_FLASH_BLOCK_SIZE := 4096

BOARD_USES_HGL := true
BOARD_NO_32BPP := true

BOARD_USES_HDMI_SUBTITLES := true
BOARD_USES_HDMI := true
BOARD_HDMI_STD := STD_720P
BOARD_HDMI_DDC_CH := DDC_CH_I2C_0
BOARD_USES_FIMGAPI := true

BOARD_USES_HDMI_EDID := true
BOARD_USES_HDMI_JUMPER := false

BOARD_USE_SAMSUNG_COLORFORMAT := true
BOARD_FIX_NATIVE_COLOR_FORMAT := true
BOARD_NONBLOCK_MODE_PROCESS := true
BOARD_USE_STOREMETADATA := true
BOARD_USE_METADATABUFFERTYPE := true
BOARD_USES_MFC_FPS := false
BOARD_USE_S3D_SUPPORT := true
BOARD_USE_CSC_FIMC := false
BOARD_USE_H264_PREPEND_SPS_PPS := true

# Enable V4L2 & ION
BOARD_USE_V4L2 := false
BOARD_USE_V4L2_ION := false
BOARD_NO_OVERLAY := false

#SCREEN_WIDTH := 1080
#SCREEN_HEIGHT := 720
SCREEN_WIDTH := 1024
SCREEN_HEIGHT := 768
DEFAULT_FB_NUM := 0
NUM_FRAMEBUFFER_SURFACE_BUFFERS := 3

USE_OPENGL_RENDERER := true

# GPS
BOARD_HAVE_X_GPS := true

#
# Wifi related defines
#
#BOARD_WIFI_VENDOR	:= realtek

#WPA_SUPPLICANT_VERSION              := VER_0_8_X
#BOARD_WPA_SUPPLICANT_DRIVER			:= NL80211
#CONFIG_DRIVER_WEXT :=y
#BOARD_WPA_SUPPLICANT_PRIVATE_LIB	:= lib_driver_cmd_rtl

#WIFI_DRIVER_MODULE_ARG           	:= ""
#WIFI_FIRMWARE_LOADER             	:= ""
#WIFI_DRIVER_FW_PATH_STA          	:= ""
#WIFI_DRIVER_FW_PATH_AP           	:= ""
#WIFI_DRIVER_FW_PATH_P2P          	:= ""
#WIFI_DRIVER_FW_PATH_PARAM        	:= ""

BOARD_WIFI_VENDOR	:= MediaTek
BOARD_CONNECTIVITY_VENDOR := MediaTek

ifeq ($(strip $(BOARD_CONNECTIVITY_VENDOR)), MediaTek)
BOARD_MEDIATEK_USES_GPS  := false
BOARD_MEDIATEK_USES_FM  := false
BOARD_CONNECTIVITY_MODULE := combo_mt66xx


ifeq ($(strip $(BOARD_CONNECTIVITY_MODULE)), combo_mt66xx)
combo_config :=  hardware/mediatek/config/$(strip $(BOARD_CONNECTIVITY_MODULE))/board_config.mk
include  $(combo_config)
endif

endif





















