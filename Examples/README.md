# Cloud Connection Examples

## Building the Examples

To build and run this application successfully you must do the following:

### Run the RUN_ONCE.bat 

This will copy in the data files required by the Vision engine to run the game, they are not included in the download to save space.

### Add Your Google Application ID

Change the REPLACE_ME value for the value provided to you by Google. Note that although the value given to you by Google is numeric, it must stay marked as a "string" value in the xml file.

The value is found in this file...

`ScoresAchievementsCpp\Source\ScoresAchievementsCppApp\Platform\Android\res\values\ids.xml`

```xml

	<string name="app_id">REPLACE_ME</string>
```

If you don't have a Google Application ID yet then you need to set one up, have an look on the main README.md file for information on how to configure your game.


## Example - ScoresAchievementsCpp

Shows how to use the Plugin from the C++ interface.

**TODO** - MAIN CLASSES

## Common Problems

### "Application ID (REPLACE_ME) must be a numeric value" - Runtime Error

You have not set your Goole Application ID in the ids.xml. See the section "*Set Your Google Application ID*" in the Android Installation readme file.

```

	E/ValidateServiceOp(2857): Application ID (REPLACE_ME) must be a numeric value. Please verify 
	that your manifest refers to the correct project ID.
	I/ActivityManager(1641): Displayed com.havok.Vision.ScoresAchievementsCppApp/com.havok.Vision.CloudConnectionLifeCycleSupport: +1s445ms
	V/threaded_app(30633): NativeWindowCreated: 0x307480 -- 0x4fbb70
	V/threaded_app(30633): APP_CMD_INIT_WINDOW
	D/AndroidRuntime(30633): Shutting down VM
	W/dalvikvm(30633): threadid=1: thread exiting with uncaught exception (group=0x40018560)
	E/AndroidRuntime(30633): FATAL EXCEPTION: main
	E/AndroidRuntime(30633): java.lang.IllegalStateException: A fatal developer error has occurred. Check the logs for further information.
	E/AndroidRuntime(30633): 	at com.google.android.gms.internal.eh$h.b(Unknown Source)
```

### "Unable to resolve project target" - Build Error 

**TODO**

```

	1>  BUILD FAILED
	1>  C:\Android\sdk\tools\ant\build.xml:601: The following error occurred while executing this line:
	1>  C:\Android\sdk\tools\ant\build.xml:542: Unable to resolve project target 'Google Inc.:Google APIs:18'
```

### TODO: UnAuthorised!!