#include "CloudConnectionPluginPCH.hpp"
#include "GPGAndroidClient.hpp"

#if defined(_VISION_ANDROID)

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
  return true;
}

void GPGAndroidClient::SignOut()
{
  hkvLog::Info( "PACloudConnectionPlugin - GPGAndroidClient::SignOut()" );
}

const char* GPGAndroidClient::GetUserDisplayName() const
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

void GPGAndroidClient::UnlockAchievement(const char* achievementId)
{
  hkvLog::Info( "PACloudConnectionPlugin - GPGAndroidClient::UnlockAchievement() '%s'", achievementId );
}

void GPGAndroidClient::ShowAchievements()
{
  hkvLog::Info( "PACloudConnectionPlugin - GPGAndroidClient::ShowAchievements()" );
}
    

void GPGAndroidClient::SubmitHighScore(const char* leaderboardId, ULONG64 score)
{
  hkvLog::Info( "PACloudConnectionPlugin - GPGAndroidClient::SubmitHighScore() '%s',%d", leaderboardId, score );
}

void GPGAndroidClient::ShowLeaderboard(const char* leaderboardId) 
{
   hkvLog::Info( "PACloudConnectionPlugin - GPGAndroidClient::ShowLeaderboard() '%s'", leaderboardId );
}

#endif
