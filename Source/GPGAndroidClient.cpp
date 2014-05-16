#include "CloudConnectionPluginPCH.hpp"

#if defined(_VISION_ANDROID)

#include "GPGAndroidClient.hpp"
#include "GPGAndroidStateManager.hpp"

/** RTTI definitions */
V_IMPLEMENT_DYNAMIC( GPGAndroidClient, CloudConnectionClient, &g_CloudConnectionModule );

GPGAndroidClient::GPGAndroidClient()
{
  m_pPlayerName = new VString("GPGAndroidClient Dummy Player");
}

GPGAndroidClient::~GPGAndroidClient()
{
  V_SAFE_DELETE( m_pPlayerName );
}

bool GPGAndroidClient::IsAuthenticated()
{
  bool auth = false;
  gpg::GameServices* gameservices = StateManager::GetGameServices();
  if ( gameservices != NULL )
  {
    auth = gameservices->IsAuthorized();
  }
  return auth;
}

void GPGAndroidClient::SignOut()
{
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::SignOut()" );    
  StateManager::SignOut();
}

const char* GPGAndroidClient::GetUserDisplayName() const
{
  gpg::GameServices* gameservices = StateManager::GetGameServices();
  if ( gameservices != NULL )
  {     
    if ( !gameservices->IsAuthorized() ) 
    {
      //get the players google+ name
      hkvLog::Warning( "PACloudConnectionPlugin - GPGAndroidClient::GetUserDisplayName() - METHOD NOT YET IMPLEMENTED" );    
    }
  }
      
  return (*m_pPlayerName);
}


void GPGAndroidClient::BeginUserInitiatedSignIn() 
{
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::BeginUserInitiatedSignIn()" );
  StateManager::BeginUserInitiatedSignIn();
}


bool GPGAndroidClient::IsAuthInProgress()
{
  return StateManager::IsAuthInProgress();
}

void GPGAndroidClient::UnlockAchievement(const char* achievementId)
{
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::UnlockAchievement() '%s'", achievementId );
  StateManager::UnlockAchievement(achievementId);
}

void GPGAndroidClient::ShowAchievements()
{
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::ShowAchievements()" );
  StateManager::ShowAchievements();
}
    

void GPGAndroidClient::SubmitHighScore(const char* leaderboardId, ULONG64 score)
{
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::SubmitHighScore() '%s',%d", leaderboardId, score );
  StateManager::SubmitHighScore(leaderboardId, score);
}

void GPGAndroidClient::ShowLeaderboard(const char* leaderboardId) 
{
   hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::ShowLeaderboard() '%s'", leaderboardId );
   StateManager::ShowLeaderboard(leaderboardId);
}

#endif
