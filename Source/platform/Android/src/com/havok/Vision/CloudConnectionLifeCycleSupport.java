 package com.havok.Vision;
 
 import android.os.Bundle;
 import android.app.Activity;
 import android.util.Log;
 import android.content.pm.ApplicationInfo;
 import android.content.pm.ActivityInfo;
 import android.content.pm.PackageManager.NameNotFoundException;
 import android.content.pm.PackageManager;
 
 /**
 * This class provides the Cloud Connection Plugin with pre- Android 4.0 support for Google Play Games Services
 * If you do not wish to target pre-Android 4.0 devices then this class is not required. 
 *
 * For apps which target Android 2.3 or 3.x devices (API Version prior to 14), Play Game Services has no way to automatically receive Activity lifecycle callbacks. 
 * In these cases, Play Game Services relies on the owning Activity to notify it of lifecycle events. 
 * Any Activity which owns a GameServices object should call the AndroidSupport::* functions from within their own lifecycle callback functions. 
 * The arguments in these functions match those provided by Android, so no additional processing is necessary.
 */
 public class CloudConnectionLifeCycleSupport extends NativeLibLoader 
 {
  private static String TAG = "CloudConnectionLifeCycleSupport";
    
  // The following methods are Implemented in the cloud connection C++ plugin.
  // if you want to move all these methods out of this class and into your own implementation
  // then the names of the JNI method  calls in C++ must also be changed to match
  private static native void nativeOnActivityCreated(Activity activity, Bundle savedInstanceState);
  private static native void nativeOnActivityDestroyed(Activity activity);
  private static native void nativeOnActivityPaused(Activity activity);
  private static native void nativeOnActivityResumed(Activity activity);
  private static native void nativeOnActivitySaveInstanceState(Activity activity, Bundle outState);
  private static native void nativeOnActivityStarted(Activity activity);
  private static native void nativeOnActivityStopped(Activity activity);

  /** Loads the Native Library defined in android.app.lib_name
  *
  * if you do not load the library that contains the native JNI callbacks then they will not function
  * make sure the native library that contains the JNI callbacks has been loaded. In our case it should be
  * our main android app shared library that is defined in the manifest as android.app.lib_name*/ 
  void loadNativeLibrary()
  { 
    try 
    {
      ActivityInfo ai = getPackageManager().getActivityInfo( getComponentName(), PackageManager.GET_META_DATA);
      Bundle bundle = ai.metaData;
      String androidAppLibName = bundle.getString("android.app.lib_name");
      Log.v(TAG, "loadLibrary("+androidAppLibName+")");
      System.loadLibrary(androidAppLibName);
    } 
    catch (NameNotFoundException e) 
    {
      Log.e(TAG, "Failed to load meta-data 'android.app.lib_name', NameNotFound: " + e.getMessage());
    } 
    catch (NullPointerException e) 
    {
      Log.e(TAG, "Failed to load meta-data 'android.app.lib_name', NullPointer: " + e.getMessage());        
    }
  }  
 
  public void onCreate(Bundle savedInstanceState){
    super.onCreate(savedInstanceState);
    loadNativeLibrary();  //makes sure our main android native library is loaded or JNI calls won't work
    try
    {
      nativeOnActivityCreated(this, savedInstanceState);
    }
    catch( UnsatisfiedLinkError e )
    {
      if ( android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.ICE_CREAM_SANDWICH )
      {
        Log.w(TAG, "pre-Android 4.0 Life Cycle Support is not working", e);
      }
    }
  }

  public void onDestroy(){
    super.onDestroy();
    try
    {
      nativeOnActivityDestroyed(this);
    }
    catch( UnsatisfiedLinkError e )
    {
      if ( android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.ICE_CREAM_SANDWICH )
      {
        Log.w(TAG, "pre-Android 4.0 Life Cycle Support is not working", e);
      }
    }
  }

  public void onPause(){
    super.onPause();
    try
    {
      nativeOnActivityPaused(this);
    }
    catch( UnsatisfiedLinkError e )
    {
      if ( android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.ICE_CREAM_SANDWICH )
      {
        Log.w(TAG, "pre-Android 4.0 Life Cycle Support is not working", e);
      }
    }
  }

  public void onResume(){
    super.onResume();
    try
    {
      nativeOnActivityResumed(this);
    }
    catch( UnsatisfiedLinkError e )
    {
      if ( android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.ICE_CREAM_SANDWICH )
      {
        Log.w(TAG, "pre-Android 4.0 Life Cycle Support is not working", e);
      }
    } 
  }

  public void onStart(){
    super.onStart();     
    try
    {
      nativeOnActivityStarted(this);
    }
    catch( UnsatisfiedLinkError e )
    {
      if ( android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.ICE_CREAM_SANDWICH )
      {
        Log.w(TAG, "pre-Android 4.0 Life Cycle Support is not working", e);
      }
    }	 
  }

  public void onStop(){
    super.onStop();
    try
    {
      nativeOnActivityStopped(this);
    }
    catch( UnsatisfiedLinkError e )
    {
      if ( android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.ICE_CREAM_SANDWICH )
      {
        Log.w(TAG, "pre-Android 4.0 Life Cycle Support is not working", e);
      }
    }	 
  }

  public void onSaveInstanceState(Bundle outState) {
    super.onSaveInstanceState(outState);     
    try
    {
      nativeOnActivitySaveInstanceState(this, outState);
    }
    catch( UnsatisfiedLinkError e )
    {
      if ( android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.ICE_CREAM_SANDWICH )
      {
        Log.w(TAG, "pre-Android 4.0 Life Cycle Support is not working", e);
      }
    }	 
  }
 }