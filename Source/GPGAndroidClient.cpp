#include "CloudConnectionPluginPCH.hpp"

#if defined(_VISION_ANDROID) || defined(_VISION_IOS)

#include "GPGAndroidClient.hpp"
#include "GPGStateManager.hpp"

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

void GPGAndroidClient::GetAchievement(const char* achievementId)
{
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::GetAchievement() '%s'", achievementId );
  StateManager::FetchAchievement(achievementId);
}

void GPGAndroidClient::IncrementAchievement(const char* achievementId, int steps)
{    
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::IncrementAchievement() '%s', %d", achievementId, steps );
  StateManager::IncrementAchievement(achievementId, steps);
}

void GPGAndroidClient::SetAchievementStepsAtLeast (const char* achievementId, int steps)
{
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::SetAchievementStepsAtLeast() '%s', %d", achievementId, steps );
  StateManager::SetAchievementStepsAtLeast(achievementId, steps);
}

void GPGAndroidClient::RevealAchievement(const char* achievementId)
{
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::RevealAchievement() '%s'", achievementId );
  StateManager::RevealAchievement(achievementId);
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
    
void GPGAndroidClient::SubmitScore(const char* leaderboardId, ULONG64 score)
{
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::SubmitHighScore() '%s',%d", leaderboardId, score );
  StateManager::SubmitHighScore(leaderboardId, score);
}

void GPGAndroidClient::SubmitScore(const char* leaderboardId, ULONG64 score, const char* metadata)
{
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::SubmitHighScore() '%s',%d,'%s'", leaderboardId, score, metadata );
  StateManager::SubmitHighScore(leaderboardId, score, metadata);
}

void GPGAndroidClient::ShowLeaderboard(const char* leaderboardId) 
{
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::ShowLeaderboard() '%s'", leaderboardId );
  StateManager::ShowLeaderboard(leaderboardId);
}

void GPGAndroidClient::ShowLeaderboards()
{
  hkvLog::Debug( "PACloudConnectionPlugin - GPGAndroidClient::ShowLeaderboards()" );
  StateManager::ShowLeaderboards();
}

#endif
