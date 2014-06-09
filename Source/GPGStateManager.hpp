#ifndef _GPGSTATEMANANGER_HPP_
#define _GPGSTATEMANANGER_HPP_

#if defined(_VISION_ANDROID) || defined(_VISION_IOS)

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

class CCAchievement;

/// \brief
/// Manages the State of Google Play Games for both the Android & iOS Platforms
/// via the gpg::GameServices object
class StateManager 
{
public:

#if defined(_VISION_ANDROID)
   /// \brief 
   /// Called from the developers application to initialise the GPG on Android.
   /// Builds the Google Play Games Platform Configuration and attempts the silent
   /// sign-in to the services.
   /// \param AndroidApplication The android application state
  static void InitServices(struct android_app* AndroidApplication);

#elif defined(_VISION_IOS)     
  /// \brief    
  /// Called from the developers application to initialise the GPG on iOS.   
  /// Builds the Google Play Games Platform Configuration and attempts the silent
  /// sign-in to the services.
  /// \param GPG_CLIENTID The Google Client ID for the game services you wish to connect to
  static void InitServices(const char* GPG_CLIENTID);
#else
#error unsupported platform!!
#endif

  /// \brief initialises the GPG services with the given platform configuration
  static void InitServices( gpg::PlatformConfiguration const &pc );

  /// \brief gets the google game services state object
  static gpg::GameServices *GetGameServices();
  /// \brief gets the google player object for the signed in player (can be null)
  static gpg::Player *GetSignedInPlayer();
  /// \brief starts the UI user sign-in
  static void BeginUserInitiatedSignIn();
  /// \brief signs any currently signed in player out
  static void SignOut();
  /// \brief Fetch and achievement non-blocking
  static void FetchAchievement(const char *achievementId);
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

  /// \note
  /// Converts a Google Play Games C++ Native API Type into a Cloud Connection Plugin Type
  /// /param GPGPType The type to be converted
  /// /return The type as a CCAchievementType
  static unsigned int GPGAchTypeToCCAchType( gpg::AchievementType GPGPType );
  /// \note
  /// Converts a Google Play Games C++ Native API State into a Cloud Connection Plugin State
  /// /param GPGPState The state to be converted
  /// /return The State as a CCAchievementState
  static unsigned int GPGAchStateToCCAchState( gpg::AchievementState GPGPState );

  
  /// \brief callback when the Google Sign-in Authorisation process has finished
  static void OnAuthFinished(gpg::AuthOperation op, gpg::AuthStatus status);
  /// \brief callback when the Google Sign-in Authorisation process has started
  static void OnAuthStarted(gpg::AuthOperation op);
  /// \brief callback when the player manger fetches player data about the signed in player
  static void OnFetchSelf(gpg::PlayerManager::FetchSelfResponse response);
  /// \brief callback when the achievement manger fetches achievement data
  /// \param response Contains data and response status for a single achievement.
  static void OnFetchAchievement(gpg::AchievementManager::FetchResponse response);
  /// \brief returns the AuthStatus as a human readable value
  static const char* AuthStatusToName( gpg::AuthStatus status );

  static bool is_auth_in_progress_;
  static std::unique_ptr<gpg::GameServices> game_services_;
  static std::shared_ptr<gpg::Player> player_;                          ///< the data for the currently-signed in player
  static VMap<std::string, CCAchievement*> m_ccAchievementCache;       ///< cache of all achievements that have been downloaded
};


#endif

#endif
