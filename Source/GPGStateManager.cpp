#if defined(_VISION_ANDROID) || defined(_VISION_IOS)

#include "VisionBaseIncludes.h"
#include "GPGStateManager.hpp"
#include "gpg/android_initialization.h"
#include "gpg/debug.h"
#include "android/Log.h"
#include "CloudConnectionCallbacks.hpp"
#include "gpg/achievement_manager.h"


bool StateManager::is_auth_in_progress_ = false;
std::unique_ptr<gpg::GameServices> StateManager::game_services_;
std::shared_ptr<gpg::Player> StateManager::player_;

gpg::GameServices *StateManager::GetGameServices() {
  return game_services_.get();
}

gpg::Player *StateManager::GetSignedInPlayer() 
{
  return player_.get();
}

void StateManager::BeginUserInitiatedSignIn() {
  if (!game_services_->IsAuthorized()) {
    hkvLog::Debug("StartAuthorizationUI");
    game_services_->StartAuthorizationUI();
  }
}

void StateManager::SignOut() {
  if (game_services_->IsAuthorized()) {
    hkvLog::Debug("SignOut");
    game_services_->SignOut();
    if ( GetSignedInPlayer() != NULL )
    {
      player_ = NULL;
    }
  }
}

void StateManager::IncrementAchievement(const char *achievementId, uint32_t steps) 
{
  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("Achievement Increment Steps");
    game_services_->Achievements().Increment(achievementId, steps);
  }
}

void StateManager::SetAchievementStepsAtLeast(const char *achievementId, uint32_t steps) 
{
  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("Achievement Set Steps");
    game_services_->Achievements().SetStepsAtLeast(achievementId, steps);
  }
}


void StateManager::RevealAchievement(char const *achievement_id) 
{
  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("Achievement revealed");
    game_services_->Achievements().Reveal(achievement_id);
  }
}

void StateManager::UnlockAchievement(char const *achievement_id) 
{
  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("Achievement unlocked");
    game_services_->Achievements().Unlock(achievement_id);
  }
}

void StateManager::SubmitHighScore(char const *leaderboard_id, uint64_t score) 
{
  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("High score submitted");
    game_services_->Leaderboards().SubmitScore(leaderboard_id, score);
  }
}

void StateManager::SubmitHighScore(char const *leaderboard_id, uint64_t score, char const *metadata) 
{
  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("High score submitted with metadata");
    game_services_->Leaderboards().SubmitScore(leaderboard_id, score, metadata);
  }
}

void StateManager::ShowAchievements() {
  if (game_services_->IsAuthorized()) {
    hkvLog::Debug("Show achievement");
    game_services_->Achievements().ShowAllUI();
  }
}

void StateManager::ShowLeaderboard(char const *leaderboard_id) {
  if (game_services_->IsAuthorized()) {
    hkvLog::Debug("Show leaderboard");
    game_services_->Leaderboards().ShowUI(leaderboard_id);
  }
}

void StateManager::ShowLeaderboards() 
{
  if (game_services_->IsAuthorized()) 
  {
    hkvLog::Debug("Show All leaderboards");
    game_services_->Leaderboards().ShowAllUI();
  }
}

void StateManager::InitServices( gpg::PlatformConfiguration const &pc ) 
{
  hkvLog::Debug("Initializing Services");
  if (!game_services_) {
    hkvLog::Debug("Uninitialized services, so creating");
    game_services_ = gpg::GameServices::Builder()
        .SetLogging(gpg::DEFAULT_ON_LOG, gpg::LogLevel::VERBOSE)
        .SetOnAuthActionStarted( OnAuthStarted )
        .SetOnAuthActionFinished( OnAuthFinished )
        .Create(pc);
  }
  hkvLog::Debug("Created");
}

void StateManager::OnAuthStarted(gpg::AuthOperation op)
{
  hkvLog::Debug("Sign in started");
  is_auth_in_progress_ = true;
  CloudConnectionCallbackManager::OnAuthActionStarted.TriggerCallbacks();
}

void StateManager::OnAuthFinished(gpg::AuthOperation op, gpg::AuthStatus status) {
  hkvLog::Debug("Sign in finished with a result of %d", status);
  is_auth_in_progress_ = false;
  CloudConnectionCallbackManager::OnAuthActionFinished.TriggerCallbacks();
  
  hkvLog::Debug("OnAuthActionFinished");
  if (IsSuccess(status)) 
  {
    hkvLog::Debug("CloudConnection - You are logged in!");
  } 
  else 
  {
    hkvLog::Debug("CloudConnection - You are not logged in!");
  }

  const gpg::AchievementManager& pAchievementManager = game_services_->Achievements();
  const gpg::LeaderboardManager& pLeaderboardManager = game_services_->Leaderboards();  
//          const gpg::PlayerManager& playerManger = game_services_->Players();

  hkvLog::Debug("Fetching Self Player nonblocking");
  game_services_->Players().FetchSelf( gpg::DataSource::CACHE_OR_NETWORK, OnFetchSelf );
  hkvLog::Debug("--------------------------------------------------------------");

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
  //if ( IsSuccess(response) )
  {
    gpg::Player player = (gpg::Player)response.data;     

    std::shared_ptr<gpg::Player> p ( new gpg::Player( player ) );
    player_ = p;
    hkvLog::Debug("Player Fetch Self response data (Player Name): %s", player_.get()->Name().c_str() );        
    CloudConnectionCallbackManager::OnPlayerDataFetched.TriggerCallbacks();
  }
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
