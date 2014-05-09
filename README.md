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

### Android
* Android NDK r9d or greater (NDK previous to r9d will not work)
* Google Services SDK is installed (from the Gooogle ADK)
* Build requires compiled with C++11
* Build requires compiled with RTTI


### Compiler params required to build with the google gpg pluging for android
-std=gnu++11 -frtti 
(NOTE: builidng Game App with -frtti causes error: undefined reference to 'typeinfo for ?' errors)
### libs required to link the google gpg plugin for android
-lgpg
-llog -lz
-lgnustl_static

###already included by Project Anarchy project
-landroid -lEGL -lGLESv1_CM

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






