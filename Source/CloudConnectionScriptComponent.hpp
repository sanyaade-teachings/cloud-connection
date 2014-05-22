#ifndef _CLOUDCONNECTIONSCRIPTCOMPONENT_HPP_
#define _CLOUDCONNECTIONSCRIPTCOMPONENT_HPP_

#include "VisionBaseIncludes.h"

/// \brief
/// This class provides support for callbacks from the cloud connection client
/// to any Lua scripts that want to listen for things like Authorisation events
class CloudConnectionScriptComponent : public VScriptComponent
{
public:
	// RTTI declarations
	V_DECLARE_DYNCREATE_DLLEXP(CloudConnectionScriptComponent, CLOUDCONNECTIONPLUGIN_IMPEXP); 

  /// \brief Implements IVisCallbackHandler_cl::OnHandleCallback.  
  virtual void OnHandleCallback (IVisCallbackDataObject_cl *pData) HKV_OVERRIDE;

protected:
private:
};

#endif