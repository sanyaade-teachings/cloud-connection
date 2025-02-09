/**
 * @file gpg/platform_configuration.h
 * @copyright Copyright 2014 Google Inc. All Rights Reserved.
 * @brief Declaration of platform-specific builder configuration objects.
 */

#ifndef GPG_PLATFORM_CONFIGURATION_H_
#define GPG_PLATFORM_CONFIGURATION_H_

#ifndef __cplusplus
#error Header file supports C++ only
#endif  // __cplusplus

#include "gpg/platform_defines.h"

#if defined(GPG_IOS)
#include "gpg/ios_platform_configuration.h"
namespace gpg {

/**
 * Defines the platform configuration used when creating an instance of the
 * GameServices class. Sets it to iOS.
 */
typedef IosPlatformConfiguration PlatformConfiguration;
}  // namespace gpg

#elif GPG_ANDROID
#include "gpg/android_platform_configuration.h"
namespace gpg {

/**
 * Defines the platform configuration used when creating an instance of the
 * GameServices class. Sets it to Android.
 */
typedef AndroidPlatformConfiguration PlatformConfiguration;
}  // namespace gpg

#else
#error Unsupported platform.
#endif

#endif  // GPG_PLATFORM_CONFIGURATION_H_
