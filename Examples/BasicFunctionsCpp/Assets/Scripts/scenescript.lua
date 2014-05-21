-- new script file

function OnAfterSceneLoaded()

  local ccClient = CloudConnection:GetClient()
  local displayName = ccClient:GetUserDisplayName()
  
   --Console:SetVisible(true)
   Console:PrintLine(displayName)
end
