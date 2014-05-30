#ifndef _CLOUDCONNECTIONBASE_H_
#define _CLOUDCONNECTIONBASE_H_

//This file gives all the includes you need to implement the Cloud Connection Plugin in a game

//Vision classes required to use the client from C++
#include "CloudConnection.hpp"
#include "CloudConnectionClient.hpp"
#include "CloudConnectionCallbacks.hpp"
#include "CloudConnectionScriptComponent.hpp"
#include "CCAchievement.hpp"

#if defined(_VISION_ANDROID) || defined(_VISION_IOS)

//Android and iOS required includes for use of cloud connection C++ plugin

//required to initialise the GPG state manager
#include "GPGStateManager.hpp"
#include "gpg/android_initialization.h"
#include "gpg/debug.h"

//required to statically link the plugin
VIMPORT IVisPlugin_cl* GetEnginePlugin_CloudConnectionPlugin();

#else

//No platform defined for cloud connection plugin

#endif

#endif