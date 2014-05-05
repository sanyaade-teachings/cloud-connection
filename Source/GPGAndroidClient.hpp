#ifndef _GPGANDROIDCLIENT_HPP_
#define _GPGANDROIDCLIENT_HPP_
#if defined(_VISION_ANDROID)

#include "VisionBaseIncludes.h"
#include "PACloudConnectionClient.hpp"

/// \brief
/// Defines an concrete implementation for for a Project Anarchy Cloud Connection Client.
/// Provides the Google Play Games Android Client
class GPGAndroidClient : public PACloudConnectionClient
{
  /// \brief
  /// Returns whether or not user is authenticated
  virtual bool IsAuthenticated() HKV_OVERRIDE;

  /// \brief
  /// Signs out
  virtual void SignOut() HKV_OVERRIDE;

  /// \brief
  /// Returns the authenticated user's display name
  virtual VString GetUserDisplayName() HKV_OVERRIDE;
};

#endif
#endif
