## Manual Setup Android

This section describes all the settings you would require to manually setup a project to use the the plugin if you do not want to use the Visual Studio property sheets.

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
