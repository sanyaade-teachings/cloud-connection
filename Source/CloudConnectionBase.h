#ifndef _CLOUDCONNECTIONBASE_H_
#define _CLOUDCONNECTIONBASE_H_

//This file gives all the includes you need to implement the Cloud Connection Plugin in a game

//Vision classes required to use the client from C++
#include "CloudConnection.hpp"
#include "CloudConnectionClient.hpp"

#if defined(_VISION_ANDROID)

//Android required includes for use of cloud connection plugin

//required to initialise the GPG state manager
#include "GPGAndroidStateManager.hpp"
#include "gpg/android_initialization.h"
#include "gpg/debug.h"

//required to statically link the plugin
VIMPORT IVisPlugin_cl* GetEnginePlugin_CloudConnectionPlugin();

#elif defined(_VISION_IOS)

//iOS required includes for use of cloud connection plugin

#else

//No platform defined for cloud connection plugin

#endif

#endif