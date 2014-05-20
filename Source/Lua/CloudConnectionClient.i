%nodefaultctor CloudConnectionClient;
%nodefaultdtor CloudConnectionClient;

/// \brief
/// Defines an abstract interface for a Project Anarchy Cloud Connection Client. 
/// Concrete implementations might be, for example, the Google Play Games Client client for Android or for iOS.
class CloudConnectionClient : public VTypedObject
{
public:
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

  
  //Vision specific extension:
  %extend 
  {
    VSWIG_CREATE_CAST_UNSAFE(CloudConnectionClient)
  }
};