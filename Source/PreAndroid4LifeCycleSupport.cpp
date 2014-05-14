#if defined(_VISION_ANDROID)

#include <jni.h>
#include "gpg/android_support.h"

// These JNI functions are for the com.havok.Vision.CloudConnectionLifeCycleSupport java class
// They are used to notify pre Android 4.0 devices about life cycle changes to the Activity.
// If it is not required to support Android 2.3 or 3.x devices then these functions are not required

extern "C"
{
  void Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityCreated(
       JNIEnv *env,
       jobject thiz,
       jobject activity,
       jobject saved_instance_state) {
     gpg::AndroidSupport::OnActivityCreated(env,
                                            activity,
                                            saved_instance_state);
   }

  void Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityDestroyed(
      JNIEnv *env, jobject thiz, jobject activity) {
    gpg::AndroidSupport::OnActivityDestroyed(env, activity);
  }

  void Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityPaused(
      JNIEnv *env, jobject thiz, jobject activity) {
    gpg::AndroidSupport::OnActivityPaused(env, activity);
  }

  void Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityResumed(
      JNIEnv *env, jobject thiz, jobject activity) {
    gpg::AndroidSupport::OnActivityResumed(env, activity);
  }

  void Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivitySaveInstanceState(
      JNIEnv *env, jobject thiz, jobject activity, jobject out_state) {
    gpg::AndroidSupport::OnActivitySaveInstanceState(env, activity, out_state);
  }

  void Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityStarted(
      JNIEnv *env, jobject thiz, jobject activity) {
    gpg::AndroidSupport::OnActivityStarted(env, activity);
  }

  void Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityStopped(
      JNIEnv *env, jobject thiz, jobject activity) {
    gpg::AndroidSupport::OnActivityStopped(env, activity);
  }
}

#endif