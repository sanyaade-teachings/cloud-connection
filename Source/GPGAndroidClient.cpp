#include "PACloudConnectionPluginPCH.hpp"
#include "GPGAndroidClient.hpp"

#if defined(_VISION_ANDROID)

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
  return true;
}

void GPGAndroidClient::SignOut()
{
  hkvLog::Info( "PACloudConnectionPlugin - GPGAndroidClient::SignOut()" );
}

VString GPGAndroidClient::GetUserDisplayName()
{
  return (*m_pPlayerName);
}


void GPGAndroidClient::BeginUserInitiatedSignIn() 
{
  hkvLog::Info( "PACloudConnectionPlugin - GPGAndroidClient::BeginUserInitiatedSignIn()" );
}


bool GPGAndroidClient::IsAuthInProgress()
{
  return false;
}

void GPGAndroidClient::UnlockAchievement(const VString &achievementId)
{
  hkvLog::Info( "PACloudConnectionPlugin - GPGAndroidClient::UnlockAchievement() '%s'", achievementId.AsChar() );
}

void GPGAndroidClient::ShowAchievements()
{
  hkvLog::Info( "PACloudConnectionPlugin - GPGAndroidClient::ShowAchievements()" );
}
    

void GPGAndroidClient::SubmitHighScore(const VString &leaderboardId, ULONG64 score)
{
  hkvLog::Info( "PACloudConnectionPlugin - GPGAndroidClient::SubmitHighScore() '%s',%d", leaderboardId.AsChar(), score );
}

void GPGAndroidClient::ShowLeaderboard(const VString &leaderboardId) 
{
   hkvLog::Info( "PACloudConnectionPlugin - GPGAndroidClient::ShowLeaderboard() '%s'", leaderboardId.AsChar() );
}

#endif
