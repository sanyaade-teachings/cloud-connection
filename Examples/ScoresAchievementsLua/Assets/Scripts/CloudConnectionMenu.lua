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
