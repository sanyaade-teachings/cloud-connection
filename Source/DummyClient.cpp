#include "CloudConnectionPluginPCH.hpp"
#include "DummyClient.hpp"
#include "CloudConnectionCallbacks.hpp"

/** RTTI definitions */
V_IMPLEMENT_DYNAMIC( DummyClient, CloudConnectionClient, &g_CloudConnectionModule );
   
DummyClient::DummyClient()
{
  m_pPlayerName = new VString("Dummy Player");
  m_authenticated = true;
}

DummyClient::~DummyClient()
{
  V_SAFE_DELETE( m_pPlayerName );
}

bool DummyClient::IsAuthenticated()
{
  return m_authenticated;
}

void DummyClient::SignOut()
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::SignOut()" );
  m_authenticated = false;
}

const char* DummyClient::GetUserDisplayName() const
{
  return (*m_pPlayerName);
}


void DummyClient::BeginUserInitiatedSignIn() 
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::BeginUserInitiatedSignIn()" );
  CloudConnectionCallbackManager::OnAuthActionStarted.TriggerCallbacks();
  m_authenticated = true;
  CloudConnectionCallbackManager::OnAuthActionFinished.TriggerCallbacks();
}


bool DummyClient::IsAuthInProgress()
{
  return false;
}

void DummyClient::UnlockAchievement(const char* achievementId)
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::UnlockAchievement() '%s'", achievementId );
}

void DummyClient::ShowAchievements()
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::ShowAchievements()" );
}
    

void DummyClient::SubmitHighScore(const char* leaderboardId, ULONG64 score)
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::SubmitHighScore() '%s',%d", leaderboardId, score );
}

void DummyClient::ShowLeaderboard(const char* leaderboardId) 
{
   hkvLog::Info( "PACloudConnectionPlugin - DummyClient::ShowLeaderboard() '%s'", leaderboardId);
}
