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

/// \brief Callback when a single achievement has been succesfully fetched from the network
class CCOnAchievementFetchedCallback : public VCallback
{
public:
  CCOnAchievementFetchedCallback();
  ~CCOnAchievementFetchedCallback();
protected:
private:
};

/// \brief Manager for all the callbacks required
class CLOUDCONNECTIONPLUGIN_IMPEXP CloudConnectionCallbackManager
{
public:
  CloudConnectionCallbackManager();
  ~CloudConnectionCallbackManager();

  CCOnAuthActionStartedCallback OnAuthActionStarted;       ///< called when a sign-in event begins
  CCOnAuthActionFinishedCallback OnAuthActionFinished;     ///< called when a sign-in event ends
  CCOnPlayerDataFetchedCallback OnPlayerDataFetched;       ///< called when a player data has been fetched
  CCOnAchievementFetchedCallback OnAchievementFetched;     ///< called when a single achievement has been succesfully fetched from the network
protected:
private:
};

#endif