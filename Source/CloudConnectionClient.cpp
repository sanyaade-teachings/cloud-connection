#include "CloudConnectionPluginPCH.hpp"
#include "CloudConnectionClient.hpp"
#include "CloudConnectionScriptComponent.hpp"
#include "CloudConnectionCallbacks.hpp"

/** RTTI definitions */
V_IMPLEMENT_DYNAMIC( CloudConnectionClient, VisTypedEngineObject_cl, &g_CloudConnectionModule );

void CloudConnectionClient::OneTimeInit()
{    	
  //Listen for callbacks from the cloud connection plugin
	CloudConnectionCallbackManager::OnAuthActionStarted += this;
	CloudConnectionCallbackManager::OnAuthActionFinished += this;
	CloudConnectionCallbackManager::OnPlayerDataFetched += this;
}

void CloudConnectionClient::OneTimeDeInit()
{    	
  //UnListen for callbacks from the cloud connection plugin
	CloudConnectionCallbackManager::OnAuthActionStarted -= this;
	CloudConnectionCallbackManager::OnAuthActionFinished -= this;
	CloudConnectionCallbackManager::OnPlayerDataFetched -= this;
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
    //Trigger script here

    /**
    	IVScriptInstancePtr ssscript = Vision::GetScriptManager()->GetSceneScript();
	    if ( ssscript != NULL ) {
		    VASSERT_MSG( ssscript->HasFunction( function ), "The lua function '%s' does not exist in the scene script file", function );
		    ssscript->ExecuteFunctionArg( function, "t", this );
	    }
      */

  }
  else if( pData->m_pSender==&CloudConnectionCallbackManager::OnAuthActionFinished )
  {                
    hkvLog::Debug("CloudConnectionScriptComponent - OnAuthActionFinished");
    //Trigger script here
  }
  else if( pData->m_pSender==&CloudConnectionCallbackManager::OnPlayerDataFetched )
  {                
    hkvLog::Debug("CloudConnectionScriptComponent - OnPlayerDataFetched");
    // Trigger script here
  }
}