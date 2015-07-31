LOCAL_PATH := $(call my-dir)
GFK_PATH := $(LOCAL_PATH)/../../../..

# Native Activity
include $(CLEAR_VARS)

LOCAL_MODULE := native-activity
LOCAL_C_INCLUDES := $(GFK_PATH)/include/ \
                    $(LOCAL_PATH)/../../common/include/ \
                    $(GFK_PATH)/lib/enet/include/ \
                    $(GFK_PATH)/lib/libnatpmp/
LOCAL_SRC_FILES := main.cpp \
                   AndroidJetGame.cpp
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2
LOCAL_STATIC_LIBRARIES := android_native_app_glue
LOCAL_STATIC_LIBRARIES += libgfk

include $(BUILD_SHARED_LIBRARY)

# Include any static library makefiles here
TEMP_LOCAL_PATH := $(LOCAL_PATH)
include $(TEMP_LOCAL_PATH)/lib/gfk/Android.mk

$(call import-module,android/native_app_glue)
