package com.havok.Vision;

import android.app.NativeActivity;
import android.util.Log;

public class NativeLibLoader extends NativeActivity
{
  private static String TAG = "NativeLibLoader";

  static
  {
    Log.v(TAG, "Static Constructor");
      
    try
    {
      //Try to load the Release FMOD libraries
      System.loadLibrary("fmodex");
      System.loadLibrary("fmodevent");
      Log.v(TAG, "Loaded FMOD Release Libraries");
    }
    catch( UnsatisfiedLinkError e )
    {
      //Try to load the debug FMOD libraries instead if the release ones aren't present
      Log.v(TAG, "Couldn't load the FMOD Release Libraries : '" + e.getMessage() + "'" );
      System.loadLibrary("fmodexL");
      System.loadLibrary("fmodeventL");
      Log.v(TAG, "Loaded FMOD Debug Libraries");
    }
  }

  public NativeLibLoader()
  {
    super();
    Log.v(TAG, "Object Constructor");
  }
}
