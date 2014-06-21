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

** TODO NOT WORKING ***

`$(HAVOK_THIRDPARTY_DIR)/plugins/cloud-connection/ThirdParty/redistsdks/gpg-cpp-sdk/V1.0/ios`
`$(HAVOK_THIRDPARTY_DIR)/plugins/cloud-connection/ThirdParty/redistsdks/google-plus-ios-sdk/V1.5.1`


### Library files required (Application Project Only)

Add to `Build Settings` -> `Search Paths` -> `Library Search Paths` 

`$(HAVOK_THIRDPARTY_DIR)/plugins/cloud-connection/Lib/iOS/Debug-iphoneos/`
`$(HAVOK_THIRDPARTY_DIR)/plugins/cloud-connection/Lib/iOS/Release-iphoneos/`

Add the Cloud Connection library `-lCloudConnection` to `Build Settings` -> `Linking` -> `Other Linker Flags`.
This will link your application against the library `libCloudConnection.a`

** TODO : LINK AGAINST THE GPG libraries **

** TODO: see guide on linking with the Google Play Games services SDK **
https://developers.google.com/games/services/ios/quickstart
https://developers.google.com/games/services/ios/quickstart#option_2_manual_installation
 
### In Build Settings -> Deployment

You must set the “iOS Deployment Target” to at least “iOS 6.0” (iOS 4.3 will not work)

### In Build settings -> ‘Custom compiler flags’

Under “Apple LLVM 5.1 - Language - C++”, you must set the “C++ Language Dialect” to “GNU++11 -std=gnu++11” and the “C++ Standard Library” to “libc++ (LLVM C++ standard library with C++ 11 support)

`-std=c++98` must be removed from “Apple LLVM 5.1 - Custom Compiler Flags” -> “Other C++ Flags”

Set `Enable C++ Runtime Types` to `Yes`

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


## Links

* Google SDK’s - https://developers.google.com/games/services/downloads/
