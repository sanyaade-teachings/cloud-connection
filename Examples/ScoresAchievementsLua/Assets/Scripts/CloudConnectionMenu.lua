-- This Script file processes the actions for a GUI that demonstrate Google Play Games basic functions
-- Signin/out, show highscore, show achievements, submit a high score, unlocking an achievement
-- See MainMenu.xml for the definition of the menu items
-- For tutorial on how to use the GUI system in lua then please see http://www.projectanarchy.com/guis-lua

--this is the ID of the achievement that this demo unlocks
--get this from the google developer console when you create your achievements
local ACHIEVEMENT_ID = "CggI9__cunsQAhAB"     

--this is the ID of the leaderboard that this demo will submit a score to
--get this from the google developer console when you create your leaderboard
local LEADERBOARD_ID = "CggI9__cunsQAhAC" 

function OnAfterSceneLoaded()           
  -- Enable debug output in the log file so we can see that callbacks are working
  Debug:Enable(true)
     
  -- test that we can get an acheivement via 'OnAchievementFetched' callback
  local ccClient = CloudConnection:GetClient()  
  ccClient:GetAchievement( ACHIEVEMENT_ID )
     
end

-- called when an item in the menu is clicked
function OnItemClicked(self, uiItem, buttons, mousePosX, mousePosY)
  Debug:Log("An item on the menu was clicked")

  -- get the cloud connection client
  local ccClient = CloudConnection:GetClient()
        
  -- action the button that was pressed
  if uiItem:GetID() == GUI:GetID("SIGNIN") then  
    ccClient:BeginUserInitiatedSignIn()               -- show the user sign-in dialog
  elseif uiItem:GetID() == GUI:GetID("SIGNOUT") then  
    ccClient:SignOut()                                -- signs the user out    
  elseif uiItem:GetID() == GUI:GetID("ALLACH") then      
    ccClient:ShowAchievements()                       -- show the UI for all achievements for the signed in player
  elseif uiItem:GetID() == GUI:GetID("UNLOCKACH") then      
    ccClient:UnlockAchievement( ACHIEVEMENT_ID )      -- unlocks an achievements for the signed in player
  elseif uiItem:GetID() == GUI:GetID("ALLLEAD") then  
    ccClient:ShowLeaderboards()                       -- shows the UI for all leaderboards for the signed in player
  elseif uiItem:GetID() == GUI:GetID("SUBMITSCORE") then  
    -- submits a high score to a leaderboard
    local highScore = 12346;      
    ccClient:SubmitScore( LEADERBOARD_ID, highScore )    
  end
  
end


--This callback is made to the script when the Cloud Connection
--Client has started the authorisation process
function OnAuthActionStarted()
  Debug:Log("OnAuthActionStarted callback was successfully made to Lua script")
end

--This callback is made to the script when the Cloud Connection
--Client has finsihed the authorisation process, either succesfully or unsucesfully
--this call can also be the result of a sign-out as well as a sign-in attempt
function OnAuthActionFinished()
  Debug:Log("OnAuthActionFinished callback was successfully made to Lua script")
    
  local ccClient = CloudConnection:GetClient()
  
  -- check the authentication
  if ccClient:IsAuthenticated() then
    Debug:Log("The user is now authenticated" )
  else
    Debug:Log("The user no longer authenticated" )
  end
end

--This callback is made to the script when the Cloud Connection
--Client has retrived the player data, this means that calls
--to GetUserDisplayName() will now return a valid value
function OnPlayerDataFetched()
  Debug:Log("OnPlayerDataFetched callback was successfully made to Lua script")
      
  local ccClient = CloudConnection:GetClient()
  
  -- check the users display name now we know it is available
  if ccClient:isAuthenticated() then
    local displayName = ccClient:GetUserDisplayName()    
    Debug:Log("The users Display Name is '" .. displayName .. "'" )    
  end
end

--This callback is made to the script when the Cloud Connection
--Client has retrived achievement data via the GetAchievement( id ) call
function OnAchievementFetched( id, name, description, achtype, achstate, totalsteps, currentsteps )
  Debug:Log("OnAchievementFetched callback was successfully made to Lua script")
  Debug:Log("ID=")
  Debug:Log(id)
  Debug:Log(name)
  Debug:Log(description)
  Debug:Log(achtype)
  Debug:Log(achstate)
  Debug:Log(totalsteps)
  Debug:Log(currentsteps)
end