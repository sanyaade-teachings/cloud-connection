//  Plugin Defines removed from stdafx and placed here.
// 

#ifndef _CLOUDCONNECTIONPLUGINMODULE_H_
#define _CLOUDCONNECTIONPLUGINMODULE_H_

#ifdef WIN32
  #ifdef CLOUDCONNECTIONPLUGIN_EXPORTS
    #define CLOUDCONNECTIONPLUGIN_IMPEXP __declspec(dllexport)
  #elif CLOUDCONNECTIONPLUGIN_IMPORTS
    #define CLOUDCONNECTIONPLUGIN_IMPEXP __declspec(dllimport)
  #else
    #define CLOUDCONNECTIONPLUGIN_IMPEXP __declspec()
  #endif

#elif defined (_VISION_IOS) || defined(_VISION_ANDROID) || defined(HK_PLATFORM_TIZEN)
  #define CLOUDCONNECTIONPLUGIN_IMPEXP

#else
  #error Undefined platform!
#endif

#endif

