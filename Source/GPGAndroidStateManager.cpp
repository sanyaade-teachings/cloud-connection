#if defined(_VISION_ANDROID)

#include "VisionBaseIncludes.h"
#include "GPGAndroidStateManager.hpp"
#include "gpg/android_initialization.h"
#include "gpg/debug.h"
#include "android/Log.h"
#define DEBUG_TAG "PACloudConnectionNativeActivity"
#define LOGI(...) \
    ((void)__android_log_print(ANDROID_LOG_INFO, DEBUG_TAG, __VA_ARGS__))



#include "gpg/achievement_manager.h"
bool StateManager::is_auth_in_progress_ = false;
std::unique_ptr<gpg::GameServices> StateManager::game_services_;

void OnAuthActionFinished(gpg::AuthOperation op, gpg::AuthStatus status) {
  LOGI("OnAuthActionFinished");
}

void OnAuthActionStarted(gpg::AuthOperation op) {
  LOGI("OnAuthActionStarted");
  switch ( op ) {
  case gpg::AuthOperation::SIGN_IN:
    LOGI("Signing In");
    break;
  case gpg::AuthOperation::SIGN_OUT:
    LOGI("Signing Out");
    break;
  }
}

gpg::GameServices *StateManager::GetGameServices() {
  return game_services_.get();
}

void StateManager::BeginUserInitiatedSignIn() {
  if (!game_services_->IsAuthorized()) {
    LOGI("StartAuthorizationUI");
    game_services_->StartAuthorizationUI();
  }
}

void StateManager::SignOut() {
  if (game_services_->IsAuthorized()) {
    LOGI("SignOut");
    game_services_->SignOut();
  }
}

void StateManager::UnlockAchievement(char const *achievement_id) {
  if (game_services_->IsAuthorized()) {
    LOGI("Achievement unlocked");
    game_services_->Achievements().Unlock(achievement_id);
  }
}

void StateManager::SubmitHighScore(char const *leaderboard_id, uint64_t score) {
  if (game_services_->IsAuthorized()) {
    LOGI("High score submitted");
    game_services_->Leaderboards().SubmitScore(leaderboard_id, score);
  }
}

void StateManager::ShowAchievements() {
  if (game_services_->IsAuthorized()) {
    LOGI("Show achievement");
    game_services_->Achievements().ShowAllUI();
  }
}

void StateManager::ShowLeaderboard(char const *leaderboard_id) {
  if (game_services_->IsAuthorized()) {
    LOGI("Show achievement");
    game_services_->Leaderboards().ShowUI(leaderboard_id);
  }
}


void StateManager::InitServices(
    gpg::PlatformConfiguration const &pc,
    gpg::GameServices::Builder::OnAuthActionStartedCallback started_callback,
    gpg::GameServices::Builder::OnAuthActionFinishedCallback
        finished_callback) {
  LOGI("Initializing Services");
  if (!game_services_) {
    LOGI("Uninitialized services, so creating");
    game_services_ = gpg::GameServices::Builder()
        .SetLogging(gpg::DEFAULT_ON_LOG, gpg::LogLevel::VERBOSE)
        .SetOnAuthActionStarted([started_callback](gpg::AuthOperation op) {
          LOGI("Sign in started");
          is_auth_in_progress_ = true;
          started_callback(op);
        })
        .SetOnAuthActionFinished([finished_callback](gpg::AuthOperation op,
                                                     gpg::AuthStatus status) {
          LOGI("Sign in finished with a result of %d", status);
          is_auth_in_progress_ = false;
          finished_callback(op, status);

          const gpg::AchievementManager& pAchievementManager = game_services_->Achievements();
          const gpg::LeaderboardManager& pLeaderboardManager = game_services_->Leaderboards();
          LOGI("Fetching Self Player nonblocking");
//          const gpg::PlayerManager& playerManger = game_services_->Players();
          game_services_->Players().FetchSelf(
            gpg::DataSource::CACHE_OR_NETWORK, 
            [] (gpg::PlayerManager::FetchSelfResponse response) { 
              gpg::Player player = (gpg::Player)response.data;
              LOGI("Player Fetch Self response data (Player Name): %s", player.Name().c_str() ); 
              LOGI("Player Fetch Self response status: %d", response.status);});
          LOGI("--------------------------------------------------------------");

          LOGI("Fetching all blocking");
          gpg::AchievementManager::FetchAllResponse fetchResponse = game_services_->Achievements().FetchAllBlocking(std::chrono::milliseconds(1000));
          LOGI("--------------------------------------------------------------");

          LOGI("Fetching all nonblocking");
          game_services_->Achievements().FetchAll(gpg::DataSource::CACHE_OR_NETWORK, [] (gpg::AchievementManager::FetchAllResponse response) {LOGI("Achievement response status: %d", response.status);});
          LOGI("--------------------------------------------------------------");

        })
        .Create(pc);
  }
  LOGI("Created");
}


void StateManager::InitServices(struct android_app* AndroidApplication)
{
  VASSERT_MSG(AndroidApplication != NULL, "The android_app* cannot be null");

  // gpg-cpp: Set platform intiialization
  gpg::AndroidInitialization::android_main(AndroidApplication);

  // gpg-cpp:  Here we create the callback on auth operations
  auto callback = [&](gpg::AuthOperation op, gpg::AuthStatus status) {
    hkvLog::Debug("OnAuthActionFinished");
    if (IsSuccess(status)) {
      hkvLog::Debug("Cloud Connection - You are logged in!");
    } else {
      hkvLog::Debug("Cloud Connection - You are not logged in!");
    }
  };

  // gpg-cpp:  We need to check to see if there's a previous state.
  // If there was, we'll just continue, but if not we'll set up
  // gpg-cpp for the first time.
  if (AndroidApplication->savedState != NULL) {
    // We are starting with a previous saved state; restore from it.
    //engine.state = *(struct saved_state*)AndroidApplication->savedState;
  } else {
    hkvLog::Debug("Setting up gpg-cpp");

    // Get the platform configuration.
    gpg::AndroidPlatformConfiguration platform_configuration;
    platform_configuration.SetActivity(AndroidApplication->activity->clazz);

    hkvLog::Debug("SetActivity finished gpg-cpp");

    // Now, create the game service (see StateManager.cpp)
    // and pass in our callback
    StateManager::InitServices(platform_configuration, NULL, callback );
    
    hkvLog::Debug("InitServices finished gpg-cpp");
  }
}
#endif
