#include "CloudConnectionPluginPCH.hpp"

#if defined(_VISION_ANDROID) || defined(_VISION_IOS)

#if defined(_VISION_ANDROID)
#include "gpg/android_initialization.h"
#include "android/Log.h"
#endif

#include "VisionBaseIncludes.h"
#include "CloudConnectionBase.h"


bool StateManager::is_auth_in_progress_ = false;
std::unique_ptr<gpg::GameServices> StateManager::game_services_;
std::shared_ptr<gpg::Player> StateManager::player_;
VMap<std::string, CCAchievement*> StateManager::m_ccAchievementCache;

gpg::GameServices *StateManager::GetGameServices() 
{
  return game_services_.get();
}

gpg::Player *StateManager::GetSignedInPlayer() 
{  
  return player_.get();
}

void StateManager::BeginUserInitiatedSignIn() 
{
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  if (!game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("StartAuthorizationUI");
    game_services_->StartAuthorizationUI();
  }
}

void StateManager::SignOut() {
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("SignOut");
    game_services_->SignOut();
    if ( GetSignedInPlayer() != NULL )
    {
      player_ = NULL;
    }
  }
}

void StateManager::FetchAchievement(const char *achievementId)
{
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("FetchAchievement");               
    game_services_->Achievements().Fetch(
      gpg::DataSource::CACHE_OR_NETWORK, 
      achievementId,
      OnFetchAchievement);
  }
}

void StateManager::IncrementAchievement(const char *achievementId, uint32_t steps) 
{
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("Achievement Increment Steps");
    game_services_->Achievements().Increment(achievementId, steps);
  }
}

void StateManager::SetAchievementStepsAtLeast(const char *achievementId, uint32_t steps) 
{
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("Achievement Set Steps");
    game_services_->Achievements().SetStepsAtLeast(achievementId, steps);
  }
}


void StateManager::RevealAchievement(char const *achievement_id) 
{
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("Achievement revealed");
    game_services_->Achievements().Reveal(achievement_id);
  }
}

void StateManager::UnlockAchievement(char const *achievement_id) 
{
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("Achievement unlocked");
    game_services_->Achievements().Unlock(achievement_id);
  }
}

void StateManager::SubmitHighScore(char const *leaderboard_id, uint64_t score) 
{
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("High score submitted");
    game_services_->Leaderboards().SubmitScore(leaderboard_id, score);
  }
}

void StateManager::SubmitHighScore(char const *leaderboard_id, uint64_t score, char const *metadata) 
{
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("High score submitted with metadata");
    game_services_->Leaderboards().SubmitScore(leaderboard_id, score, metadata);
  }
}

void StateManager::ShowAchievements() 
{
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("Show achievement");
    game_services_->Achievements().ShowAllUI();
  }
}

void StateManager::ShowLeaderboard(char const *leaderboard_id) 
{
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("Show leaderboard");
    game_services_->Leaderboards().ShowUI(leaderboard_id);
  }
}

void StateManager::ShowLeaderboards() 
{
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("Show All leaderboards");
    game_services_->Leaderboards().ShowAllUI();
  }
}

void StateManager::InitServices( gpg::PlatformConfiguration const &pc ) 
{
  hkvLog::Debug("Initializing Google Play Games Services");
  if (!game_services_) 
  {
    hkvLog::Debug("Uninitialized Google Play Games services, so creating");
    game_services_ = gpg::GameServices::Builder()
        .SetLogging(gpg::DEFAULT_ON_LOG, gpg::LogLevel::VERBOSE)
        .SetOnAuthActionStarted( OnAuthStarted )
        .SetOnAuthActionFinished( OnAuthFinished )
        .Create(pc);
  }
  hkvLog::Debug("Created Google Play Games Services");
}

void StateManager::OnAuthStarted(gpg::AuthOperation op)
{
  hkvLog::Debug("Sign in started");
  is_auth_in_progress_ = true;
  CloudConnection::Callbacks.OnAuthActionStarted.TriggerCallbacks();
}

void StateManager::OnAuthFinished(gpg::AuthOperation op, gpg::AuthStatus status) 
{
  VASSERT_MSG( game_services_ != NULL, "The Google Play Game Services have not been initialised" );

  hkvLog::Debug("Sign in finished with a result of %d, %s", status, AuthStatusToName(status) );
  is_auth_in_progress_ = false;
  CloudConnection::Callbacks.OnAuthActionFinished.TriggerCallbacks();
  
  hkvLog::Debug("OnAuthActionFinished");
  if (IsSuccess(status)) 
  {
    hkvLog::Debug("CloudConnection - You are logged in!");
    // fetch the data for the signed in player
    hkvLog::Debug("Fetching Self Player nonblocking");
    game_services_->Players().FetchSelf( gpg::DataSource::CACHE_OR_NETWORK, OnFetchSelf );
  } 
  else 
  {
    hkvLog::Debug("CloudConnection - You are not logged in!");
    player_ = nullptr;    //remove current player if there is one
  }

  const gpg::AchievementManager& pAchievementManager = game_services_->Achievements();
  const gpg::LeaderboardManager& pLeaderboardManager = game_services_->Leaderboards();  
//          const gpg::PlayerManager& playerManger = game_services_->Players();

  /*
  LOGI("Fetching all blocking");
  gpg::AchievementManager::FetchAllResponse fetchResponse = game_services_->Achievements().FetchAllBlocking(std::chrono::milliseconds(1000));
  LOGI("--------------------------------------------------------------");

  LOGI("Fetching all nonblocking");
  game_services_->Achievements().FetchAll(gpg::DataSource::CACHE_OR_NETWORK, [] (gpg::AchievementManager::FetchAllResponse response) {LOGI("Achievement response status: %d", response.status);});
  LOGI("--------------------------------------------------------------");
  */
}

void StateManager::OnFetchSelf(gpg::PlayerManager::FetchSelfResponse response)
{       
  hkvLog::Debug("Player Fetch Self response status: %d", response.status);
  if ( response.status == gpg::ResponseStatus::VALID )
  {
    gpg::Player player = (gpg::Player)response.data;     

    std::shared_ptr<gpg::Player> p ( new gpg::Player( player ) );
    player_ = p;
    hkvLog::Debug("Player Fetch Self response data (Player Name): %s", player_.get()->Name().c_str() );        
    CloudConnection::Callbacks.OnPlayerDataFetched.TriggerCallbacks();
  }
}

void StateManager::OnFetchAchievement(gpg::AchievementManager::FetchResponse response) 
{
  hkvLog::Debug("StateManager::OnFetchAchievement - Achievement response status: %d", response.status);
  if ( response.status == gpg::ResponseStatus::VALID )
  {
    //find the mathing CCAchievemnet in our map or create a new one if it doesn't exits yet
    gpg::Achievement gpgAch = response.data;
    CCAchievement* pCcAch;
    bool found = m_ccAchievementCache.Lookup( gpgAch.Id(), pCcAch );
    if ( !found )
    {
      pCcAch = new CCAchievement();            
      m_ccAchievementCache.SetAt( gpgAch.Id(), pCcAch ); 
    }

    VASSERT_MSG( pCcAch != NULL, "The CCAchievement has not been found or created, it cannot be null" );
          
    //populate pCcAch with data from response if it is valid
    pCcAch->SetValid( gpgAch.Valid() );
    if ( gpgAch.Valid() == true )
    {
      pCcAch->SetId( gpgAch.Id().c_str() );
      pCcAch->SetName( gpgAch.Name().c_str() );
      pCcAch->SetDescription( gpgAch.Description().c_str() );
      pCcAch->SetType( GPGAchTypeToCCAchType( gpgAch.Type() ) );
      pCcAch->SetState( GPGAchStateToCCAchState( gpgAch.State() ) );
      pCcAch->SetCurrentSteps( gpgAch.CurrentSteps() );
      pCcAch->SetTotalSteps( gpgAch.TotalSteps() );
      pCcAch->SetLastModified( gpgAch.LastModified().count() );
    }

    //Send the data onto the callback
    hkvLog::Debug("CloudConnectionCallbackManager::OnAchievementFetched.TriggerCallbacks( pCcAch );");
    CloudConnection::Callbacks.OnAchievementFetched.TriggerCallbacks( pCcAch );
  }
}
 
unsigned int StateManager::GPGAchTypeToCCAchType( gpg::AchievementType GPGPType )
{
  unsigned int cctype = 0;
  switch( GPGPType )
  {
  case gpg::AchievementType::STANDARD:
    cctype = CCAchievementType::STANDARD;
    break;
  case gpg::AchievementType::INCREMENTAL:
    cctype = CCAchievementType::INCREMENTAL;
    break;
  default:
    hkvLog::Warning(" GPGAchTypeToCCAchType - the type conversion was not handled");
  }
  return cctype;
}

/// \note
/// Converts a Google Play Games C++ Native API State into a Cloud Connection Plugin State
/// /param GPGPState The state to be converted
/// /return The State as a CCAchievementState
unsigned int StateManager::GPGAchStateToCCAchState( gpg::AchievementState GPGPState )
{
  unsigned int ccstate = 0;
  switch( GPGPState )
  {
  case gpg::AchievementState::HIDDEN:
    ccstate = CCAchievementState::HIDDEN;
    break;
  case gpg::AchievementState::REVEALED:
    ccstate = CCAchievementState::REVEALED;
    break;
  case gpg::AchievementState::UNLOCKED:
    ccstate = CCAchievementState::UNLOCKED;
    break;
  default:
    hkvLog::Warning(" GPGAchStateToCCAchState - the state conversion was not handled");
  }
  return ccstate;
}

/// \brief returns the AuthStatus as a human readable value
const char* StateManager::AuthStatusToName( gpg::AuthStatus status )
{
  if ( status == gpg::AuthStatus::VALID )
  {
    return "VALID";
  }
  else if ( status == gpg::AuthStatus::ERROR_INTERNAL )
  {
    return "ERROR_INTERNAL";
  }
  else if ( status == gpg::AuthStatus:: ERROR_NOT_AUTHORIZED  )
  {
    return "ERROR_NOT_AUTHORIZED";
  }
  else if ( status == gpg::AuthStatus:: ERROR_VERSION_UPDATE_REQUIRED )
  {
    return "ERROR_VERSION_UPDATE_REQUIRED";
  }
  else if ( status == gpg::AuthStatus:: ERROR_TIMEOUT )
  {
    return "ERROR_TIMEOUT";
  }  

  return "UNKNOWN_ERROR";
}

#if defined(_VISION_ANDROID)
// Android specific initialisation method
void StateManager::InitServices(struct android_app* AndroidApplication)
{
  VASSERT_MSG(AndroidApplication != NULL, "The android_app* cannot be null");

  // gpg-cpp: Set platform intiialization
  gpg::AndroidInitialization::android_main(AndroidApplication);

  // gpg-cpp:  We need to check to see if there's a previous state.
  // If there was, we'll just continue, but if not we'll set up
  // gpg-cpp for the first time.
  if (AndroidApplication->savedState == NULL) 
  {
    // We are not starting with a previous saved state so set up the GPG service
    hkvLog::Debug("Android Setting up gpg-cpp");

    // Get the platform configuration.
    gpg::AndroidPlatformConfiguration platform_configuration;
    platform_configuration.SetActivity(AndroidApplication->activity->clazz);

    hkvLog::Debug("SetActivity finished gpg-cpp");

    // Now, create the game service
    StateManager::InitServices(platform_configuration);
    
    hkvLog::Debug("Android InitServices finished gpg-cpp");
  }
}
#elif defined(_VISION_IOS)
// iOS specific initialisation method
void StateManager::InitServices(const char* GPG_CLIENTID)
{
    hkvLog::Debug("iOS Setting up gpg-cpp");

    // Get the platform configuration.        
    gpg::IosPlatformConfiguration platform_configuration;
    platform_configuration.SetClientID(std::string(GPG_CLIENTID));

    // Now, create the game service
    StateManager::InitServices(platform_configuration);
    
    hkvLog::Debug("iOS InitServices finished gpg-cpp");
}
#else
#error unsupported platform
#endif  //end platform initialisation methods


#endif  // end defined(_VISION_ANDROID) || defined(_VISION_IOS)
