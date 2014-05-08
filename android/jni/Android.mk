LOCAL_PATH := $(call my-dir)
GFK_PATH := $(LOCAL_PATH)/../..

#LOCAL_SRC_FILES is relative to the jni directory
GFK_SRC := ../../src

# AssImp
include $(CLEAR_VARS)

LOCAL_MODULE := libassimp
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libassimp.so
LOCAL_EXPORT_C_INCLUDES := $(GFK_PATH)/lib/assimp/include

include $(PREBUILT_SHARED_LIBRARY)

# GFK
include $(CLEAR_VARS)

LOCAL_MODULE    := libgfk
LOCAL_CFLAGS    := -fexceptions

LOCAL_C_INCLUDES := $(GFK_PATH)/include/

LOCAL_SRC_FILES := \
	GFKAndroidWrapper.cpp \
	AndroidGame.cpp \
	$(GFK_SRC)/GFK/Math/Vector2.cpp \
	$(GFK_SRC)/GFK/Math/MathHelper.cpp \
	$(GFK_SRC)/GFK/Network/IPAddress.cpp \
	$(GFK_SRC)/GFK/GameTime.cpp \
	$(GFK_SRC)/GFK/Game.cpp \
	$(GFK_SRC)/GFK/Network/UDPSocket.cpp \
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
	$(GFK_SRC)/GFK/Graphics/AssImpBridge.cpp \
	$(GFK_SRC)/GFK/Graphics/Mesh.cpp \

LOCAL_LDLIBS    := -llog -lGLESv2
LOCAL_SHARED_LIBRARIES := libassimp

include $(BUILD_SHARED_LIBRARY)
