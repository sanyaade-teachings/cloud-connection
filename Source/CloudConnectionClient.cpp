#include "CloudConnectionPluginPCH.hpp"
#include "CloudConnectionClient.hpp"
#include "CloudConnectionScriptComponent.hpp"
#include "CloudConnectionCallbacks.hpp"
#include "CCAchievement.hpp"

/** RTTI definitions */
V_IMPLEMENT_DYNAMIC( CloudConnectionClient, VisTypedEngineObject_cl, &g_CloudConnectionModule );

void CloudConnectionClient::OneTimeInit()
{    	
  //Listen for callbacks from the cloud connection plugin
	CloudConnectionCallbackManager::OnAuthActionStarted += this;
	CloudConnectionCallbackManager::OnAuthActionFinished += this;
	CloudConnectionCallbackManager::OnPlayerDataFetched += this;
  CloudConnectionCallbackManager::OnAchievementFetched += this;
}

void CloudConnectionClient::OneTimeDeInit()
{    	
  //UnListen for callbacks from the cloud connection plugin
	CloudConnectionCallbackManager::OnAuthActionStarted -= this;
	CloudConnectionCallbackManager::OnAuthActionFinished -= this;
	CloudConnectionCallbackManager::OnPlayerDataFetched -= this;
  CloudConnectionCallbackManager::OnAchievementFetched -= this;
}

void CloudConnectionClient::AddScriptCallbackListener( VScriptInstance* pInstance )
{    
  VASSERT_MSG( pInstance != NULL, "The script instance to add to the cloud connection client cannot be null" );


  VScriptComponent* pComp = Components().GetComponentOfType<CloudConnectionScriptComponent>();
  if ( pComp == NULL )
  {
    IVScriptManager* pSM = Vision::GetScriptManager();
    if(pSM)
    {
      lua_State* pLuaState = ((VScriptResourceManager*)pSM)->GetMasterState();
      VASSERT_MSG( pLuaState != NULL, "The lua state cannot be null" );
      if(pLuaState) 
      {
        //add the script component
        CloudConnectionScriptComponent* pScriptComponent = new CloudConnectionScriptComponent();    
        pScriptComponent->Initialize();
        pScriptComponent->SetScriptInstance( pInstance );
        AddComponent( pScriptComponent );

        hkvLog::Debug("added CloudConnectionScriptComponent to the script instance");
      }
    }
  }
  else
  {
    hkvLog::Debug("CloudConnectionClient already has an instance of the cloud connection script component");
  }
}

/// \brief IVisCallbackHandler_cl override
void CloudConnectionClient::OnHandleCallback( IVisCallbackDataObject_cl* pData )
{
  //Listen here for sign-in/sign-out callbacks
  hkvLog::Debug("CloudConnectionScriptComponent - OnHandleCallback");      
  if( pData->m_pSender == &CloudConnectionCallbackManager::OnAuthActionStarted )
  {
    hkvLog::Debug("CloudConnectionScriptComponent - OnAuthActionStarted");
    TriggerCCScriptFunction("OnAuthActionStarted");
  }
  else if( pData->m_pSender==&CloudConnectionCallbackManager::OnAuthActionFinished )
  {                
    hkvLog::Debug("CloudConnectionScriptComponent - OnAuthActionFinished");
    TriggerCCScriptFunction("OnAuthActionFinished");
  }
  else if( pData->m_pSender==&CloudConnectionCallbackManager::OnPlayerDataFetched )
  {                
    hkvLog::Debug("CloudConnectionScriptComponent - OnPlayerDataFetched");
    TriggerCCScriptFunction("OnPlayerDataFetched");
  }
  else if( pData->m_pSender==&CloudConnectionCallbackManager::OnAchievementFetched )
  {                
    if ( pData != NULL )
    {          
      CCAchievement* pAch = (CCAchievement*)pData;
      hkvLog::Debug("CloudConnectionScriptComponent - OnAchievementFetched '%s','%s'", pAch->Id(), pAch->Name() );

      if ( pAch->Valid() )
      {
        //this would be nice instead of a function with loads of parameters but couldn't get this to make an instance of the object in lua???
        //TriggerCCScriptFunctionArg("OnAchievementFetched", "t",  pAch);   

        //send the achievemnt data on to lua via the callback
        VScriptComponent* pComp = Components().GetComponentOfType<CloudConnectionScriptComponent>();  //there is only one CloudConnectionScriptComponent
        if ( pComp != NULL )
        {
          VScriptInstance* pScriptInst = pComp->GetScriptInstance();
          if ( pScriptInst != NULL )
          {
            const char* szFunction = "OnAchievementFetched";
            if ( pScriptInst->HasFunction(szFunction) )
            {                
              //send this data on to Lua
              pScriptInst->ExecuteFunctionArg(szFunction, "sssiiii", 
                pAch->Id(), 
                pAch->Name(), 
                pAch->Description(),
                pAch->Type(),
                pAch->State(),
                pAch->TotalSteps(),
                pAch->CurrentSteps() );
            }
            else
            {
              hkvLog::Warning("CloudConnectionClient - CloudConnectionScriptComponent does not have callback function '%s'", szFunction);
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
  VScriptComponent* pComp = Components().GetComponentOfType<CloudConnectionScriptComponent>();  //there is only one CloudConnectionScriptComponent
  if ( pComp != NULL )
  {
    VScriptInstance* pScriptInst = pComp->GetScriptInstance();
    if ( pScriptInst != NULL )
    {
      if ( pScriptInst->HasFunction(szFunction) )
      {                
        pScriptInst->ExecuteFunction(szFunction);
      }
      else
      {
        hkvLog::Warning("CloudConnectionClient - CloudConnectionScriptComponent does not have callback function '%s'", szFunction);
      }
    }      
  }
}

void CloudConnectionClient::TriggerCCScriptFunctionArg( const char* szFunction, const char* szArgFormat, void* parameter )
{      
  VScriptComponent* pComp = Components().GetComponentOfType<CloudConnectionScriptComponent>();  //there is only one CloudConnectionScriptComponent
  if ( pComp != NULL )
  {
    VScriptInstance* pScriptInst = pComp->GetScriptInstance();
    if ( pScriptInst != NULL )
    {
      if ( pScriptInst->HasFunction(szFunction) )
      {                
        // We access the ellipses through a va_list, so let's declare one
        pScriptInst->ExecuteFunctionArg(szFunction, szArgFormat, parameter);
      }
      else
      {
        hkvLog::Warning("CloudConnectionClient - CloudConnectionScriptComponent does not have callback function '%s'", szFunction);
      }
    }      
  }
}