#ifndef _CLOUDCCONNECTIONCLIENT_HPP_
#define _CLOUDCCONNECTIONCLIENT_HPP_

#include "VisionBaseIncludes.h"
#include "CloudConnectionTypes.h"
#include "CloudConnectionPluginImportExport.h"

/// \brief
/// Defines an abstract interface for a Project Anarchy Cloud Connection Client. 
/// Concrete implementations might be, for example, the Google Play Games Client client for Android or for iOS.
class CloudConnectionClient : public VTypedObject
{
public:
	/** RTTI declarations */
	V_DECLARE_DYNAMIC_DLLEXP(CloudConnectionClient, CLOUDCONNECTIONPLUGIN_IMPEXP);  

  /// \brief
  /// Returns whether or not user is authenticated
  virtual bool IsAuthenticated() = 0;

  /// \brief
  /// Signs user out
  virtual void SignOut() = 0;

  /// \brief
  /// Returns the authenticated user's display name
  virtual VString GetUserDisplayName() = 0;

  /// \brief
  /// Brings up a platform-specific user authorization flow. 
  virtual void BeginUserInitiatedSignIn() = 0;    

  /// \brief Is there a sign-in process currently in progress
  /// \return true if an sign-in has started but not yet finished, false otherwise
  virtual bool IsAuthInProgress() = 0;

  /// \brief
  /// Unlock an achievement for the currently signed in player. 
  virtual void UnlockAchievement(const VString &achievementId) = 0;

  /// \brief
  /// Presents a UI to the user that displays information about all achievements. 
  virtual void ShowAchievements() = 0;
    
  /// \brief
  /// Submit a score to the leaderboard for the currently signed-in player. 
  virtual void SubmitHighScore(const VString &leaderboardId, ULONG64 score) = 0;

  /// \brief
  /// Presents a UI to the user that displays information about a specific leaderboard. 
  virtual void ShowLeaderboard(const VString &leaderboardId)  = 0;

protected:
private:
};

#endif