# Project Anarchy Cloud Connection Plugin Installation (iOS)

This document shows you how to setup the plugin to work with your game. For details on how to use the plugin then please see the main README.md file.

## Download The Plugin

The plugin should be downloaded from GitHub to the following folder (you will need to create the "plugins" folder if it doesn't already exist)

`%HAVOK_THIRDPARTY_DIR%\plugins\cloud-connection`

(this folder is an alias of the following... `%VISION_SDK%\ThirdParty\plugins\cloud-connection`)

## XCode Project Setup iOS

### Add Header Search Paths
Add the following to your "`Build Settings` -> `Search Paths` -> `Header Search Paths`"

`$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\Source`

### Add Library Search Paths

** TODO NOT WORKING ***

`$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\ThirdParty\redistsdks\gpg-cpp-sdk\V1.0\ios`
`$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\ThirdParty\redistsdks\google-plus-ios-sdk\V1.5.1`



### Library file required
link against library `libCloudConnection.a`
 
`$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\Lib\iOS\Release-iphone\libCloudConnection.a`

or

`$(HAVOK_THIRDPARTY_DIR)\plugins\cloud-connection\Lib\iOS\Debug-iphone\libCloudConnection.a`

### In project settings ‘Custom compiler flags’
`-std=c++98` must be changed for `-std=c++11`

### Third Party Library, Framework & Bundle Requirements

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
