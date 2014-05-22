#ifndef _CLOUDCCONNECTIONCLIENT_HPP_
#define _CLOUDCCONNECTIONCLIENT_HPP_

#include "VisionBaseIncludes.h"
#include "CloudConnectionTypes.h"
#include "CloudConnectionPluginImportExport.h"

class CloudConnectionScriptComponent;

/// \brief
/// Defines an abstract interface for a Project Anarchy Cloud Connection Client. 
/// Concrete implementations might be, for example, the Google Play Games Client client for Android or for iOS.
class CloudConnectionClient : public VisTypedEngineObject_cl, public IVisCallbackHandler_cl 
{
public:
	/** RTTI declarations */
	V_DECLARE_DYNAMIC_DLLEXP(CloudConnectionClient, CLOUDCONNECTIONPLUGIN_IMPEXP);  
    
  /// \brief
  /// Initialse this object, creates any components that need to be attached to it
  virtual void OneTimeInit();
    
  /// \brief
  /// De-Initialse this object, removes any components that are attached to it
  virtual void OneTimeDeInit();
    
  /// \brief IVisCallbackHandler_cl override
  virtual void OnHandleCallback( IVisCallbackDataObject_cl* pData ) HKV_OVERRIDE;

  /// \brief
  /// Adds a script component that will list for callback events about for the Cloud Connection
  void AddScriptCallbackListener( );

  /// \brief
  /// Returns whether or not user is authenticated
  virtual bool IsAuthenticated() = 0;

  /// \brief
  /// Signs user out
  virtual void SignOut() = 0;

  /// \brief
  /// Returns the authenticated user's display name
  virtual const char* GetUserDisplayName() const = 0;

  /// \brief
  /// Brings up a platform-specific user authorization flow. 
  virtual void BeginUserInitiatedSignIn() = 0;    

  /// \brief Is there a sign-in process currently in progress
  /// \return true if an sign-in has started but not yet finished, false otherwise
  virtual bool IsAuthInProgress() = 0;

  /// \brief 
  /// Increments an achievement by the given number of steps.
  virtual void IncrementAchievement(const char* achievementId, int steps) = 0;

  /// \brief 
  /// Reveal a hidden achievement to the currently signed-in player.
  virtual void RevealAchievement(const char* achievementId) = 0;

  /// \brief
  /// Set an achievement to have at least the given number of steps completed. 
  virtual void SetAchievementStepsAtLeast (const char* achievementId, int steps) = 0;

  /// \brief
  /// Unlock an achievement for the currently signed in player. 
  virtual void UnlockAchievement(const char* achievementId) = 0;

  /// \brief
  /// Presents a UI to the user that displays information about all achievements. 
  virtual void ShowAchievements() = 0;
    
  /// \brief
  /// Submit a score to the leaderboard for the currently signed-in player. 
  virtual void SubmitHighScore(const char* leaderboardId, ULONG64 score) = 0;

  /// \brief
  /// Submit a score to the leaderboard for the currently signed-in player with metadata (such as something the player did to earn the score).
  virtual void SubmitHighScore(const char* leaderboardId, ULONG64 score, const char* metadata) = 0;

  /// \brief
  /// Presents a UI to the user that displays information about a specific leaderboard. 
  virtual void ShowLeaderboard(const char* leaderboardId)  = 0;

  /// \brief
  /// Presents a UI to the user that displays information about all leaderboards.
  virtual void ShowLeaderboards() = 0;

protected:
private:
};

#endif