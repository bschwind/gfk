LOCAL_PATH := $(call my-dir)
GFK_PATH := $(LOCAL_PATH)/../../../..
ENET_PATH := $(LOCAL_PATH)/../../../../lib/enet
JET_INCLUDE_PATH := $(LOCAL_PATH)/../../include

# TODO - When the GFK library is stable enough, just include
#        the .so libraries instead of building from source
#LOCAL_SRC_FILES is relative to the jni directory
GFK_SRC := ../../../../src
ENET_SRC := ../../../../lib/enet

# ENET

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
	${ENET_SRC}/unix.c \

include $(BUILD_STATIC_LIBRARY)

# GFK
include $(CLEAR_VARS)

LOCAL_MODULE := libgfk
LOCAL_CFLAGS := -fexceptions

LOCAL_C_INCLUDES := $(GFK_PATH)/include/ \
                    $(JET_INCLUDE_PATH) \
                    $(ENET_PATH)/include/

LOCAL_SRC_FILES := \
	GFKAndroidWrapper.cpp \
	AndroidJetGame.cpp \
	TopDownCamera.cpp \
	../../network/NetworkHelper.cpp \
	../../network/Packet.cpp \
	../../network/Outbox.cpp \
	../../objects/ClientData.cpp \
	../../objects/Jet.cpp \
	$(GFK_SRC)/GFK/Math/Vector2.cpp \
	$(GFK_SRC)/GFK/Math/MathHelper.cpp \
	$(GFK_SRC)/GFK/Network/IPAddress.cpp \
	$(GFK_SRC)/GFK/Game.cpp \
	$(GFK_SRC)/GFK/Network/UDPSocket.cpp \
	$(GFK_SRC)/GFK/Network/BytePacker.cpp \
	$(GFK_SRC)/GFK/Network/NetworkBuffer.cpp \
	$(GFK_SRC)/GFK/Graphics/MonitorConfig.cpp \
	$(GFK_SRC)/GFK/Graphics/GraphicsDevice.cpp \
	$(GFK_SRC)/GFK/Graphics/Color.cpp \
	$(GFK_SRC)/GFK/Graphics/PackedColor.cpp \
	$(GFK_SRC)/GFK/Graphics/Camera2D.cpp \
	$(GFK_SRC)/GFK/Math/Matrix.cpp \
	$(GFK_SRC)/GFK/Math/Quaternion.cpp \
	$(GFK_SRC)/GFK/Math/Vector3.cpp \
	$(GFK_SRC)/GFK/Graphics/Camera.cpp \
	$(GFK_SRC)/GFK/Graphics/Shader.cpp \
	$(GFK_SRC)/GFK/Graphics/PrimitiveBatch2D.cpp \
	$(GFK_SRC)/GFK/Graphics/PrimitiveBatch3D.cpp \
	$(GFK_SRC)/GFK/Graphics/GLErrorHandling.cpp \
	$(GFK_SRC)/GFK/System/GameTime.cpp \
	$(GFK_SRC)/GFK/System/Logger.cpp \

LOCAL_LDLIBS := -llog -lGLESv2
LOCAL_SHARED_LIBRARIES += libandroid
LOCAL_STATIC_LIBRARIES += libenet

include $(BUILD_SHARED_LIBRARY)
