-- This scene Script file creates opens a Basic GUI and uses it demonstrate Google Play Games basic functions
-- See the MainMenu.lua script file to see how the actions from the dialog that is opened are processed
-- For tutorial on how to use the GUI system in lua then please see http://www.projectanarchy.com/guis-lua

function OnAfterSceneLoaded()
         
  -- initalise the GUI and show it (if it hasn't been done already)
  if G.basicGUI == nil then
    GUI:LoadResourceFile("Dialogs/MenuSystem.xml")
    G.basicGUI = GUI:ShowDialog("Dialogs/CloudConnectionMenu.xml")
    G.basicGUI:SetVisible(true) 
    GUI:SetCursorVisible(true)    
  end
           
end

function OnBeforeSceneUnloaded()

  -- close the menu
  local mode = Application:GetEditorMode()
  if mode == Vision.EDITOR_PLAY or mode == Vision.EDITOR_RUN then
     GUI:SetCursorVisible(false)
     GUI:CloseDialog( G.basicGUI )
  end
end




