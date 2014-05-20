#ifndef _GPGANDROIDSTATEMANANGER_HPP_
#define _GPGANDROIDSTATEMANANGER_HPP_

#if defined(_VISION_ANDROID)

#include "gpg/achievement.h"
#include "gpg/achievement_manager.h"
#include "gpg/builder.h"
#include "gpg/debug.h"
#include "gpg/default_callbacks.h"
#include "gpg/game_services.h"
#include "gpg/leaderboard.h"
#include "gpg/leaderboard_manager.h"
#include "gpg/platform_configuration.h"
#include "gpg/player_manager.h"
#include "gpg/score_page.h"
#include "gpg/types.h"

/// \brief
/// Manages the State of Google Play Games for the Android Platform
/// in the gpg::GameServices object
class StateManager 
{
 public:

   /// \brief 
   /// Called from the developers application to initialise the GPG on Android.
   /// Builds the Google Play Games Platform Configuration and attempts the silent
   /// sign-in to the services.
  static void InitServices(struct android_app* AndroidApplication);

  /// \brief initialises the GPG services
  static void InitServices( gpg::PlatformConfiguration const &pc );

  /// \brief gets the google game services state object
  static gpg::GameServices *GetGameServices();
  /// \brief gets the google player object for the signed in player (can be null)
  static gpg::Player *GetSignedInPlayer();
  /// \brief starts the UI user sign-in
  static void BeginUserInitiatedSignIn();
  /// \brief signs any currently signed in player out
  static void SignOut();
  /// \brief Increments an achievement by the given number of steps. 
  static void IncrementAchievement(const char *achievementId, uint32_t steps);
  /// \brief Set an achievement to have at least the given number of steps completed. 
  static void SetAchievementStepsAtLeast(const char *achievementId, uint32_t steps);
  /// \brief Reveal a hidden achievement to the currently signed-in player
  static void RevealAchievement(const char *achievementId);
  /// \brief unlocks the achievement with the given Id for the currently signed-in player
  static void UnlockAchievement(const char *achievementId);
  /// \brief submits a highscore to the leaderboard with the given Id for the currently signed-in player
  static void SubmitHighScore(const char *leaderboardId, uint64_t score);
  /// \brief submits a highscore to the leaderboard with the given Id for the currently signed-in player, with meta-data
  static void SubmitHighScore(const char *leaderboardId, uint64_t score, const char *metadata);
  /// \brief brings up the Achievements UI
  static void ShowAchievements();
  /// \brief brings up the leaderboards UI for the leaderboard of given Id
  static void ShowLeaderboard(const char *leaderboardId);
  /// \brief brings up the leaderboards UI for all leaderboards
  static void ShowLeaderboards();
  /// \brief returns true if the sign-in has been started but has not yet completed, false otherwise
  static bool IsAuthInProgress() 
  {
    return is_auth_in_progress_;
  }

 private:
  
  /// \brief callback when the Google Sign-in Authorisation process has finished
  static void OnAuthFinished(gpg::AuthOperation op, gpg::AuthStatus status);
  /// \brief callback when the Google Sign-in Authorisation process has started
  static void OnAuthStarted(gpg::AuthOperation op);
  /// \brief callback when the player manger fetches player data about the signed in player
  static void OnFetchSelf(gpg::PlayerManager::FetchSelfResponse response);

  static bool is_auth_in_progress_;
  static std::unique_ptr<gpg::GameServices> game_services_;
  static std::shared_ptr<gpg::Player> player_;              ///< the data for the currently-signed in player
};


#endif

#endif
