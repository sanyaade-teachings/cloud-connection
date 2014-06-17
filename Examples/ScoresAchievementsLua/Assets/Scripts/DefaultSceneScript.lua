-- This scene Script file creates opens a Basic GUI and uses it demonstrate Google Play Games basic functions
-- See the MainMenu.lua script file to see how the actions from the dialog that is opened are processed
-- For tutorial on how to use the GUI system in lua then please see http://www.projectanarchy.com/guis-lua

function OnAfterSceneLoaded()
        
   -- initalise the GUI and show it 
  GUI:LoadResourceFile("Dialogs/MenuSystem.xml")
  G.basicGUI = GUI:ShowDialog("Dialogs/CloudConnectionMenu.xml")
  G.basicGUI:SetVisible(true) 
  GUI:SetCursorVisible(true)    

  -- adding listener for CloudConnection callbacks for to this script
  local ccClient = CloudConnection:GetClient()
  ccClient:AddScriptCallbackListener()            
  
end

function OnBeforeSceneUnloaded()

  -- removing listener for CloudConnection callbacks for to this script
  local ccClient = CloudConnection:GetClient()
  ccClient:RemoveScriptCallbackListener()   

  -- close the menu
  local mode = Application:GetEditorMode()
  if mode == Vision.EDITOR_PLAY or mode == Vision.EDITOR_RUN then
     GUI:SetCursorVisible(false)
     GUI:CloseDialog( G.basicGUI )
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


