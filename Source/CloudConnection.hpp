#ifndef _CLOUDCONNECTION_HPP_
#define _CLOUDCONNECTION_HPP_

#include "CloudConnectionPluginImportExport.h"

class CloudConnectionClient;
class CloudConnectionScriptMananger;

/// 
/// \brief
/// Main Module responsible for the Cloud Service Connections
///
class CloudConnection : public IVisCallbackHandler_cl, public VTypedObject
{
public: 
  /** RTTI declarations */
	V_DECLARE_DYNAMIC_DLLEXP(CloudConnection, CLOUDCONNECTIONPLUGIN_IMPEXP);

	CloudConnection();
	virtual ~CloudConnection();

  /// \brief Called Once to initalise when the Plugin is created
  void OneTimeInit();
  /// \brief Called Once to de-initalise when the Plugin is destroyed
  void OneTimeDeInit();

	/// \brief
	///   IVisCallbackHandler_cl implementation  
  virtual void OnHandleCallback(IVisCallbackDataObject_cl *pData) HKV_OVERRIDE;
    
  /// \brief
  /// Gets the Global Instance of this Cloud Connection Module
	CLOUDCONNECTIONPLUGIN_IMPEXP static CloudConnection* GetInstance() 
  {
    return &g_GlobalManager;
  }

  /// \brief Gets the Cloud Connection Client
  /// \return The Cloud Connection Client for the Target Platform
  CLOUDCONNECTIONPLUGIN_IMPEXP CloudConnectionClient* GetClient();

protected:
  	  
	static CloudConnection g_GlobalManager; ///< one global instance of our manager

private:
  CloudConnectionClient* m_pCloudConnClient; ///< The instance of the Cloud Connection Client for the Target Platform
  CloudConnectionScriptMananger* m_pCloudConnSM;  ///< Manges the Lua/swig bindings for the plugin
};

#endif