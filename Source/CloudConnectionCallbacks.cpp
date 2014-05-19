#include "CloudConnectionPluginPCH.hpp"
#include "CloudConnectionCallbacks.hpp"

//statics
CCOnAuthActionStartedCallback CloudConnectionCallbackManager::OnAuthActionStarted;       ///< called when a sign-in event begins
CCOnAuthActionFinishedCallback CloudConnectionCallbackManager::OnAuthActionFinished;     ///< called when a sign-in event ends

CCOnAuthActionStartedCallback::CCOnAuthActionStartedCallback() {}
CCOnAuthActionStartedCallback::~CCOnAuthActionStartedCallback() {}

CCOnAuthActionFinishedCallback::CCOnAuthActionFinishedCallback() {}
CCOnAuthActionFinishedCallback::~CCOnAuthActionFinishedCallback() {}

CloudConnectionCallbackManager::CloudConnectionCallbackManager() {}
CloudConnectionCallbackManager::~CloudConnectionCallbackManager() {}