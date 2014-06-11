#ifndef _CLOUDCONNECTIONCALLBACKS_HPP_
#define _CLOUDCONNECTIONCALLBACKS_HPP_

#include "VisionBaseIncludes.h"

/// \brief Manager for all the callbacks required
class CloudConnectionCallbackManager
{
public:
  CloudConnectionCallbackManager();
  ~CloudConnectionCallbackManager();

  VisCallback_cl OnAuthActionStarted;      ///< called when a sign-in event begins
  VisCallback_cl OnAuthActionFinished;     ///< called when a sign-in event ends
  VisCallback_cl OnPlayerDataFetched;      ///< called when a player data has been fetched
  VisCallback_cl OnAchievementFetched;     ///< called when a single achievement has been succesfully fetched from the network
protected:
private:
};

#endif