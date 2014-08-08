#include <jni.h>
#include <android/log.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "AndroidJetGame.hpp"

#define  LOG_TAG    "libgfk"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

using namespace gfk;

namespace jetGame
{

AndroidJetGame game;

extern "C"
{
	JNIEXPORT void JNICALL Java_com_android_gfk_GFKLib_init(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_com_android_gfk_GFKLib_resize(JNIEnv * env, jobject obj, jint width, jint height);
	JNIEXPORT void JNICALL Java_com_android_gfk_GFKLib_step(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_com_android_gfk_GFKLib_unloadContent(JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL Java_com_android_gfk_GFKLib_init(JNIEnv * env, jobject obj)
{
	game.Initialize();
}

JNIEXPORT void JNICALL Java_com_android_gfk_GFKLib_resize(JNIEnv * env, jobject obj, jint width, jint height)
{
	game.ResizeWindow(width, height);
}

JNIEXPORT void JNICALL Java_com_android_gfk_GFKLib_step(JNIEnv * env, jobject obj)
{
	game.Tick();
}

JNIEXPORT void JNICALL Java_com_android_gfk_GFKLib_unloadContent(JNIEnv * env, jobject obj)
{
	game.UnloadContent();
}

}
