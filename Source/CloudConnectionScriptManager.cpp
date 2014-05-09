#include "CloudConnectionPluginPCH.hpp"
#include "CloudConnectionScriptManager.hpp"
#include "VisionBaseIncludes.h"
#include "CloudConnectionClient.hpp"
#include "CloudConnectionModule.hpp"

#define LUA_MODULE_CLOUDCONNECTION "CloudConnection"
extern "C" int luaopen_CloudConnection(lua_State *);

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
        luaopen_CloudConnection(pLuaState);
      } 
      else 
      {
        hkvLog::FatalError("Unable to create Lua CloudConnection Module, lua_State is NULL!");
      }
    }
  } 
  else if(pData->m_pSender==&IVScriptManager::OnScriptProxyCreation) 
  {
		VScriptCreateStackProxyObject * pScriptData = (VScriptCreateStackProxyObject *)pData;

		//process data only if no other callback did that
		if(!pScriptData->m_bProcessed)
		{
			int iRetParams = 0;

			if(pScriptData->m_pInstance->IsOfType(V_RUNTIME_CLASS(CloudConnectionClient)))
      {
				//call lua cast function for CloudConnectionClient (created via the macro in CloudConnectionClient.i)
				iRetParams = LUA_CallStaticFunction(
					pScriptData->m_pLuaState, // our lua state
					LUA_MODULE_CLOUDCONNECTION, // the name of the module
					"CloudConnectionClient", // the name of the class
					"Cast", // the name of the fucntion
					"E>E", // the function's signature
					pScriptData->m_pInstance //the input parameters (out instance to cast)
					);
			} 
      else if(pScriptData->m_pInstance->IsOfType( V_RUNTIME_CLASS(CloudConnectionModule) )) 
      {
				//call lua cast function for CloudConnectionModule (created via the macro in CloudConnectionModule.i)
				iRetParams = LUA_CallStaticFunction(
					pScriptData->m_pLuaState, // our lua state
					LUA_MODULE_CLOUDCONNECTION, // the name of the module
					"CloudConnectionModule", // the name of the class
					"Cast", // the name of the fucntion
					"E>E", // the function's signature
					pScriptData->m_pInstance //the input parameters (out instance to cast)
					);
			}

			//could we handle the object?
			if(iRetParams>0)
			{
				//the cast failed if the result is a nil value
				if(lua_isnil(pScriptData->m_pLuaState, -1))
        {
					lua_pop(pScriptData->m_pLuaState, iRetParams); //in case of a nil value we drop the params from the lua stack
        }
				else
        {
					pScriptData->m_bProcessed = true; //avoid further processing
        }
			}
		}
	}
}