#ifndef _CLOUDCONNECTIONMODULE_HPP_
#define _CLOUDCONNECTIONMODULE_HPP_

#include "CloudConnectionPluginImportExport.h"

class CloudConnectionClient;

/// 
/// \brief
/// Module responsible for the Cloud Service Connections
///
class CloudConnectionModule : public IVisCallbackHandler_cl
{
public:
	CloudConnectionModule();
	virtual ~CloudConnectionModule();

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
};

#endif