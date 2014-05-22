#include "CloudConnectionPluginPCH.hpp"
#include "CloudConnection.hpp"
#include "ClientFactory.hpp"
#include "CloudConnectionScriptManager.hpp"

CloudConnection CloudConnection::g_GlobalManager; ///< static one global instance of our manager

/** RTTI definitions */
V_IMPLEMENT_DYNAMIC( CloudConnection, VTypedObject, &g_CloudConnectionModule );

CloudConnection::CloudConnection()
{
  // creates a new cloud connection client for the target platform
  m_pCloudConnClient = ClientFactory::CreateCloudConnectionClient(); 
  m_pCloudConnSM = new CloudConnectionScriptMananger();
}

CloudConnection::~CloudConnection()
{
  V_SAFE_DELETE( m_pCloudConnClient );
  V_SAFE_DELETE( m_pCloudConnSM );
}

CloudConnectionClient* CloudConnection::GetClient()
{
  return m_pCloudConnClient;
}

void CloudConnection::OneTimeInit()
{    
  m_pCloudConnSM->OneTimeInit();    //initalise lua scripting
  m_pCloudConnClient->OneTimeInit();
}

void CloudConnection::OneTimeDeInit()
{
  m_pCloudConnSM->OneTimeDeInit();  //deinitialise lua scripting
  m_pCloudConnClient->OneTimeDeInit();  
}

void CloudConnection::OnHandleCallback(IVisCallbackDataObject_cl *pData)
{

}