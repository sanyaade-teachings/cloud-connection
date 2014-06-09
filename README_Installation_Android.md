# Project Anarchy Cloud Connection Plugin Installation (Android)

This document shows you how to setup the plugin to work with your game. For details on how to use the plugin then please see the main README.md file.

## Download The Plugin

The plugin should be downloaded from GitHub to the following folder (you will need to create the "plugins" folder if it doesn't already exist)

`%HAVOK_THIRDPARTY_DIR%\plugins\cloud-connection`

(this folder is an alias of the following... `%VISION_SDK%\ThirdParty\plugins\cloud-connection`)



## Setup Your Visual Studio Project

The easiest way to setup your game is to use the included Visual Studio Property Sheets. The contain the settings you need to use the plugin in your game. They can be found in the following folder...

`%HAVOK_THIRDPARTY_DIR%\plugins\cloud-connection\PropertySheets`

Open your game solution in Visual Studio and go to the property manager tab...

![alt text](Docs/helpimages/addpropsheet1.png "Go to the property manager")

Add the relevant existing property sheet to your Application configuration. There are property sheets available for your Application & Plugin for x86/Arm and  Debug/Dev & Release configurations...

![alt text](Docs/helpimages/addpropsheet2.png "Go to the property manager")

The property sheet must be "above" the anarchy property sheet....

![alt text](Docs/helpimages/addpropsheet3.png "Go to the property manager")


You will need to perform this step for all configurations that you want to use the Plugin (this includes the Win32 build as there is a Dummy Client available to do prototyping and testing on that platform)


## Java Project Setup

The use of the cloud connection plugin requires a custom Java setup, this will override the "Deploy APK" process that is provided by default in Project Anarchy and use the Google Android ANT build process.

After the native binaries have been built in Visual Studio, the Android ANT build process is called to finish the build or java classes and libraries and package the .apk output ready for deployment to the handset.

### Add The Java Project To Your Game

Copy the contents of:

`$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\Source\platform\Android`

into your games Application folder

`$(MY_GAME)\Source\$(MY_GAME_APPLICATION)\Platform\Android`

Your manifest, Android res and java source folders will now be located in the following places and will no longer be generated or updated by the Project Anarchy "Deploy APK" process.

* Android Manifest - `$(MY_GAME)\Source\$(MY_GAME_APPLICATION)\Platform\Android\AndroidManifest.xml`
* Android Res folder (icons etc ) - `$(MY_GAME)\Source\$(MY_GAME_APPLICATION)\Platform\Android\res`
* Java Source - `$(MY_GAME)\Source\$(MY_GAME_APPLICATION)\Platform\Android\src`

Your .apk file will now be built into the following folder:

* .apk output - `$(MY_GAME)\Source\$(MY_GAME_APPLICATION)\Platform\Android\bin`

### Modify Your Manifest
 
If you already have been using your own customised AndroidManifest.xml than you can go ahead and replace the default `$(MY_GAME)\Source\$(MY_GAME_APPLICATION)\Platform\Android\AndroidManifest.xml` with your own.


You need to add these lines to your `AndroidManifest.xml` to use the Google Play Game Services (if they don't exist already)

```xml

	<meta-data android:name="com.google.android.gms.games.APP_ID" android:value="@string/app_id" />`
	<meta-data android:name="com.google.android.gms.version" android:value="@integer/google_play_services_version" />
```

Also make sure your package name and android.app.lib_name are correct

**Package Name**
```xml

	...
	<manifest xmlns:android="http://schemas.android.com/apk/res/android"
      	package="com.havok.Vision.PACCPTestGameApplication"
	...
```

**android.app.lib_name**

This should match with the name of the native binary that was built in Visual Studio e.g. PACCPTestGameApplication.so
 
```xml

	...
	<meta-data android:name="android.app.lib_name" android:value="PACCPTestGameApplication" />
	...
```

### Set Your Google Application ID

There is a resource file located at `$(MY_GAME)\Source\$(MY_GAME_APPLICATION)\Platform\Android\res\values\ids.xml` in which you should put your **Google Application ID** that you obtained when you set up google play game services.

```xml

	<string name="app_id">REPLACE_ME</string>
```

### Enable Android 2.3 / 3.x Support If Required

To support Google Play Games services correctly on handsets that are less than Android 4.0 then you should use the activity class `com.havok.Vision.CloudConnectionLifeCycleSupport`

```xml

        <activity android:name="com.havok.Vision.CloudConnectionLifeCycleSupport"
		...
```

If you have your own custom Java Activity already then you can extend it from `com.havok.Vision.CloudConnectionLifeCycleSupport`

### Customising the Build Process

There is a `custom_rules.xml` file which grab's the native binaries that were compiled in Visual Studio and also places the assets required into the final .apk.

* Custom Build - `$(MY_GAME)\Source\$(MY_GAME_APPLICATION)\Platform\Android\custom_rules.xml`

This file has hooks in it to the Android build process and you should modify this file to suit your needs if required.

### Futher Reading

The [Google Android ANT Build Process Documentation](http://developer.android.com/tools/building/building-cmdline.html) is available online for further reading on how the build process works.

## Vision ANT Tasks

The following Vision ANT Tasks can be made available to an ANT build script by including the task definitions specified in the `VisionAntTasks.jar` 

```xml

	<!-- adding the Vision ANT Tasks task definitions -->
	<taskdef resource="com/havok/Vision/anttasks/visionanttasks.properties">
		<classpath>
		  <pathelement location="ant/VisionAntTasks/VisionAntTasks.jar"/>
		</classpath>
	</taskdef>  
```

### VisionCopyLib

Copies an native library (.so) file into a the correct sub-folder for the processor architecture and removes any unneeded symbols from the file to reduce the size. It will also prefix the library with "lib" if it does not have that prefix already.

**Parameters:**

* `Arch` - REQUIRED - x86, arm or armv7  
* `Lib` - REQUIRED - The path to the .so file to be copied
* `ToDir`- REQUIRED - The path to the folder where the .so will be copied to (and placed in an the appropriate architecture sub-folder)
* `Strip` - OPTIONAL - true or false. true to strip unneeded symbols, false to leave as is/>

**Example:**

This example will copy `d:/files/mygame/bin/x86/MyGame.so` to `d:/output/libs/x86/libMyGame.so` and also remove any unneeded symbols from  `libMyGame.so`

```xml
   
	<VisionCopyLib 
	  Arch="x86" 
	  Lib="d:/files/mygame/bin/MyGame.so"
	  ToDir="d:/output/libs"
	  Strip="true"/>
```

### VisionCopyAssets

Copies assets from one folder to another. Is aware of the Vision asset management system and will try to exclude files that are not relevant to the android profile (if one is found in `AssetMgmt_data/android.aidlt` ).

**Parameters:**

* `DestinationPath` - REQUIRED - The path to a folder where the assets will be copied
* `fileset` - REQUIRED - A source folder to be copied. You can use the excludes to omit any custom folders or files (see [ANT FileSet Type](http://ant.apache.org/manual/Types/fileset.html))

**Example 1:**

Will copy the assets into `./assets/Assets` from `../../../../Assets/` while excluding the Vision asset management data thumbnails folder.  `./assets/Assets` will be created if it doesn't exist.

```xml

	<VisionCopyAssets DestinationPath="./assets">
	  <fileset dir="../../../../Assets/">
	    <include name="**"/>
	    <exclude name="**/AssetMgmt_data/thumbnails/*"/>
	  </fileset>
	</VisionCopyAssets>

```

**Example 2:**

Will copy the assets into `./assets/Data` from `../../../../Data/` while excluding the Vision asset management data thumbnails folder. `./assets/Data` will be created if it doesn't exist.

```xml

    <VisionCopyAssets DestinationPath="./assets">
      <fileset dir="../../../../Data/">
        <include name="**"/>
        <exclude name="**/AssetMgmt_data/thumbnails/*"/>
      </fileset>
    </VisionCopyAssets>

```

### VisionStripLib

Strips all unneeded symbols from the native library (.so) to reduce size and obfuscate file. This will overwrite the input library file.
 
**Parameters:**

* `Arch` - REQUIRED - x86, arm or armv7  
* `Lib` - REQUIRED - The path to the .so file to be stripped

**Example**

Removes any unneeded symbols from `MyGame.so`, overwriting `MyGame.so` with the output.

```xml

	<VisionStripLib Arch="x86" Lib="d:/files/mygame/bin/MyGame.so">
```


## Manual Setup Android

This section describes all the settings you require to setup the plugin manually if you do not want to use the property sheets.

#### Compiler params required to build with the google gpg pluging for android
* NDK tool chain version must be at least 4.8 for x86 build
* NDK tool chain version must be at least 4.6 for Arm build
* -std=gnu++11 
* -frtti 

#### PreProcessor Definitions required in developer plugin
* CLOUDCONNECTIONPLUGIN_IMPORTS in both the developer plugin and application

#### Win32 dll Only 
* Cloud Connection pluging dll must be coped into the exe target dir in the Post-Build Event step
xcopy /Y /D /C "CloudConnectionPlugin.vPluginD" "$(TargetDir)"


###include folders required

#### All platforms

`$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\Source`


#### Android
```

	$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\android\include
	$(NDKROOT)/platforms/android-9/arch-arm/usr/include
	$(NDKROOT)/sources/android/native_app_glue
```

###lib folders required

##### Arm
```

	$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\Lib\android_arm\debug (for debug only) 
	$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\Lib\android_arm\release (for release only) 
	$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\android\lib\armeabi-v7a
	$(NDKROOT)/platforms\android-9\arch-arm\usr\lib
	$(NDKROOT)/sources/cxx-stl/gnu-libstdc++/4.8/libs/armeabi-v7a
```

##### x86
```

	$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\Lib\android_arm\debug (for debug only) 
	$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\Lib\android_x86\release (for release only) 
	$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\android\lib\x86
	$(NDKROOT)/platforms\android-9\arch-x86\usr\lib
	$(NDKROOT)/sources/cxx-stl/gnu-libstdc++/4.8/libs/x86
```

### Libraries required for Linking
#### Cloud Connection Plugin
* -lCloudConnectionPlugin

#### google gpg plugin for android

* -lgpg
* -llog 
* -lz
* -lgnustl_static


#### already included by Project Anarchy project
* -landroid 
* -lEGL 
* -lGLESv1_CM

#### Android Manifest
Requires a customised Manifest from `cloud-connection\Data\Android\AndroidManifest.xml`

Add these lines to your AndroidManifest.xml

```xml

	<meta-data android:name="com.google.android.gms.games.APP_ID" android:value="@string/app_id" />`
	<meta-data android:name="com.google.android.gms.version" android:value="@integer/google_play_services_version" />
```

#### Android Activity		
Extend activity from this class to have pre-Android 4.0 support `com.havok.Vision.CloudConnectionLifeCycleSupport`

		
#### Android Google Play Services Java Library
Android build is reliant on this library (contains classes and resources), it must be compiled correctly into the final .apk
`$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\Source\platform\Android\google-play-services_lib\V4323000`

The Google Play Services APP_ID must be given in the xml in the developer build and compiled correctly into the final .apk
`res\values\ids.xml` - contains the `APP_ID` that must be changed for the developers Google Application

`<string name="app_id">REPLACE_ME</string>`
