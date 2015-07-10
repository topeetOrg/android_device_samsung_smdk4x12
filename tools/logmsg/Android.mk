LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := eng debug optional
LOCAL_SRC_FILES := record_panic.c logmsg_common.c
LOCAL_MODULE := record_panic_msg
LOCAL_STATIC_LIBRARIES := libcutils libc liblog
include $(BUILD_EXECUTABLE)

