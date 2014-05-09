#include "CloudConnectionPluginPCH.hpp"
#include "DummyClient.hpp"

/** RTTI definitions */
V_IMPLEMENT_DYNAMIC( DummyClient, CloudConnectionClient, &g_CloudConnectionModule );
   
DummyClient::DummyClient()
{
  m_pPlayerName = new VString("Dummy Player");
}

DummyClient::~DummyClient()
{
  V_SAFE_DELETE( m_pPlayerName );
}

bool DummyClient::IsAuthenticated()
{
  return true;
}

void DummyClient::SignOut()
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::SignOut()" );
}

VString DummyClient::GetUserDisplayName()
{
  return (*m_pPlayerName);
}


void DummyClient::BeginUserInitiatedSignIn() 
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::BeginUserInitiatedSignIn()" );
}


bool DummyClient::IsAuthInProgress()
{
  return false;
}

void DummyClient::UnlockAchievement(const VString &achievementId)
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::UnlockAchievement() '%s'", achievementId.AsChar() );
}

void DummyClient::ShowAchievements()
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::ShowAchievements()" );
}
    

void DummyClient::SubmitHighScore(const VString &leaderboardId, ULONG64 score)
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::SubmitHighScore() '%s',%d", leaderboardId.AsChar(), score );
}

void DummyClient::ShowLeaderboard(const VString &leaderboardId) 
{
   hkvLog::Info( "PACloudConnectionPlugin - DummyClient::ShowLeaderboard() '%s'", leaderboardId.AsChar() );
}
