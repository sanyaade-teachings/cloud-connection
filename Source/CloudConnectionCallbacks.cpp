#include "CloudConnectionPluginPCH.hpp"
#include "CloudConnectionCallbacks.hpp"

//statics
CCOnAuthActionStartedCallback CloudConnectionCallbackManager::OnAuthActionStarted;       ///< called when a sign-in event begins
CCOnAuthActionFinishedCallback CloudConnectionCallbackManager::OnAuthActionFinished;     ///< called when a sign-in event ends
CCOnPlayerDataFetchedCallback CloudConnectionCallbackManager::OnPlayerDataFetched;       ///< called when a player data has been fetched

CCOnAuthActionStartedCallback::CCOnAuthActionStartedCallback() {}
CCOnAuthActionStartedCallback::~CCOnAuthActionStartedCallback() {}

CCOnAuthActionFinishedCallback::CCOnAuthActionFinishedCallback() {}
CCOnAuthActionFinishedCallback::~CCOnAuthActionFinishedCallback() {}
 
CCOnPlayerDataFetchedCallback::CCOnPlayerDataFetchedCallback() {}
CCOnPlayerDataFetchedCallback::~CCOnPlayerDataFetchedCallback() {}

CloudConnectionCallbackManager::CloudConnectionCallbackManager() {}
CloudConnectionCallbackManager::~CloudConnectionCallbackManager() {}
