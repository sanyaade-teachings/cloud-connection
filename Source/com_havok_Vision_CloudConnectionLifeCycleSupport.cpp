#if defined(_VISION_ANDROID)

#include "platform\Android\jni\com_havok_Vision_CloudConnectionLifeCycleSupport.h"
#include <jni.h>
#include "gpg/android_support.h"
#include "VisionBaseIncludes.h"

// These JNI functions are for the com.havok.Vision.CloudConnectionLifeCycleSupport java class
// They are used to notify pre Android 4.0 devices about life cycle changes to the Activity.
// If it is not required to support Android 2.3 or 3.x devices then these functions are not required

JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityCreated
  (JNIEnv *env, jclass, jobject activity, jobject saved_instance_state)
{
  hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityCreated");
  gpg::AndroidSupport::OnActivityCreated(env,
                                      activity,
                                      saved_instance_state);
}

JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityDestroyed
  (JNIEnv *env, jclass thiz, jobject activity)
{
  hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityDestroyed");
  gpg::AndroidSupport::OnActivityDestroyed(env, activity);
}

JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityPaused
  (JNIEnv *env, jclass thiz, jobject activity)
{
  hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityPaused");
  gpg::AndroidSupport::OnActivityPaused(env, activity);
}

JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityResumed
  (JNIEnv *env, jclass thiz, jobject activity)
{
  hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityResumed");
  gpg::AndroidSupport::OnActivityResumed(env, activity);
}

JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivitySaveInstanceState
  (JNIEnv *env, jclass thiz, jobject activity, jobject out_state)
{
  hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivitySaveInstanceState");
  gpg::AndroidSupport::OnActivitySaveInstanceState(env, activity, out_state);
}

JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityStarted
  (JNIEnv *env, jclass thiz, jobject activity)
{
  hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityStarted");
  gpg::AndroidSupport::OnActivityStarted(env, activity);
}

JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityStopped
  (JNIEnv *env, jclass thiz, jobject activity)
{
  hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityStopped");
  gpg::AndroidSupport::OnActivityStopped(env, activity);
}


#endif