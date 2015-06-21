LOCAL_PATH := $(call my-dir)
ROOT_PATH := $(LOCAL_PATH)/../../../../../..

GFK_PATH := $(ROOT_PATH)
ASSIMP_PATH := $(ROOT_PATH)/lib/assimp
ENET_PATH := $(ROOT_PATH)/lib/enet
NAT_PMP_PATH := $(ROOT_PATH)/lib/libnatpmp
IF_ADDRS_PATH := $(ROOT_PATH)/lib/android-ifaddrs
NET_ADAPTER_PATH := $(ROOT_PATH)/lib/net-adapter
JET_INCLUDE_PATH := $(LOCAL_PATH)/../../../../include

GFK_SRC := ../../../../../../src

# GFK
include $(CLEAR_VARS)

LOCAL_MODULE := libgfk
LOCAL_CFLAGS := -fexceptions

LOCAL_C_INCLUDES := $(GFK_PATH)/include/ \
		    $(ASSIMP_PATH)/include/ \
		    $(JET_INCLUDE_PATH) \
		    $(ENET_PATH)/include/ \
		    $(NAT_PMP_PATH) \
		    $(NET_ADAPTER_PATH)/include/

LOCAL_SRC_FILES := \
	../../GFKAndroidWrapper.cpp \
	../../TopDownCamera.cpp \
	../../../../network/JetClient.cpp \
	../../../../network/NetworkHelper.cpp \
	../../../../network/Packet.cpp \
	../../../../network/Outbox.cpp \
	../../../../objects/ClientData.cpp \
	../../../../objects/Jet.cpp \
	../../../../objects/GameInput.cpp \
	$(GFK_SRC)/GFK/Math/Vector2.cpp \
	$(GFK_SRC)/GFK/Math/MathHelper.cpp \
	$(GFK_SRC)/GFK/Network/IPAddress.cpp \
	$(GFK_SRC)/GFK/Game.cpp \
	$(GFK_SRC)/GFK/Network/UDPSocket.cpp \
	$(GFK_SRC)/GFK/Network/BytePacker.cpp \
	$(GFK_SRC)/GFK/Network/NetworkBuffer.cpp \
	$(GFK_SRC)/GFK/Network/NetDiscoveryServer.cpp \
	$(GFK_SRC)/GFK/Network/NetDiscoveryClient.cpp \
	$(GFK_SRC)/GFK/Network/PortMapping.cpp \
	$(GFK_SRC)/GFK/Graphics/MonitorConfig.cpp \
	$(GFK_SRC)/GFK/Graphics/GraphicsDevice.cpp \
	$(GFK_SRC)/GFK/Graphics/Color.cpp \
	$(GFK_SRC)/GFK/Graphics/AssImpBridge.cpp \
	$(GFK_SRC)/GFK/Graphics/Mesh.cpp \
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

LOCAL_CPPFLAGS += -DENABLE_STRNATPMPERR
LOCAL_SHARED_LIBRARIES += libandroid
LOCAL_STATIC_LIBRARIES += libassimp
LOCAL_STATIC_LIBRARIES += libenet
LOCAL_STATIC_LIBRARIES += libnatpmp
LOCAL_STATIC_LIBRARIES += libnetadapter

include $(BUILD_STATIC_LIBRARY)

# Build our dependencies
TEMP_LOCAL_PATH := $(LOCAL_PATH)

include $(TEMP_LOCAL_PATH)/../../lib/enet/Android.mk
include $(TEMP_LOCAL_PATH)/../../lib/natpmp/Android.mk
include $(TEMP_LOCAL_PATH)/../../lib/net_adapter/Android.mk
include $(TEMP_LOCAL_PATH)/../../lib/assimp/Android.mk
