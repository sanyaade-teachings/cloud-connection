# Project Anarchy Cloud Connection Plugin

This plugin for the [Project Anarchy game engine](http://www.projectanarchy.com) allows you to interact with the [Google Play Games services](https://developers.google.com/games/services/) in Android or iOS.

## Overview
The Project Anarchy Cloud Connection Plugin provides several clients to allow you to access the Google Play Games API using either a C++ or Lua interface. The plugin provides support for the following features of the Google Play Games API:

### Google Play Games Client (Android & iOS) 
* sign in
* sign out
* unlock/reveal/increment achievement
* post score to leaderboard
* show achievements
* show leaderboards

### Dummy Client (Any Platform)
This client performs no actions and creates no connections. It is used for testing and development. This will allow you to build up code in the Win32 platform before testing it out on either iOS or Android.

## Requirements

### Project Anarchy
* Build 2014.1 or greater

### Android
* Android NDK r9d or greater (NDK previous to r9d will not work)
* Build	**MUST** be compiled with C++11 support ( -std=c++11 )
* Build **MUST** to be compiled with RTTI support ( -frtti )

### iOS
* Xcode version 5.0.1 or higher.
* A mobile device running iOS 6.0 or higher.


## Configure Your Game Service

To use the plugin, you must first [configure your 
game](https://developers.google.com/games/services/console/enabling) in the 
Google Play Developer Console. Follow the instructions on creating a client ID 
for Android and/or iOS (depending on what platforms you intend to deploy or game 
on). Be particularly careful when entering your package name and your 
certificate fingerprints, since mistakes on those screens can be difficult to 
recover from.

Please note the following pieces of information when creating your client IDs, 
as they will be necessary later:

**Android**

* Your package name (e.g. "com.example.awesomegame")
* Your application ID (e.g. 123456789012)

**iOS**

* Your bundle identifier (e.g. "com.example.AwesomeGame")
* Your application ID (e.g. 123456789012)*
* Your client ID (e.g. "46798138751-afwa4iejsfjskj.apps.googleusercontent.com")

_[*] The application ID is the number that Google Play Developer Console 
assigns to your project. Please note that is not the same as your Apple 
application ID._

**Note:** Do not forget to add your test accounts (the accounts with which you 
will try signing in) to the **Testing** section of the Developer Console, 
otherwise you will not be able to sign in to your game.

There is an excellect video here from Google that points out the [Top 7 Google Play game services setup mistakes](https://developers.google.com/live/shows/5936979195723776)

## Add Achievements and Leaderboards

Add 
[achievements](https://developers.google.com/games/services/common/concepts/achievements) 
and 
[leaderboards](https://developers.google.com/games/services/common/concepts/leaderboards) 
to your game in the Google Play Developer Console. For each achievement and 
leaderboard you configure, make sure to note the corresponding **achievement ID** or **leaderboard ID**, as those will be needed when making the API calls. 
Achievement and leaderboard IDs are alphanumeric strings (e.g. "Cgkx9eiuwi8_AQ").



## Manual Setup Android

### Compiler params required to build with the google gpg pluging for android
* -std=gnu++11 
* -frtti
*  
(NOTE: builidng Game App with -frtti causes error: undefined reference to 'typeinfo for ?' errors)

### libs required to link the google gpg plugin for android

* -lgpg
* -llog -lz
* -lgnustl_static


###already included by Project Anarchy project
* -landroid 
* -lEGL 
* -lGLESv1_CM

### PreProcessor Definitions required in developer plugin
* CLOUDCONNECTIONPLUGIN_IMPORTS in both the developer plugin and application

#### Win32 dll Only 
* Cloud Connection pluging dll must be coped into the exe target dir in the Post-Build Event step
xcopy /Y /D /C "CloudConnectionPlugin.vPluginD" "$(TargetDir)"


###include folders required

```

	cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\android\include
	$(NDKROOT)/platforms/android-9/arch-arm/usr/include
	$(NDKROOT)/sources/android/native_app_glue
```

###lib folders required

##### Arm
```

	cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\android\lib\armeabi-v7a
	$(NDKROOT)/platforms\android-9\arch-arm\usr\lib
	$(NDKROOT)/sources/cxx-stl/gnu-libstdc++/4.8/libs/armeabi-v7a
```

##### x86
```

	cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\android\lib\x86
	$(NDKROOT)/platforms\android-9\arch-x86\usr\lib
	$(NDKROOT)/sources/cxx-stl/gnu-libstdc++/4.8/libs/x86
```

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
`\cloud-connection\ThirdParty\redistsdks\google-play-services_lib\V4323000`

The Google Play Services APP_ID must be given in the xml in the developer build and compiled correctly into the final .apk
`res\values\ids.xml` - contains the `APP_ID` that must be changed for the developers Google Application

`<string name="app_id">REPLACE_ME</string>`

## Manual Setup iOS

### Library, Framework & Bundle Requirements

https://developers.google.com/games/services/downloads/

* From the Google Play Games C++ SDK (gpg-cpp-sdk) ( \cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\ios )
  * gpg.bundle
  * gpg.framework
* From the Google+ iOS SDK (\cloud-connection\ThirdParty\redistsdks\google-plus-ios-sdk\V1.5.1)
  * GooglePlus.framework
  * GooglePlus.bundle
  * GoogleOpenSource.framework

## Using the Plugin

## Initialisation

To initialize the plugin whether you wish to use it via C++ or Lua you must add the following code into your PluginMain.cpp

```C++

	#include "CloudConnectionBase.h"
	#include "com_havok_Vision_CloudConnectionLifeCycleSupport.inl"
	...
	
	// inside yourOnInitEnginePlugin() method
  	VISION_PLUGIN_ENSURE_LOADED(CloudConnectionPlugin);  
	#if defined(_VISION_ANDROID)
  		StateManager::InitServices(AndroidApplication); //Set up platform intiialization of Google Play Services
		DummyJNIFunction();   //Dummy - don't let the compiler strip JNI functions for < Android 4.0
	#endif
```

After this, the Cloud Connection client is now available in the following manner:

### in C++

```C++

	//Get the instance of the cloud connection client  
	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();
```

### in Lua

Access to plugin is via the global "CloudConnection"

```Lua

	--Get the instance of the cloud connection client
	local ccClient = CloudConnection:GetClient()
```

## Sign-In

**TODO**

## Sign-Out

**TODO**

## Revealing/Unlocking an Achievement

**TODO**

## Incrementing an Achievement

**TODO**

## Submitting a Score to a Leaderboard

**TODO**

## Showing the Achievements UI

**TODO**

## Showing the Leaderboard UI

**TODO**

## Callbacks

**TODO**

## Building for Android

When you are signing your APK file, please make sure that you are signing it with the correct certificate, that is, the one that corresponds to the SHA1 certificate fingerprint you entered in the Developer Console during the setup.

## Buidling for iOS

** TODO **






