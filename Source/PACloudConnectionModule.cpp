#include "PACloudConnectionPluginPCH.hpp"
#include "PACloudConnectionModule.hpp"
#include "ClientFactory.hpp"

PACloudConnectionModule PACloudConnectionModule::g_GlobalManager; ///< static one global instance of our manager

PACloudConnectionModule::PACloudConnectionModule()
{
  // creates a new cloud connection client for the target platform
  m_pCloudConnClient = ClientFactory::GetPACloudConnectionClient(); 
}

PACloudConnectionModule::~PACloudConnectionModule()
{
  V_SAFE_DELETE( m_pCloudConnClient );
}

PACloudConnectionClient* PACloudConnectionModule::GetClient()
{
  return m_pCloudConnClient;
}

void PACloudConnectionModule::OnHandleCallback(IVisCallbackDataObject_cl *pData)
{

}