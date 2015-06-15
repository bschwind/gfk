LOCAL_PATH := $(call my-dir)

NAT_PMP_PATH := $(LOCAL_PATH)/../../../../../../lib/libnatpmp
NAT_PMP_SRC := ../../../../../../lib/libnatpmp

# NAT_PMP
include $(CLEAR_VARS)

LOCAL_MODULE := libnatpmp
LOCAL_C_INCLUDES := ${NAT_PMP_PATH}
LOCAL_CFLAGS += -DENABLE_STRNATPMPERR
LOCAL_SRC_FILES := \
	${NAT_PMP_SRC}/natpmp.c \
	${NAT_PMP_SRC}/getgateway.c

include $(BUILD_STATIC_LIBRARY)
