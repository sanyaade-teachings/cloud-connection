# Project Anarchy Cloud Connection Plugin

This plugin allows you to create connection to cloud service providers from a Project Anarchy game.

## Supported Services
* Google Play Games (Android & iOS)
  * Leaderboards
  * Achievements
  
* Dummy Client (Any Platform)
   this client performs no actions and creates no connections, use for Testing and Development
  * Leaderboards (Performs no actions)
  * Achievements (Performs no actions)

## Requirements

### Project Anarchy
* Build 2014.1 or greater

### Android
* Android NDK r9d or greater (NDK previous to r9d will not work)
* Google Services SDK is installed (from the Gooogle ADK)
* Build requires compiled with C++11
* Build requires compiled with RTTI

## Manual Setup

### Compiler params required to build with the google gpg pluging for android
-std=gnu++11 -frtti 
(NOTE: builidng Game App with -frtti causes error: undefined reference to 'typeinfo for ?' errors)
### libs required to link the google gpg plugin for android
-lgpg
-llog -lz
-lgnustl_static

###already included by Project Anarchy project
-landroid -lEGL -lGLESv1_CM

### PreProcessor Definitions required in developer plugin
* CLOUDCONNECTIONPLUGIN_IMPORTS in both the developer plugin and application

#### Win32 dll Only 
* Cloud Connection pluging dll must be coped into the exe target dir in the Post-Build Event step
xcopy /Y /D /C "CloudConnectionPlugin.vPluginD" "$(TargetDir)"

#### Linking plugin

#include "CloudConnectionBase.h"
#include "com_havok_Vision_CloudConnectionLifeCycleSupport.inl"

* in developer plugin OnInitEnginePlugin() call macro VISION_PLUGIN_ENSURE_LOADED(CloudConnectionPlugin);

##### In Android
Call these functions in OnInitEnginePlugin() to initialse the Google Connection
  DummyJNIFunction();                             //Dummy - don't let the compiler strip JNI functions for < Android 4.0
  StateManager::InitServices(AndroidApplication); //Set up platform intiialization of Google Play Services

###include folders required
cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\android\include
$(NDKROOT)/platforms/android-9/arch-arm/usr/include
$(NDKROOT)/sources/android/native_app_glue

###lib folders required

##### Arm
cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\android\lib\armeabi-v7a
$(NDKROOT)/platforms\android-9\arch-arm\usr\lib
$(NDKROOT)/sources/cxx-stl/gnu-libstdc++/4.8/libs/armeabi-v7a

##### x86
cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\android\lib\x86
$(NDKROOT)/platforms\android-9\arch-x86\usr\lib
$(NDKROOT)/sources/cxx-stl/gnu-libstdc++/4.8/libs/x86

#### Android Manifest
Requires a customised Manifest from
cloud-connection\Data\Android\AndroidManifest.xml

Add these lines
		<!-- CloudConnection START - required by the google play games services GPG/GMS -->
        <meta-data android:name="com.google.android.gms.games.APP_ID" android:value="@string/app_id" />
        <meta-data android:name="com.google.android.gms.version" android:value="@integer/google_play_services_version"/>
		<!--  CloudConnection END - required by the google play games services GPG/GMS -->
		
Extend activity from this class to have pre-Android 4.0 support
com.havok.Vision.CloudConnectionLifeCycleSupport

		
#### Android Google Play Services Java Library
Android build is reliant on this library (contains classes and resources), it must be compiled correctly into the final .apk
\cloud-connection\ThirdParty\redistsdks\google-play-services_lib\V4323000

The Google Play Services APP_ID must be given in the xml in the developer build and compiled correctly into the final .apk
res\values\ids.xml - contains the APP_ID that must be changed for the developers Google Application

<string name="app_id">REPLACE_ME</string>

## iOS

### System Requirements
Xcode version 5.0.1 or higher.
A mobile device running iOS 6.0 or higher.

### Library, Framework & Bundle Requirements

https://developers.google.com/games/services/downloads/

* From the Google Play Games C++ SDK (gpg-cpp-sdk) ( \cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\ios )
	gpg.bundle
	gpg.framework
	
* From the Google+ iOS SDK (\cloud-connection\ThirdParty\redistsdks\google-plus-ios-sdk\V1.5.1)
	GooglePlus.framework
	GooglePlus.bundle
	GoogleOpenSource.framework

## Lua

### Global Access

Global access to via "CloudConnection"

e.g. To get the cloud connection user display name

  local ccClient = CloudConnection:GetClient()
  local displayName = ccClient:GetUserDisplayName()





