#ifndef _PACLOUDCCONNECTIONCLIENT_HPP_
#define _PACLOUDCCONNECTIONCLIENT_HPP_

#include "VisionBaseIncludes.h"

/// \brief
/// Defines an abstract interface for a Project Anarchy Cloud Connection Client. 
/// Concrete implementations might be, for example, the Google Play Games Client client for Android or for iOS.
class PACloudConnectionClient
{
public:
  /// \brief
  /// Returns whether or not user is authenticated
  virtual bool IsAuthenticated() = 0;

  /// \brief
  /// Signs out
  virtual void SignOut() = 0;

  /// \brief
  /// Returns the authenticated user's display name
  virtual VString GetUserDisplayName() = 0;

protected:
private:
};

#endif