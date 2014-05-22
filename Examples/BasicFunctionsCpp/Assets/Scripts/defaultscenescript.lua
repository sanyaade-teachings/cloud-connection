-- This scene Script file creates opens a Basic GUI and uses it demonstrate Google Play Games basic functions
-- See the MainMenu.lua script file to see how the actions from the dialog that is opened are processed
-- For tutorial on how to use the GUI system in lua then please see http://www.projectanarchy.com/guis-lua

function OnAfterSceneLoaded()

  local ccClient = CloudConnection:GetClient()
  local displayName = ccClient:GetUserDisplayName()  
   --Console:SetVisible(true)
   --Console:PrintLine(displayName)
   
   -- initalise the GUI   
  GUI:LoadResourceFile("Dialogs/MenuSystem.xml")
  G.basicGUI = GUI:ShowDialog("Dialogs/MainMenu.xml")
  G.basicGUI:SetVisible(true) 
  GUI:SetCursorVisible(true)                         
       
end

function OnBeforeSceneUnloaded()

  local mode = Application:GetEditorMode()
  if mode == Vision.EDITOR_PLAY or mode == Vision.EDITOR_RUN then
     GUI:SetCursorVisible(false)
     GUI:CloseDialog( G.basicGUI )
  end

end
