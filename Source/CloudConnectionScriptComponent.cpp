#include "CloudConnectionPluginPCH.hpp"
#include "CloudConnectionScriptComponent.hpp"
#include "CloudConnectionCallbacks.hpp"

// register the class in the engine module so it is available for RTTI
V_IMPLEMENT_DYNCREATE(CloudConnectionScriptComponent,VScriptComponent, &g_CloudConnectionModule );


void CloudConnectionScriptComponent::OnHandleCallback (IVisCallbackDataObject_cl *pData)
{
  VScriptComponent::OnHandleCallback(pData);  //call our superclass
}