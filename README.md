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

