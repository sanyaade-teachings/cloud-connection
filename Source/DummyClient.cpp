#include "CloudConnectionPluginPCH.hpp"
#include "DummyClient.hpp"
#include "CloudConnectionCallbacks.hpp"
#include "CloudConnection.hpp"
#include "CCAchievement.hpp"

/** RTTI definitions */
V_IMPLEMENT_DYNAMIC( DummyClient, CloudConnectionClient, &g_CloudConnectionModule );
   
DummyClient::DummyClient()
{
  //create the dummy player
  m_pPlayerName = new VString("Dummy Player");
  m_authenticated = true;

  //create a dummy achievement
  m_pDummyAchievement = new CCAchievement();
  m_pDummyAchievement->SetId( "DUMMY_ID" );
  m_pDummyAchievement->SetValid( true );
  m_pDummyAchievement->SetCurrentSteps( 0 );
  m_pDummyAchievement->SetTotalSteps( 0 );    
  m_pDummyAchievement->SetType( STANDARD );
  m_pDummyAchievement->SetState( UNLOCKED );  
  m_pDummyAchievement->SetLastModified( 0 );
  m_pDummyAchievement->SetName("Dummy Achievement");
  m_pDummyAchievement->SetDescription( "This is not a real achievement, it is a dummy test" );
  
}

DummyClient::~DummyClient()
{
  V_SAFE_DELETE( m_pPlayerName );
  V_SAFE_DELETE( m_pDummyAchievement );
}

bool DummyClient::IsAuthenticated()
{
  return m_authenticated;
}

void DummyClient::SignOut()
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::SignOut()" );
  CloudConnection::Callbacks.OnAuthActionStarted.TriggerCallbacks();
  m_authenticated = false;
  CloudConnection::Callbacks.OnAuthActionFinished.TriggerCallbacks();
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
  //send a valid dummy achievement via the callback
  CloudConnection::Callbacks.OnAchievementFetched.TriggerCallbacks( m_pDummyAchievement );
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
