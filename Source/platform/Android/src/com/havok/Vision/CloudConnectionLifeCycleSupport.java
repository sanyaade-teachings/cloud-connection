 package com.havok.Vision;
 /**
 * This class provides the Cloud Connection Plug with pre- Android 4.0 support for Google Play Games Services
 * If you do not wish to target pre-Android 4.0 devices then this class is not required. 
 *
 * For apps which target Android 2.3 or 3.x devices (API Version prior to 14), Play Game Services has no way to automatically receive Activity lifecycle callbacks. 
 * In these cases, Play Game Services relies on the owning Activity to notify it of lifecycle events. 
 * Any Activity which owns a GameServices object should call the AndroidSupport::* functions from within their own lifecycle callback functions. 
 * The arguments in these functions match those provided by Android, so no additional processing is necessary.
 */
 public class CloudConnectionLifeCycleSupport extends NativeLibLoader 
 {
   protected void onCreate(Bundle savedInstanceState){
     super.onCreate(savedInstanceState);
     nativeOnActivityCreated(this, savedInstanceState);
   }

   protected void onDestroy(){
     super.onDestroy();
     nativeOnActivityDestroyed(this);
   }

   protected void onPause(){
     super.onPause();
     nativeOnActivityPaused(this);
   }

   protected void onResume(){
     super.onResume();
     nativeOnActivityResumed(this);
   }

   protected void onStart(){
     super.onStart();
     nativeOnActivityStarted(this);
   }

   protected void onStop(){
     super.onStop();
     nativeOnActivityStopped(this);
   }

   protected void onSaveInstanceState(Bundle outState) {
     super.onSaveInstanceState(outState);
     nativeOnActivitySaveInstanceState(this, outState);
   }

   // The following methods are Implemented in the cloud connection C++ plugin.
   // if you want to move all these methods out of this class and into your own implmentation
   // then the names of the JNI method  calls in C++ must also be changed to match
   private static native void nativeOnActivityCreated(Activity activity, Bundle savedInstanceState);
   private static native void nativeOnActivityDestroyed(Activity activity);
   private static native void nativeOnActivityPaused(Activity activity);
   private static native void nativeOnActivityResumed(Activity activity);
   private static native void nativeOnActivitySaveInstanceState(Activity activity, Bundle outState);
   private static native void nativeOnActivityStarted(Activity activity);
   private static native void nativeOnActivityStopped(Activity activity);
 }