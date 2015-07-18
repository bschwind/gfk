LOCAL_PATH := $(call my-dir)

NET_ADAPTER_PATH := $(LOCAL_PATH)/../../../../../../lib/net-adapter
NET_ADAPTER_SRC := ../../../../../../lib/net-adapter/src

# NET_ADAPTER
include $(CLEAR_VARS)

LOCAL_MODULE := libnetadapter
LOCAL_C_INCLUDES := ${NET_ADAPTER_PATH}/include/ \
					${IF_ADDRS_PATH}/include/
LOCAL_STATIC_LIBRARIES += libandroidifaddrs
LOCAL_SRC_FILES := \
	${NET_ADAPTER_SRC}/NetAdapter_Shared.cpp \
	${NET_ADAPTER_SRC}/NetAdapter_Unix.cpp \

include $(BUILD_STATIC_LIBRARY)

# Build our dependencies
TEMP_LOCAL_PATH := $(LOCAL_PATH)

include $(TEMP_LOCAL_PATH)/../../lib/android_ifaddrs/Android.mk
