#ifndef _COM_HAVOK_VISION_CLOUDCONNECTIONLIFECYCLESUPPORT_INL_
#define _COM_HAVOK_VISION_CLOUDCONNECTIONLIFECYCLESUPPORT_INL_

// These JNI functions are for the com.havok.Vision.CloudConnectionLifeCycleSupport java class
// They are used to notify pre Android 4.0 devices about life cycle changes to the Activity.
// If it is not required to support Android 2.3 or 3.x devices then these functions are not required

#if defined(_VISION_ANDROID)

#include "com_havok_Vision_CloudConnectionLifeCycleSupport.h"
#include <jni.h>
#include "gpg/android_support.h"
#include "VisionBaseIncludes.h"

/// \brief used to stop the compiler removing the JNI functions
void DummyJNIFunction()
{
  //Dummy - don't strip JNI functions
  Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityCreated(NULL, NULL, NULL, NULL);
  Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityDestroyed(NULL, NULL, NULL);
  Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityPaused(NULL, NULL, NULL);
  Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityResumed(NULL, NULL, NULL);
  Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivitySaveInstanceState(NULL, NULL, NULL, NULL);
  Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityStarted(NULL, NULL, NULL);
  Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityStopped(NULL, NULL, NULL);
}

extern "C" JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityCreated
  (JNIEnv *env, jclass thiz, jobject activity, jobject saved_instance_state)
{
  if ( env != NULL )
  {      
    hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityCreated");
    gpg::AndroidSupport::OnActivityCreated(env,
                                        activity,
                                        saved_instance_state);
  }
}

extern "C" JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityDestroyed
  (JNIEnv *env, jclass thiz, jobject activity)
{
  if ( env != NULL )
  {
    hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityDestroyed");
    gpg::AndroidSupport::OnActivityDestroyed(env, activity);
  }
}

extern "C" JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityPaused
  (JNIEnv *env, jclass thiz, jobject activity)
{  
  if ( env != NULL )
  {
    hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityPaused");
    gpg::AndroidSupport::OnActivityPaused(env, activity);
  }
}

extern "C" JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityResumed
  (JNIEnv *env, jclass thiz, jobject activity)
{
  if ( env != NULL )
  {
    hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityResumed");
    gpg::AndroidSupport::OnActivityResumed(env, activity);
  }
}

extern "C" JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivitySaveInstanceState
  (JNIEnv *env, jclass thiz, jobject activity, jobject out_state)
{
  if ( env != NULL )
  {          
    hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivitySaveInstanceState");
    gpg::AndroidSupport::OnActivitySaveInstanceState(env, activity, out_state);
  }
}

extern "C" JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityStarted
  (JNIEnv *env, jclass thiz, jobject activity)
{  
  if ( env != NULL )
  {      
    hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityStarted");    
    gpg::AndroidSupport::OnActivityStarted(env, activity);
  }
}

extern "C" JNIEXPORT void JNICALL Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityStopped
  (JNIEnv *env, jclass thiz, jobject activity)
{
  if ( env != NULL )
  {         
    hkvLog::Debug("Java_com_havok_Vision_CloudConnectionLifeCycleSupport_nativeOnActivityStopped");
    gpg::AndroidSupport::OnActivityStopped(env, activity);
  }
}

#endif

#endif