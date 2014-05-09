#include "CloudConnectionPluginPCH.hpp"
#include "CloudConnectionModule.hpp"
#include "ClientFactory.hpp"
#include "CloudConnectionScriptManager.hpp"

CloudConnectionModule CloudConnectionModule::g_GlobalManager; ///< static one global instance of our manager

/** RTTI definitions */
V_IMPLEMENT_DYNAMIC( CloudConnectionModule, VTypedObject, &g_CloudConnectionModule );

CloudConnectionModule::CloudConnectionModule()
{
  // creates a new cloud connection client for the target platform
  m_pCloudConnClient = ClientFactory::GetCloudConnectionClient(); 
  m_pCloudConnSM = new CloudConnectionScriptMananger();
}

CloudConnectionModule::~CloudConnectionModule()
{
  V_SAFE_DELETE( m_pCloudConnClient );
  V_SAFE_DELETE( m_pCloudConnSM );
}

CloudConnectionClient* CloudConnectionModule::GetClient()
{
  return m_pCloudConnClient;
}

void CloudConnectionModule::OneTimeInit()
{
  m_pCloudConnSM->OneTimeInit();    //initalise lua scripting
}

void CloudConnectionModule::OneTimeDeInit()
{
  m_pCloudConnSM->OneTimeDeInit();  //deinitialise lua scripting
}

void CloudConnectionModule::OnHandleCallback(IVisCallbackDataObject_cl *pData)
{

}