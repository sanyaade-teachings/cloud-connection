#ifndef _CLOUDCONNECTIONMODULE_HPP_
#define _CLOUDCONNECTIONMODULE_HPP_

#include "CloudConnectionPluginImportExport.h"

class CloudConnectionClient;
class CloudConnectionScriptMananger;

/// 
/// \brief
/// Module responsible for the Cloud Service Connections
///
class CloudConnectionModule : public IVisCallbackHandler_cl, public VTypedObject
{
public: 
  /** RTTI declarations */
	V_DECLARE_DYNAMIC_DLLEXP(CloudConnectionModule, CLOUDCONNECTIONPLUGIN_IMPEXP);

	CloudConnectionModule();
	virtual ~CloudConnectionModule();

  /// \brief Called Once to initalise when the Plugin is created
  void OneTimeInit();
  /// \brief Called Once to de-initalise when the Plugin is destroyed
  void OneTimeDeInit();

	/// \brief
	///   IVisCallbackHandler_cl implementation  
  virtual void OnHandleCallback(IVisCallbackDataObject_cl *pData) HKV_OVERRIDE;
    
  /// \brief
  /// Gets the Global Instance of this Cloud Connection Module
	CLOUDCONNECTIONPLUGIN_IMPEXP static CloudConnectionModule* GetInstance() 
  {
    return &g_GlobalManager;
  }

  /// \brief Gets the Global Instance of this Cloud Connection Module
  /// \return The Cloud Connection Client for the Target Platform
  CLOUDCONNECTIONPLUGIN_IMPEXP CloudConnectionClient* GetClient();

protected:
  	  
	static CloudConnectionModule g_GlobalManager; ///< one global instance of our manager

private:
  CloudConnectionClient* m_pCloudConnClient; ///< The instance of the Cloud Connection Client for the Target Platform
  CloudConnectionScriptMananger* m_pCloudConnSM;  ///< Manges the Lua/swig bindings for the plugin
};

#endif