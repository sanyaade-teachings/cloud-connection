#ifndef _DUMMYCLIENT_HPP_
#define _DUMMYCLIENT_HPP_

#include "VisionBaseIncludes.h"
#include "PACloudConnectionClient.hpp"


/// \brief
/// Defines an concrete implementation for for a Project Anarchy Cloud Connection Client that provides
/// No functionality and can be used for testing on any platform
class DummyClient : public PACloudConnectionClient
{
public:
  DummyClient();
  ~DummyClient();

  /// \brief
  /// Returns whether or not user is authenticated
  virtual bool IsAuthenticated() HKV_OVERRIDE;

  /// \brief
  /// Signs out
  virtual void SignOut() HKV_OVERRIDE;

  /// \brief
  /// Returns the authenticated user's display name
  virtual VString GetUserDisplayName() HKV_OVERRIDE;
protected:
private:
  VString* m_pPlayerName;
};


#endif