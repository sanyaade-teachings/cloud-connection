#ifndef _PACCP_PLAYGAMESCLIENTFACTORY_HPP_
#define _PLAYGAMESCLIENTFACTORY_HPP_

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
  static CloudConnectionClient* GetCloudConnectionClient()
  {
    if ( Vision::Editor.IsInEditor() ) 
    {
      return new DummyClient();
    }
  
#if defined(_VISION_ANDROID)
    return new GPGAndroidClient();
#elif defined(_VISION_IOS)
    return new GPGIOSClient();
#elif defined(_VISION_WIN32)
    return new DummyClient();
#else
    #error Target platform not supported for 'Google Play Games' in 'Project Anarchy Cloud Connection Plugin'
#endif
  }
};


#endif
