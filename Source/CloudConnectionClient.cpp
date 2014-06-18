#include "CloudConnectionPluginPCH.hpp"
#include "CloudConnectionClient.hpp"
#include "CloudConnectionScriptComponent.hpp"
#include "CloudConnectionCallbacks.hpp"
#include "CCAchievement.hpp"
#include "CloudConnection.hpp"

const char* CloudConnectionClient::FUNC_ONACHIEVEMENTFETCHED = "OnAchievementFetched"; ///< script Callback function name
const char* CloudConnectionClient::FUNC_ONPLAYERDATAFETCHED  = "OnPlayerDataFetched";  ///< script Callback function name
const char* CloudConnectionClient::FUNC_ONAUTHACTIONFINISHED = "OnAuthActionFinished"; ///< script Callback function name
const char* CloudConnectionClient::FUNC_ONAUTHACTIONSTARTED  = "OnAuthActionStarted";  ///< script Callback function name

/** RTTI definitions */
V_IMPLEMENT_DYNAMIC( CloudConnectionClient, VisTypedEngineObject_cl, &g_CloudConnectionModule );

void CloudConnectionClient::OneTimeInit()
{    	
  //Listen for callbacks from the cloud connection plugin
	CloudConnection::Callbacks.OnAuthActionStarted += this;
	CloudConnection::Callbacks.OnAuthActionFinished += this;
	CloudConnection::Callbacks.OnPlayerDataFetched += this;
  CloudConnection::Callbacks.OnAchievementFetched += this;
}

void CloudConnectionClient::OneTimeDeInit()
{    	
  //UnListen for callbacks from the cloud connection plugin
	CloudConnection::Callbacks.OnAuthActionStarted -= this;
	CloudConnection::Callbacks.OnAuthActionFinished -= this;
	CloudConnection::Callbacks.OnPlayerDataFetched -= this;
  CloudConnection::Callbacks.OnAchievementFetched -= this;
}

/// \brief IVisCallbackHandler_cl override
void CloudConnectionClient::OnHandleCallback( IVisCallbackDataObject_cl* pData )
{
  //Listen here for sign-in/sign-out callbacks
  if( pData->m_pSender == &CloudConnection::Callbacks.OnAuthActionStarted )
  {
    hkvLog::Debug("CloudConnectionScriptComponent - %s", FUNC_ONAUTHACTIONSTARTED);
    TriggerCCScriptFunction(FUNC_ONAUTHACTIONSTARTED);
  }
  else if( pData->m_pSender==&CloudConnection::Callbacks.OnAuthActionFinished )
  {                
    hkvLog::Debug("CloudConnectionScriptComponent - %s", FUNC_ONAUTHACTIONFINISHED);
    TriggerCCScriptFunction(FUNC_ONAUTHACTIONFINISHED);
  }
  else if( pData->m_pSender==&CloudConnection::Callbacks.OnPlayerDataFetched )
  {                
    hkvLog::Debug("CloudConnectionScriptComponent - %s", FUNC_ONPLAYERDATAFETCHED);
    TriggerCCScriptFunction(FUNC_ONPLAYERDATAFETCHED);
  }
  else if( pData->m_pSender==&CloudConnection::Callbacks.OnAchievementFetched )
  {                
    if ( pData != NULL )
    {          
      CCAchievement* pAch = (CCAchievement*)pData;
      hkvLog::Debug("CloudConnectionScriptComponent - %s '%s','%s'", FUNC_ONACHIEVEMENTFETCHED, pAch->Id(), pAch->Name() );

      if ( pAch->Valid() )
      {
        //send the achievemnt data on to lua via the callback (all the script instances)
        VScriptResourceManager& scriptManager = VScriptResourceManager::GlobalManager();  
        VRefCountedCollection<VScriptInstance>& scriptInstances = scriptManager.Instances();

        //send callback to each script that has the function
        for( int i = 0; i < scriptInstances.Count(); i++ )
        {
          VScriptInstance* pScriptInst = scriptInstances.GetAt(i);
          if ( pScriptInst != NULL )
          {
            if ( pScriptInst->HasFunction(FUNC_ONACHIEVEMENTFETCHED) )
            {                              
              //this would be nice instead of a function with loads of parameters 
              // but couldn't get this to make an instance of the object in lua??? (causes buffer overflow)
              //pScriptInst->ExecuteFunctionArg(FUNC_ONACHIEVEMENTFETCHED, "t",  pAch);  

              //send this data on to Lua
              pScriptInst->ExecuteFunctionArg(FUNC_ONACHIEVEMENTFETCHED, "sssiiii", 
                pAch->Id(), 
                pAch->Name(), 
                pAch->Description(),
                pAch->Type(),
                pAch->State(),
                pAch->TotalSteps(),
                pAch->CurrentSteps() );
            }
          }      
        }
      }

    }
    else
    {
      hkvLog::Warning("CloudConnectionClient::OnHandleCallback - The Achievement data sent via the callback OnAchievementFetched was null");
    }
  }
}

void CloudConnectionClient::TriggerCCScriptFunction( const char* szFunction )
{          
  //get all the script instances
  VScriptResourceManager& scriptManager = VScriptResourceManager::GlobalManager();  
  VRefCountedCollection<VScriptInstance>& scriptInstances = scriptManager.Instances();

  //send callback to each script that has the function
  for( int i = 0; i < scriptInstances.Count(); i++ )
  {
    VScriptInstance* pScriptInst = scriptInstances.GetAt(i);
    if ( pScriptInst != NULL )
    {
      if ( pScriptInst->HasFunction(szFunction) )
      {                
        pScriptInst->ExecuteFunction(szFunction);
      }
    }
  }    
}