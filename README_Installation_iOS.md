# Project Anarchy Cloud Connection Plugin Installation (iOS)

This document shows you how to setup the plugin to work with your game. For details on how to use the plugin then please see the main README.md file.

## Download The Plugin

The plugin should be downloaded from GitHub to the following folder (you will need to create the "plugins" folder if it doesn't already exist)

`%HAVOK_THIRDPARTY_DIR%\plugins\cloud-connection`

(this folder is an alias of the following... `%VISION_SDK%\ThirdParty\plugins\cloud-connection`)

## XCode Project Setup iOS

### Add Header Search Paths
Add the following to your "`Build Settings` -> `Search Paths` -> `Header Search Paths`"

`$(HAVOK_THIRDPARTY_DIR)/plugins/cloud-connection/Source`

### Add Library Search Paths

Add in the library search paths for the Google Play Games C++ SDK and the Google Plus iOS SDK which are included in the cloud connection files.

`$(HAVOK_THIRDPARTY_DIR)/plugins/cloud-connection/ThirdParty/redistsdks/gpg-cpp-sdk/V1.0/ios`
`$(HAVOK_THIRDPARTY_DIR)/plugins/cloud-connection/ThirdParty/redistsdks/google-plus-ios-sdk/V1.5.1`

### Library files required (Application Project Only)s

Add the the Cloud Connection libraries:

Add to `Build Settings` -> `Search Paths` -> `Library Search Paths` 

`$(HAVOK_THIRDPARTY_DIR)/plugins/cloud-connection/Lib/iOS/Debug-iphoneos/` - For debug build target
`$(HAVOK_THIRDPARTY_DIR)/plugins/cloud-connection/Lib/iOS/Release-iphoneos/` - For release build target

### In Build Settings -> Linking -> Other Linker Flags

* Add the ObjectiveC linker flag `-ObjC` to `Build Settings` -> `Linking` -> `Other Linker Flags`.
* Add the Cloud Connection library flag `-lCloudConnection`. This will link your application against the library `libCloudConnection.a` binary file.

 
### In Build Settings -> Deployment

You must set the `iOS Deployment Target` to at least `iOS 6.0` (iOS 4.3 will not work)

### In Build settings -> Custom compiler flags

* Under `Apple LLVM 5.1 - Language - C++`?, you must set the `C++ Language Dialect`? to `GNU++11 -std=gnu++11`?.
* Set the `C++ Standard Library`? to `libc++ (LLVM C++ standard library with C++ 11 support)`.
* `-std=c++98` must be removed from `Apple LLVM 5.1 - Custom Compiler Flags` -> `Other C++ Flags`
* Set `Enable C++ Runtime Types` to `Yes`

## Third Party Library, Framework & Bundle Requirements

Add the following to `Build Phases` -> `Link Binary With Libraries`

### For your Plugin Xcode Project

* From the Google Play Games C++ SDK (gpg-cpp-sdk) ( `$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\ios` )
  * gpg.framework
* From the Google+ iOS SDK (`$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\ThirdParty\redistsdks\google-plus-ios-sdk\V1.5.1`)
  * GooglePlus.framework
  * GoogleOpenSource.framework

### For your Application Xcode Project

* From the Google Play Games C++ SDK (gpg-cpp-sdk) ( `$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\ios` )
  * gpg.bundle
  * gpg.framework
* From the Google+ iOS SDK (`$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\ThirdParty\redistsdks\google-plus-ios-sdk\V1.5.1`)
  * GooglePlus.framework
  * GooglePlus.bundle
  * GoogleOpenSource.framework

Confirm that `libz` is specified under "Link Binary with Libraries" in the sample project's build-phase settings

## Setup the Google+ iOS SDK SDK
Set up the Google+ iOS SDK as described in steps 1-6 of Getting Started for iOS. [Google+ iOS SDK quickstart](https://developers.google.com/games/services/ios/quickstart)

### Notes

**Step 5: Add a sign-in and sign-out button** 

The GPGSignInButton is not supported by the C++ SDK. Instead, a button should be created with other mechanisms; clicking the button should trigger authentication (using `BeginUserInitiatedSignIn()` see README.md).

## Links

* [Google SDK's](https://developers.google.com/games/services/downloads/)
* [Google Play Services - Getting Started for iOS Game Development](https://developers.google.com/games/services/ios/quickstart)
