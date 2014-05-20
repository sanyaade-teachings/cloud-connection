#ifndef _CLOUDCONNECTIONCALLBACKS_HPP_
#define _CLOUDCONNECTIONCALLBACKS_HPP_

#include "VisionBaseIncludes.h"

/// \brief Callback when a sign-in event has begun
class CCOnAuthActionStartedCallback : public VCallback
{
public:
  CCOnAuthActionStartedCallback();
  ~CCOnAuthActionStartedCallback();
protected:
private:
};

/// \brief Callback when a sign-in event ends either successfully or not
class CCOnAuthActionFinishedCallback : public VCallback
{
public:
  CCOnAuthActionFinishedCallback();
  ~CCOnAuthActionFinishedCallback();
protected:
private:
};

/// \brief Callback when a the signed-in player data (such as the display name and Id) have been succesfully fetched from the network
class CCOnPlayerDataFetchedCallback : public VCallback
{
public:
  CCOnPlayerDataFetchedCallback();
  ~CCOnPlayerDataFetchedCallback();
protected:
private:
};

/// \brief Manager for all the callbacks required
class CloudConnectionCallbackManager
{
public:
  CloudConnectionCallbackManager();
  ~CloudConnectionCallbackManager();

  static CCOnAuthActionStartedCallback OnAuthActionStarted;       ///< called when a sign-in event begins
  static CCOnAuthActionFinishedCallback OnAuthActionFinished;     ///< called when a sign-in event ends
  static CCOnPlayerDataFetchedCallback OnPlayerDataFetched;       ///< called when a player data has been fetched
protected:
private:
};

#endif