# Copyright (C) 2010 The Android Open Source Project
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


# This file is the device-specific product definition file for
# smdk4x12. It lists all the overlays, files, modules and properties
# that are specific to this hardware: i.e. those are device-specific
# drivers, configuration files, settings, etc...

# These is the hardware-specific overlay, which points to the location
# of hardware-specific resource overrides, typically the frameworks and
# application settings that are stored in resourced.

LOCAL_PATH := device/samsung/smdk4x12

include $(LOCAL_PATH)/BoardConfig.mk

include device/rockchip/common/phone/rk30_phone.mk
# Get the long list of APNs
PRODUCT_COPY_FILES += device/rockchip/common/phone/etc/apns-full-conf.xml:system/etc/apns-conf.xml
PRODUCT_COPY_FILES += device/rockchip/common/phone/etc/spn-conf.xml:system/etc/spn-conf.xml

DEVICE_PACKAGE_OVERLAYS := $(LOCAL_PATH)/overlay

ifeq ($(BOARD_USES_HGL),true)
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/conf/egl.cfg:system/lib/egl/egl.cfg \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libEGL_mali.so:system/lib/egl/libEGL_mali.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libGLESv1_CM_mali.so:system/lib/egl/libGLESv1_CM_mali.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libGLESv2_mali.so:system/lib/egl/libGLESv2_mali.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libMali.so:system/lib/libMali.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libMali.so:obj/lib/libMali.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libUMP.so:system/lib/libUMP.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libUMP.so:obj/lib/libUMP.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libion.so:system/lib/libion.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libion.so:obj/lib/libion.so
endif

# Init files
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/conf/init.smdk4x12.rc:root/init.smdk4x12.rc \
	$(LOCAL_PATH)/conf/init.smdk4x12.usb.rc:root/init.smdk4x12.usb.rc \
	$(LOCAL_PATH)/conf/fstab.smdk4x12:root/fstab.smdk4x12

# For V4L2
ifeq ($(BOARD_USE_V4L2), true)
ifeq ($(BOARD_USE_V4L2_ION), true)
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/conf/ueventd.smdk4x12.v4l2ion.rc:root/ueventd.smdk4x12.rc
else
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/conf/ueventd.smdk4x12.v4l2.rc:root/ueventd.smdk4x12.rc
endif
else
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/conf/ueventd.smdk4x12.rc:root/ueventd.smdk4x12.rc
endif

# Input device calibration files and Prebuilt kl and kcm keymaps
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/samsung-keypad.kl:system/usr/keylayout/samsung-keypad.kl \
	$(LOCAL_PATH)/ft5x0x_ts.idc:system/usr/idc/ft5x0x_ts.idc

# smdk4x12 hdmi
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/../common/libhdmi/libhdmiservice_jni.so:system/lib/libhdmiservice_jni.so \



#Install third part apk 
#PRODUCT_COPY_FILES += \
#        device/samsung/smdk4x12/apk/topeet/UvcWebCam/UvcWebCam.apk:system/app/UvcWebCam.apk
#PRODUCT_COPY_FILES += \
#        device/samsung/smdk4x12/apk/topeet/UvcWebCam/libImageProc.so:system/lib/libImageProc.so

#install wifi direct test tools
PRODUCT_COPY_FILES += \
        device/samsung/smdk4x12/apk/topeet/wifidirect/WiFiDirectDemo.apk:system/app/WiFiDirectDemo.apk

PRODUCT_COPY_FILES += \
	device/samsung/smdk4x12/apk/ESFileBrowser.apk:system/app/ESFileBrowser.apk  \

PRODUCT_COPY_FILES += \
	device/samsung/smdk4x12/apk/SetOrientation.apk:system/app/SetOrientation.apk  \


PRODUCT_COPY_FILES += \
	device/samsung/smdk4x12/apk/topeet/tencent_video/com.tencent.qqlive-1.apk:system/app/com.tencent.qqlive-1.apk \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libcftutils.so:system/lib/libcftutils.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libckeygenerator.so:system/lib/libckeygenerator.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libgetproperty.so:system/lib/libgetproperty.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libHWDec9.so:system/lib/libHWDec9.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libHWDec14.so:system/lib/libHWDec14.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libHWDec16.so:system/lib/libHWDec16.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libHWDec17.so:system/lib/libHWDec17.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libmresearch.so:system/lib/libmresearch.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libNativeRQD.so:system/lib/libNativeRQD.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libnonp2pproxy.so:system/lib/libnonp2pproxy.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libpilog.so:system/lib/libpilog.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libPlayerCore_neon.so:system/lib/libPlayerCore_neon.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libQQMMANDKSignature.so:system/lib/libQQMMANDKSignature.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libsta_jni.so:system/lib/libsta_jni.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libtencentloc.so:system/lib/libtencentloc.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libTxCodec_neon.so:system/lib/libTxCodec_neon.so \
	device/samsung/smdk4x12/apk/topeet/tencent_video/lib/armeabi/libwtecdh.so:system/lib/libwtecdh.so \


#Install Weather
PRODUCT_COPY_FILES += \
        device/samsung/smdk4x12/apk/topeet/weather/weather_3.0.apk:system/app/weather_3.0.apk
PRODUCT_COPY_FILES += \
        device/samsung/smdk4x12/apk/topeet/weather/liblocSDK3.so:system/lib/liblocSDK3.so

#Install topeet apk
#Install LedTest
#PRODUCT_COPY_FILES += \
#        device/samsung/smdk4x12/apk/topeet/ledtest/ledtest.apk:system/app/ledtest.apk
#PRODUCT_COPY_FILES += \
#        device/samsung/smdk4x12/apk/topeet/ledtest/libled.so:system/lib/libled.so

#Install Buzzer
#PRODUCT_COPY_FILES += \
#        device/samsung/smdk4x12/apk/topeet/buzzer/buzzertest.apk:system/app/buzzertest.apk
#PRODUCT_COPY_FILES += \
#        device/samsung/smdk4x12/apk/topeet/buzzer/libbuzzer.so:system/lib/libbuzzer.so

#Install ADC
#PRODUCT_COPY_FILES += \
#        device/samsung/smdk4x12/apk/topeet/adc/adctest.apk:system/app/adctest.apk
#PRODUCT_COPY_FILES += \
#        device/samsung/smdk4x12/apk/topeet/adc/libadc.so:system/lib/libadc.so


# Filesystem management tools
PRODUCT_PACKAGES += \
	make_ext4fs \
	setup_fs

#3G Modem	
PRODUCT_PACKAGES += \
	rild

# audio
PRODUCT_PACKAGES += \
	audio_policy.$(TARGET_PRODUCT) \
	audio.primary.$(TARGET_PRODUCT) \
	audio.a2dp.default \
	libaudioutils \
	libaudio \
	audio.r_submix.default

# audio_policy.conf
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/conf/audio_policy.conf:/system/etc/audio_policy.conf

# ALP Audio
ifeq ($(BOARD_USE_ALP_AUDIO),true)
PRODUCT_PACKAGES += \
	libOMX.SEC.MP3.Decoder
endif

# Camera
PRODUCT_PACKAGES += \
	camera.$(TARGET_PRODUCT)

# gralloc
PRODUCT_PACKAGES += \
	gralloc.$(TARGET_PRODUCT)

# gps
PRODUCT_PACKAGES += \
	gps.$(TARGET_PRODUCT)

PRODUCT_PACKAGES += \
	Superuser \
	su

# Libs
PRODUCT_PACKAGES += \
	libstagefrighthw \
	com.android.future.usb.accessory

# Misc other modules
PRODUCT_PACKAGES += \
	lights.$(TARGET_PRODUCT) \
	hwcomposer.exynos4

# OpenMAX IL configuration files
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/media_profiles.xml:system/etc/media_profiles.xml \
	$(LOCAL_PATH)/media_codecs.xml:system/etc/media_codecs.xml \
	$(LOCAL_PATH)/conf/codec.bin:system/etc/audio/codec.bin

# OpenMAX IL modules
PRODUCT_PACKAGES += \
	libSEC_OMX_Core \
	libSEC_OMX_Resourcemanager \
	libOMX.SEC.AVC.Decoder \
	libOMX.SEC.M4V.Decoder \
	libOMX.SEC.M4V.Encoder \
	libOMX.SEC.AVC.Encoder

PRODUCT_PACKAGES += \
	sqlite3 \
	stagefright

# hwconvertor modules
PRODUCT_PACKAGES += \
	libhwconverter \
	libswconverter \
	libswscaler

PRODUCT_PACKAGES += \
	libwapi

# GPS modules
PRODUCT_PACKAGES += \
	libgps

# G-sensor
PRODUCT_PACKAGES += \
	libgsensors

# MFC firmware
PRODUCT_COPY_FILES += \
	hardware/samsung_slsi/exynos4/firmware/mfc_fw.bin:system/vendor/firmware/mfc_fw.bin

PRODUCT_COPY_FILES += \
	frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml \
	frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
	frameworks/native/data/etc/android.hardware.usb.host.xml:system/etc/permissions/android.hardware.usb.host.xml \
	frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
	frameworks/native/data/etc/android.hardware.audio.low_latency.xml:system/etc/permissions/android.hardware.audio.low_latency.xml \
	frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
	frameworks/native/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml \
	frameworks/native/data/etc/tablet_core_hardware.xml:system/etc/permissions/tablet_core_hardware.xml \
	packages/wallpapers/LivePicker/android.software.live_wallpaper.xml:system/etc/permissions/android.software.live_wallpaper.xml

# The OpenGL ES API level that is natively supported by this device.
# This is a 16.16 fixed point number
PRODUCT_PROPERTY_OVERRIDES := \
	ro.opengles.version=131072

PRODUCT_PROPERTY_OVERRIDES += \
	debug.hwui.render_dirty_regions=false

# Set default USB interface
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
	persist.sys.usb.config=mtp \
	ro.kernel.android.checkjni=0

PRODUCT_CHARACTERISTICS := tablet
PRODUCT_AAPT_CONFIG := normal ldpi mdpi hdpi xhdpi xxhdpi nodpi
PRODUCT_AAPT_PREF_CONFIG := normal ldpi mdpi hdpi xhdpi xxhdpi nodpi

$(call inherit-product-if-exists, frameworks/native/build/phone-xxhdpi-2048-dalvik-heap.mk)
$(call inherit-product-if-exists, frameworks/native/build/phone-xxhdpi-2048-hwui-memory.mk)

# we have enough storage space to hold precise GC data
PRODUCT_TAGS += dalvik.gc.type-precise

#MediaTek mt66xx 
ifeq ($(strip $(BOARD_CONNECTIVITY_VENDOR)), MediaTek)

ifeq ($(strip $(BOARD_CONNECTIVITY_MODULE)), combo_mt66xx)
$(call inherit-product, hardware/mediatek/config/$(strip $(BOARD_CONNECTIVITY_MODULE))/product_package.mk)

endif

# MFC firmware
PRODUCT_COPY_FILES += \
	device/samsung/common/libwireless/mtk_hif_sdio.ko:system/lib/modules/mtk_hif_sdio.ko \
        device/samsung/common/libwireless/mtk_stp_uart.ko:system/lib/modules/mtk_stp_uart.ko \
        device/samsung/common/libwireless/mtk_stp_wmt.ko:system/lib/modules/mtk_stp_wmt.ko \
        device/samsung/common/libwireless/mtk_wmt_wifi.ko:system/lib/modules/mtk_wmt_wifi.ko \
        device/samsung/common/libwireless/wlan_mt6620.ko:system/lib/modules/wlan_mt6620.ko \
        device/samsung/common/libwireless/mtk_stp_gps.ko:system/lib/modules/mtk_stp_gps.ko \
        device/samsung/common/libwireless/mtk_stp_bt.ko:system/lib/modules/mtk_stp_bt.ko \
        device/samsung/common/libwireless/bt_uhid.ko:system/lib/modules/bt_uhid.ko \
        hardware/mediatek/config/combo_mt66xx/init.combo_mt66xx.rc:root/init.connectivity.rc \


# ext4 ex2fsck tools 
PRODUCT_COPY_FILES += \
	device/samsung/smdk4x12/tools/e2fsck/e2fsck:system/bin/e2fsck
endif






















