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


-- called when an item in the menu is clicked
function OnItemClicked(self, uiItem, buttons, mousePosX, mousePosY)
  -- get the cloud connection client
  local ccClient = CloudConnection:GetClient()

  -- action the button that was pressed
  if uiItem:GetID() == GUI:GetID("SIGNIN") then  
    -- show the user sign-in dialog
    ccClient:BeginUserInitiatedSignIn() 
    
  elseif uiItem:GetID() == GUI:GetID("SIGNOUT") then  
    -- signs the user out
    ccClient:SignOut()
    
  elseif uiItem:GetID() == GUI:GetID("ALLACH") then  
    -- show the UI for all achievements for the signed in player
    ccClient:ShowAchievements()
    
  elseif uiItem:GetID() == GUI:GetID("UNLOCKACH") then  
    -- unlocks an achievements for the signed in player
    ccClient:UnlockAchievement( ACHIEVEMENT_ID )
    
  elseif uiItem:GetID() == GUI:GetID("ALLLEAD") then  
    -- shows the UI for all leaderboards for the signed in player
    ccClient:ShowLeaderboards()
    
  elseif uiItem:GetID() == GUI:GetID("SUBMITSCORE") then  
    -- submits a high score to a leaderboard
    local highScore = 12346;      
    ccClient:SubmitHighScore( LEADERBOARD_ID, highScore )
    
  end
  
end

function AuthenticationChanged()

  if G.basicGUI ~= nil then
    --Get the instance of the cloud connection client
    local ccClient = CloudConnection:GetClient()
    local isAutenticated = ccClient:IsAuthenticated()

    SetButtonStatus("SIGNIN", not isAutenticated );          
    SetButtonStatus("ALLACH", isAutenticated );        
    SetButtonStatus("UNLOCKACH", isAutenticated );
    SetButtonStatus("ALLLEAD", isAutenticated );
    SetButtonStatus("SUBMITSCORE", isAutenticated );
    SetButtonStatus("SIGNOUT", isAutenticated );
  end
  
end

--[[
function SetButtonStatus( buttonID, enabled )
  if G.basicGUI ~= nil then

    --find the text label to display the text in
	  VMenuItemCollection* items = &spMainDlg->Items();

    --enable the signout button if we are authenticated
	  VDlgControlBasePtr vdlg = items->FindItem( VGUIManager::GetID( buttonID ) );
	  VASSERT_MSG( vdlg != NULL, "The dialog does not have a label with ID '%s'", buttonID );
	  VPushButton* pButton = vstatic_cast<VPushButton*>(vdlg);      	--check this is a VPushButton and set enable/disable
	  pButton->SetEnabled( enabled ); 
  end
end
]]--