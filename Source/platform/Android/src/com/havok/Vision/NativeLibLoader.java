package com.havok.Vision;

import android.app.NativeActivity;
import android.util.Log;

public class NativeLibLoader extends NativeActivity
{
  private static String TAG = "NativeLibLoader";

  static
  {
      Log.v(TAG, "Static Constructor");
    System.loadLibrary("fmodexL");
    System.loadLibrary("fmodeventL");

  }

  public NativeLibLoader()
  {
    super();
    Log.v(TAG, "Object Constructor");
  }
}
