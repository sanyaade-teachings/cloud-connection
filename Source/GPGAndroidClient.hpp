#ifndef _GPGANDROIDCLIENT_HPP_
#define _GPGANDROIDCLIENT_HPP_
#if defined(_VISION_ANDROID)

#include "VisionBaseIncludes.h"
#include "CloudConnectionClient.hpp"

/// \brief
/// Defines an concrete implementation for for a Project Anarchy Cloud Connection Client.
/// Provides the Google Play Games Android Client
class GPGAndroidClient : public CloudConnectionClient
{
public:    
  /** RTTI declarations */
	V_DECLARE_DYNAMIC_DLLEXP(GPGAndroidClient, CLOUDCONNECTIONPLUGIN_IMPEXP);

  GPGAndroidClient();
  ~GPGAndroidClient();

  /// \brief
  /// Returns whether or not user is authenticated
  virtual bool IsAuthenticated() HKV_OVERRIDE;

  /// \brief
  /// Signs out
  virtual void SignOut() HKV_OVERRIDE;

  /// \brief
  /// Returns the authenticated user's display name
  virtual const char* GetUserDisplayName() const HKV_OVERRIDE;

  /// \brief
  /// Brings up a platform-specific user authorization flow. 
  virtual void BeginUserInitiatedSignIn() HKV_OVERRIDE;    

  /// \brief Is there a sign-in process currently in progress
  /// \return true if an sign-in has started but not yet finished, false otherwise
  virtual bool IsAuthInProgress() HKV_OVERRIDE;

  /// \brief
  /// Unlock an achievement for the currently signed in player. 
  virtual void UnlockAchievement(const char* achievementId) HKV_OVERRIDE;

  /// \brief
  /// Presents a UI to the user that displays information about all achievements. 
  virtual void ShowAchievements() HKV_OVERRIDE;
    
  /// \brief
  /// Submit a score to the leaderboard for the currently signed-in player. 
  virtual void SubmitHighScore(const char* leaderboardId, ULONG64 score) HKV_OVERRIDE;

  /// \brief
  /// Presents a UI to the user that displays information about a specific leaderboard. 
  virtual void ShowLeaderboard(const char* leaderboardId) HKV_OVERRIDE;

protected:
private:
  VString* m_pPlayerName; ///< TEMP DUMMY VALUE
};

#endif
#endif
