# Cloud Connection Examples

## Building the Examples

**TODO**


## Example - ScoresAchievementsCpp

Shows how to use the Plugin from the C++ interface

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