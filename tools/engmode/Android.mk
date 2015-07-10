LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:=  \
	main.c console.c ui.c font_CN16x32.c event.c \
	board_test.c process.c event_queue.c 

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include \
	$(KERNEL_HEADERS)
	
LOCAL_C_INCLUDES += hardware/samsung_slsi/exynos4/include

LOCAL_CFLAGS := -D_POSIX_SOURCE -DLINUX
LOCAL_SHARED_LIBRARIES := \
               libcutils
LOCAL_MODULE_TAGS := optional

LOCAL_MODULE:= engmode
include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:=  \
	test.c

LOCAL_C_INCLUDES := \
	config.h  ui.h event.h board_test.h  process.h \
	$(KERNEL_HEADERS)

LOCAL_CFLAGS := -D_POSIX_SOURCE -DLINUX
LOCAL_SHARED_LIBRARIES := \
               libcutils
LOCAL_MODULE_TAGS := optional

LOCAL_MODULE:= eng_dev_test
include $(BUILD_EXECUTABLE)

