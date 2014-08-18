-- This scene Script file creates opens a Basic GUI and uses it demonstrate Google Play Games basic functions
-- See the MainMenu.lua script file to see how the actions from the dialog that is opened are processed
-- For tutorial on how to use the GUI system in lua then please see http://www.projectanarchy.com/guis-lua

-- used to track if the authentication Google services has changed
-- Set to true by default as the user may have been automatically logged into to Google services
-- on startup of the application (if they have used the game before and logged in), 
-- so we need to check whether we should display the sign-in button or the menu that appears after sign-in
authenticationChanged = true    

function OnAfterSceneLoaded()
           
  GUI:LoadResourceFile("Dialogs/MenuSystem.xml")
  GUI:SetCursorVisible(true)
           
  local screenWidth,screenHeight = Screen:GetViewportSize()
  
  -- the x,y position of the Google+ sign-in button on screen
  buttonWidth = 492
  buttonHeight = 108   
  buttonX = screenWidth - buttonWidth
  buttonY = 0
  
  -- create a screen mask to act as the google sign in button
  G.googleSignInButton = Game:CreateScreenMask(buttonX,buttonY, "Textures/GoogleSigninButtonRedLong.png")  
  G.googleSignInButton:SetBlending(Vision.BLEND_ALPHA)
        
  -- create an input map to the sign-in button (touch screen and mouse)
  G.inputMap = Input:CreateMap()
  G.inputMap:MapTrigger("SignInButton", {buttonX,buttonY,buttonX+buttonWidth,buttonY+buttonHeight, 10000}, "CT_TOUCH_ANY", {once = true})   -- map a trigger to the touch area at x,y, width,height with priority 10000 
  G.inputMap:MapTrigger("SignInButton", {buttonX,buttonY,buttonX+buttonWidth,buttonY+buttonHeight, 10000, "MOUSE"}, "CT_MOUSE_LEFT_BUTTON", {once = true})   -- map a trigger for the left mouse button

end

function OnBeforeSceneUnloaded()
  GUI:SetCursorVisible(false) 

  -- remove any screen masks we created    
  G.googleSignInButton = nil
  Game:DeleteAllUnrefScreenMasks()
  -- remove any input maps we created
  if G.inputMap ~= nil then
    Input:DestroyMap(G.inputMap)
  end

  hideGUIMenu()
end


function OnUpdateSceneFinished()
	Debug:Enable(true)  
  local ccClient = CloudConnection:GetClient()      -- get the cloud connection client     
       
  -- the user authentication has changed and the user 
  -- may be signed-in or out at this point so display the correct menu
  if authenticationChanged then   
    displayMenu()
    authenticationChanged = false
  end
  
  -- check to see if the sign in button was pressed
  if ccClient:IsAuthenticated() == false then    
    local signInButtonTrigger = G.inputMap:GetTrigger("SignInButton")
    
    -- user clicked the google sign in button
    if signInButtonTrigger > 0 then    
      Debug:Log("show the user sign-in dialog")
      
      -- show the user sign-in dialog
      -- this method will return straight away and we will be notified
      -- in the OnAuthActionFinished() method when it is finished
      ccClient:BeginUserInitiatedSignIn()               
    end  
  end
  
end

--This callback is made to the script when the Cloud Connection
--Client has finsihed the authorisation process, either succesfully or unsucesfully
--this call can also be the result of a sign-out as well as a sign-in attempt
function OnAuthActionFinished()
  Debug:Log("OnAuthActionFinished callback was successfully made to Lua script")

  -- set our flag to show that authentication may have changed
  authenticationChanged = true
end

--This callback is made to the script when the Cloud Connection
--Client has started the authorisation process
function OnAuthActionStarted()
  Debug:Log("OnAuthActionStarted callback was successfully made to Lua script")    
end

-- shows either the main menu or the sign-in button
-- depending on whether the user is authenticated or not
-- by the cloud connection plugin
function displayMenu()   
  local ccClient = CloudConnection:GetClient()
  
  -- check the authentication
  if ccClient:IsAuthenticated() then
    Debug:Log("The user is authenticated so show the main menu" )
    showGUIMenu()
  else
    Debug:Log("The user is not authenticated so show the sign-in button" )
    hideGUIMenu()
  end
end 

-- shows the GUI main menu and hides the sign-in button
function showGUIMenu()
  -- initalise the GUI and show it
  G.basicGUI = GUI:ShowDialog("Dialogs/CloudConnectionMenu.xml")    
  G.basicGUI:SetVisible(true)
  
  G.googleSignInButton:SetVisible(false)
  GUI:SetCursorVisible(true)
end

-- hides the GUI main menu and shows the sign-in button
function hideGUIMenu()
  -- close the menu
  if G.basicGUI ~= nil then
     GUI:CloseDialog( G.basicGUI )
  end
  
  G.googleSignInButton:SetVisible(true)
  GUI:SetCursorVisible(true)
end
