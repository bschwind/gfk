LOCAL_PATH := $(call my-dir)

IF_ADDRS_PATH := $(LOCAL_PATH)/../../../../../../lib/android-ifaddrs
IF_ADDRS_SRC := ../../../../../../lib/android-ifaddrs/src

# ANDROID-IFADDRS
include $(CLEAR_VARS)

LOCAL_MODULE := libandroidifaddrs
LOCAL_C_INCLUDES := ${IF_ADDRS_PATH}/include/
LOCAL_SRC_FILES := \
        ${IF_ADDRS_SRC}/ifaddrs.c \

include $(BUILD_STATIC_LIBRARY)
