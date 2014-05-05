//  Plugin Defines removed from stdafx and placed here.
// 

#ifndef _PACLOUDCONNECTIONPLUGINMODULE_H_
#define _PACLOUDCONNECTIONPLUGINMODULE_H_

#ifdef WIN32
  #ifdef PACLOUDCONNECTIONPLUGIN_EXPORTS
    #define PACLOUDCONNECTIONPLUGIN_IMPEXP __declspec(dllexport)
  #elif PACLOUDCONNECTIONPLUGIN_IMPORTS
    #define PACLOUDCONNECTIONPLUGIN_IMPEXP __declspec(dllimport)
  #else
    #define PACLOUDCONNECTIONPLUGIN_IMPEXP __declspec()
  #endif

#elif defined (_VISION_IOS) || defined(_VISION_ANDROID) || defined(HK_PLATFORM_TIZEN)
  #define PACLOUDCONNECTIONPLUGIN_IMPEXP

#else
  #error Undefined platform!
#endif

#endif

