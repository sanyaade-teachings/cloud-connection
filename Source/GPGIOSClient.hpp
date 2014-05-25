#ifndef _GPGIOSCLIENT_HPP_
#define _GPGIOSCLIENT_HPP_
#if defined(_VISION_IOS)

#include "VisionBaseIncludes.h"
#include "CloudConnectionClient.hpp"

/// \brief
/// Defines an implementation for for a Project Anarchy CloudConnectionClient
/// for iOS that connects to the Google Games Services.
/// \note
/// Extending this class from the GPGAndroidClient as it is cross platform.
/// but can extend from CloudConnectionClient instead if that becomes a problem.
class GPGIOSClient : public GPGAndroidClient
{  
public:
  /** RTTI declarations */
	V_DECLARE_DYNAMIC_DLLEXP(GPGIOSClient, CLOUDCONNECTIONPLUGIN_IMPEXP);
    
  GPGIOSClient();
  ~GPGIOSClient();
protected:
private:
};

#endif
#endif