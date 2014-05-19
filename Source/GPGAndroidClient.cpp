#include "CloudConnectionPluginPCH.hpp"

#if defined(_VISION_ANDROID)

#include "GPGAndroidClient.hpp"
#include "GPGAndroidStateManager.hpp"

/** RTTI definitions */
V_IMPLEMENT_DYNAMIC( GPGAndroidClient, CloudConnectionClient, &g_CloudConnectionModule );

GPGAndroidClient::GPGAndroidClient()
{
}

GPGAndroidClient::~GPGAndroidClient()
{
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
    if ( gameservices->IsAuthorized() ) 
    {
      gpg::Player* player = StateManager::GetSignedInPlayer();
      if ( player != NULL )
      {
        return player->Name().c_str();          //get the players google+ name
      }
      else
      {
        return "Player";
      }
    }
  }
      
  return "Player";
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
