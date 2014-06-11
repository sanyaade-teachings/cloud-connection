%nodefaultctor CloudConnectionClient;
%nodefaultdtor CloudConnectionClient;

/// \brief
/// Defines an abstract interface for a Project Anarchy Cloud Connection Client. 
/// Concrete implementations might be, for example, the Google Play Games Client client for Android or for iOS.
class CloudConnectionClient : public VisTypedEngineObject_cl
{
public:

  /// \brief
  /// Adds a script component that will list for callback events about for the Cloud Connection
  /// \param pInstance The instance of the Lua script that will listen for callbacks
  void AddScriptCallbackListener( VScriptInstance* pInstance );
  
  /// \brief
  /// Removes a script component that that was listening for callback events for the Cloud Connection
  /// The script can define and listen for callbacks inside the following script functions
  void RemoveScriptCallbackListener( VScriptInstance* pInstance );

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
    
  // \brief gets a specific achievement, the achievement is returned when ready via a callback    
  virtual void GetAchievement(const char* achievementId) = 0;
  
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
  virtual void SubmitScore(const char* leaderboardId, ULONG64 score) = 0;

  /// \brief
  /// Submit a score to the leaderboard for the currently signed-in player with metadata (such as something the player did to earn the score).
  virtual void SubmitScore(const char* leaderboardId, ULONG64 score, const char* metadata) = 0;

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


%extend CloudConnectionClient
{      
	/// \brief
	/// add callbacks to the currently executing script
	void AddScriptCallbackListener(VCaptureSwigEnvironment* env)
	{
		lua_State* L = env->GetLuaState();

		//Find out which script instance we are calling this from
		VScriptInstance*  pScript = VScriptResourceManager::GetScriptInstanceForState(L);
		VASSERT_MSG(pScript != NULL, "The script instance to be added cannot be null");
      
		$self->AddScriptCallbackListener(pScript);
    
		env->SetNumReturnValues(lua_yield(L, 0));
	}
  
  /// \brief
	/// removes callbacks to the currently executing script
	void RemoveScriptCallbackListener(VCaptureSwigEnvironment* env)
	{
		lua_State* L = env->GetLuaState();

		//Find out which script instance we are calling this from
		VScriptInstance*  pScript = VScriptResourceManager::GetScriptInstanceForState(L);
		VASSERT_MSG(pScript != NULL, "The script instance to be removed cannot be null");
      
		$self->RemoveScriptCallbackListener(pScript);
    
		env->SetNumReturnValues(lua_yield(L, 0));
	}
}