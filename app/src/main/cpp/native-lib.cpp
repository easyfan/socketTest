#include <jni.h>
#include <string>
#include <android/log.h>
#include <stdio.h>
#include "android_fopen.h"
#include <android/asset_manager_jni.h>

extern "C" {
jstring
Java_com_easyfan_sockettest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
void
Java_com_easyfan_sockettest_MainActivity_loadKSFromAssets(
        JNIEnv *env,
        jobject /* this */,
        jstring AssetsPathToKS) {
    const char *path = env->GetStringUTFChars(AssetsPathToKS, 0);
    FILE* testFile = fopen(path,"r");
    if (testFile != NULL) {
        __android_log_print(ANDROID_LOG_WARN,"loadFromAssets","File opened.");
        char buffer[50];
        fread(buffer,0,49,testFile);
        __android_log_print(ANDROID_LOG_WARN,"loadFromAssets","File loaded.");
    }
}
void
Java_com_easyfan_sockettest_MainActivity_loadAssetMgr(JNIEnv *env, jobject obj, jobject assetManager){
    AAssetManager *mgr = AAssetManager_fromJava(env, assetManager);
    if (mgr == NULL) {
        __android_log_print(ANDROID_LOG_ERROR, "name.cpp", "error loading asset manager");
    } else {
        __android_log_print(ANDROID_LOG_VERBOSE, "name.cpp", "loaded asset manager");
        android_fopen_set_asset_manager(mgr);
    }

}
}
