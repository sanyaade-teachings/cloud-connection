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

/// \brief Manager for all the callbacks required
class CloudConnectionCallbackManager
{
public:
  CloudConnectionCallbackManager();
  ~CloudConnectionCallbackManager();

  static CCOnAuthActionStartedCallback OnAuthActionStarted;       ///< called when a sign-in event begins
  static CCOnAuthActionFinishedCallback OnAuthActionFinished;     ///< called when a sign-in event ends
protected:
private:
};

#endif