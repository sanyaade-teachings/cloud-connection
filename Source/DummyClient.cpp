#include "PACloudConnectionPluginPCH.hpp"
#include "DummyClient.hpp"

   
DummyClient::DummyClient()
{
  m_pPlayerName = new VString("Dummy Player");
}

DummyClient::~DummyClient()
{
  V_SAFE_DELETE( m_pPlayerName );
}

bool DummyClient::IsAuthenticated()
{
  return true;
}

void DummyClient::SignOut()
{
  hkvLog::Info( "PACloudConnectionPlugin - DummyClient::SignOut()" );
}

VString DummyClient::GetUserDisplayName()
{
  return (*m_pPlayerName);
}
