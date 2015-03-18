LOCAL_PATH := $(call my-dir)
GFK_PATH := $(LOCAL_PATH)/../../../..
ENET_PATH := $(LOCAL_PATH)/../../../../lib/enet
IF_ADDRS_PATH := $(LOCAL_PATH)/../../../../lib/android_ifaddrs
NET_ADAPTER_PATH := $(LOCAL_PATH)/../../../../lib/net_adapter
JET_INCLUDE_PATH := $(LOCAL_PATH)/../../include

# TODO - When the GFK library is stable enough, just include
#        the .so libraries instead of building from source
#LOCAL_SRC_FILES is relative to the jni directory
GFK_SRC := ../../../../src
ENET_SRC := ../../../../lib/enet
IF_ADDRS_SRC := ../../../../lib/android_ifaddrs/src
NET_ADAPTER_SRC := ../../../../lib/net_adapter/src



# ANDROID-IFADDRS
include $(CLEAR_VARS)

LOCAL_MODULE := libandroidifaddrs
LOCAL_C_INCLUDES := ${IF_ADDRS_PATH}/include/
LOCAL_SRC_FILES := \
	${IF_ADDRS_SRC}/ifaddrs.c \

include $(BUILD_STATIC_LIBRARY)



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



# GFK
include $(CLEAR_VARS)

LOCAL_MODULE := libgfk
LOCAL_CFLAGS := -fexceptions

LOCAL_C_INCLUDES := $(GFK_PATH)/include/ \
                    $(JET_INCLUDE_PATH) \
                    $(ENET_PATH)/include/ \
                    $(NET_ADAPTER_PATH)/include/

LOCAL_SRC_FILES := \
	GFKAndroidWrapper.cpp \
	AndroidJetGame.cpp \
	TopDownCamera.cpp \
	../../network/JetClient.cpp \
	../../network/NetworkHelper.cpp \
	../../network/Packet.cpp \
	../../network/Outbox.cpp \
	../../objects/ClientData.cpp \
	../../objects/Jet.cpp \
	../../objects/GameInput.cpp \
	$(GFK_SRC)/GFK/Math/Vector2.cpp \
	$(GFK_SRC)/GFK/Math/MathHelper.cpp \
	$(GFK_SRC)/GFK/Network/IPAddress.cpp \
	$(GFK_SRC)/GFK/Game.cpp \
	$(GFK_SRC)/GFK/Network/UDPSocket.cpp \
	$(GFK_SRC)/GFK/Network/BytePacker.cpp \
	$(GFK_SRC)/GFK/Network/NetworkBuffer.cpp \
	$(GFK_SRC)/GFK/Network/NetDiscoveryServer.cpp \
	$(GFK_SRC)/GFK/Network/NetDiscoveryClient.cpp \
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
LOCAL_STATIC_LIBRARIES += libnetadapter

include $(BUILD_SHARED_LIBRARY)
