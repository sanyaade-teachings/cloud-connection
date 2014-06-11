#include "CloudConnectionPluginPCH.hpp"
#include "DummyClient.hpp"
#include "CloudConnectionCallbacks.hpp"
#include "CloudConnection.hpp"

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
  CloudConnection::Callbacks.OnAuthActionStarted.TriggerCallbacks();
  m_authenticated = true;
  CloudConnection::Callbacks.OnAuthActionFinished.TriggerCallbacks();
}


bool DummyClient::IsAuthInProgress()
{
  return false;
}

void DummyClient::GetAchievement(const char* achievementId)
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::GetAchievement() '%s'", achievementId );
  //TODO: dummy client should create a valid dummy achievement and send it on via the callback
  CloudConnection::Callbacks.OnAchievementFetched.TriggerCallbacks();
  hkvLog::Warning("TODO: dummy client should create a valid dummy achievement and send it on via the callback");
}

void DummyClient::IncrementAchievement(const char* achievementId, int steps)
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::IncrementAchievement() '%s', %d", achievementId, steps );
}

void DummyClient::RevealAchievement(const char* achievementId)
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::RevealAchievement() '%s'", achievementId );
}

void DummyClient::SetAchievementStepsAtLeast (const char* achievementId, int steps)
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::SetAchievementStepsAtLeast() '%s', %d", achievementId, steps );
}

void DummyClient::UnlockAchievement(const char* achievementId)
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::UnlockAchievement() '%s'", achievementId );
}

void DummyClient::ShowAchievements()
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::ShowAchievements()" );
}
    

void DummyClient::SubmitScore(const char* leaderboardId, ULONG64 score)
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::SubmitScore() '%s',%d", leaderboardId, score );
}
  
void DummyClient::SubmitScore(const char* leaderboardId, ULONG64 score, const char* metadata)
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::SubmitScore() '%s',%d, '%s'", leaderboardId, score, metadata );
}

void DummyClient::ShowLeaderboard(const char* leaderboardId) 
{
   hkvLog::Info( "PACloudConnectionPlugin - DummyClient::ShowLeaderboard() '%s'", leaderboardId);
}

void DummyClient::ShowLeaderboards()
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::ShowLeaderboards()");
}
