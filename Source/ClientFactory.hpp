#ifndef _CLIENTFACTORY_HPP_
#define _CLIENTFACTORY_HPP_

#include "VisionBaseIncludes.h"
#include "CloudConnectionClient.hpp"
#include "DummyClient.hpp"
#include "GPGAndroidClient.hpp"
#include "GPGIOSClient.hpp"

/// \brief
/// Class contains static methods to create the Cloud Connection Client for Google Play Games for the target platform (iOS, Android, Win32)
class ClientFactory 
{
public:  
  /// \brief
  /// Creates the Plugin Instance Client For the platform you are working on
  static CloudConnectionClient* CreateCloudConnectionClient()
  {
    CloudConnectionClient* pClient = NULL;

    if ( Vision::Editor.IsInEditor() ) 
    {
      pClient = new DummyClient();
    }  
    else
    {
#if defined(_VISION_ANDROID)
      pClient = new GPGAndroidClient();
#elif defined(_VISION_IOS)
      pClient = new GPGIOSClient();
#elif defined(_VISION_WIN32)
      pClient = new DummyClient();
#else
      #error Target platform not supported for 'Google Play Games' in 'Project Anarchy Cloud Connection Plugin'
#endif
    }

    return pClient;
  }
};


#endif
