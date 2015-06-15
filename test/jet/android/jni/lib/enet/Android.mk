LOCAL_PATH := $(call my-dir)

ENET_PATH := $(LOCAL_PATH)/../../../../../../lib/enet
ENET_SRC := ../../../../../../lib/enet

# ENET
include $(CLEAR_VARS)

LOCAL_MODULE := libenet
LOCAL_C_INCLUDES := ${ENET_PATH}/include/
LOCAL_SRC_FILES := \
	${ENET_SRC}/callbacks.c \
	${ENET_SRC}/compress.c \
	${ENET_SRC}/host.c \
	${ENET_SRC}/list.c \
	${ENET_SRC}/packet.c \
	${ENET_SRC}/peer.c \
	${ENET_SRC}/protocol.c \
	${ENET_SRC}/unix.c

include $(BUILD_STATIC_LIBRARY)
