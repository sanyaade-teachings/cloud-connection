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
* in developer plugin OnInitEnginePlugin() call macro VISION_PLUGIN_ENSURE_LOADED(CloudConnectionPlugin);
* in developer app PreloadPlugins() call macro VISION_PLUGIN_ENSURE_LOADED(CloudConnectionPlugin);

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

#### Java
requires the Google Play Services SDK to be installed
%ADTROOT%sdk\extras\google\google_play_services\libproject\google-play-services_lib\libs
google-play-services.jar

Adding $(ADTROOT)sdk\extras\google\google_play_services\libproject\google-play-services_lib\libs\google-play-services.jar to Deploy APK -> Jar Files

#### Android Manifest
Requires a customised Manifest from
cloud-connection\Data\Android\AndroidManifest.xml

#### Android Res Folder
Reqires a customised res folder (contains default icons copied from Project Anarchy default)
cloud-connection\Data\Android\res

cloud-connection\Data\Android\res\values\ids.xml - contains the APP_ID that must be changed for the developers Google Application

Need to merge in the files from following into a temp res folder as they are required to make Google Play SDK work
$(ADTROOT)\sdk\extras\google\google_play_services\libproject\google-play-services_lib\res

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





