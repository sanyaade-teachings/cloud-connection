#include "CloudConnectionPluginPCH.hpp"
#include "CloudConnectionScriptManager.hpp"
#include "VisionBaseIncludes.h"
#include "CloudConnectionClient.hpp"
#include "CloudConnection.hpp"
#include "CCAchievement.hpp"

#define LUA_MODULE_CLOUDCONNECTION "CloudConnectionLuaModule"
extern "C" int luaopen_CloudConnectionLuaModule(lua_State *);

CloudConnectionScriptMananger::CloudConnectionScriptMananger() {}
CloudConnectionScriptMananger::~CloudConnectionScriptMananger() {}

void CloudConnectionScriptMananger::OneTimeInit() 
{
  IVScriptManager::OnRegisterScriptFunctions += this;
  IVScriptManager::OnScriptProxyCreation += this;
}

void CloudConnectionScriptMananger::OneTimeDeInit() 
{
  IVScriptManager::OnRegisterScriptFunctions -= this;
  IVScriptManager::OnScriptProxyCreation -= this;
}

void CloudConnectionScriptMananger::OnHandleCallback( IVisCallbackDataObject_cl* pData ) 
{
  if(pData->m_pSender==&IVScriptManager::OnRegisterScriptFunctions)
  {
    IVScriptManager* pSM = Vision::GetScriptManager();
    if(pSM)
    {
      lua_State* pLuaState = ((VScriptResourceManager*)pSM)->GetMasterState();
      if(pLuaState) 
      {
        luaopen_CloudConnectionLuaModule(pLuaState);
        
        //Register the global instance of the class "CloudConnection"
        hkvLog::Debug("CloudConnectionScriptMananger - Attempt to register the global instance of the class \"CloudConnection\"");

        //** Removed this for now as it instantly crashes the Android build **
        int iRetParams = LUA_CallStaticFunction(pLuaState, LUA_MODULE_CLOUDCONNECTION, "CloudConnection", "Cast", "v>v", CloudConnection::GetInstance());        
			  if (iRetParams==1)
			  {
				  if(lua_isnil(pLuaState, -1))
				  {
					  lua_pop(pLuaState, iRetParams);
            hkvLog::Warning("Unable to create 'CloudConnection' Global in lua - 1");
				  }
				  else
				  {
					  lua_setglobal(pLuaState, "CloudConnection");  //defines the global "CloudConnection" availble in Lua
            hkvLog::Debug("CloudConnectionScriptMananger - Registered the global instance of the class \"CloudConnection\"");
				  }
			  }
        else
        {
          hkvLog::Warning("2: Unable to create 'CloudConnection' Global in lua - 2");
        }
        
      } 
      else 
      {
        hkvLog::Warning("Unable to create CloudConnection Lua Module, lua_State is NULL!");
      }
    }
    else
    {
      hkvLog::Warning("Unable to get the VScriptManager in CloudConnection Lua Module");
    }
  } 
}