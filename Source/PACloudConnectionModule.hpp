#ifndef _PACLOUDCONNECTIONMODULE_HPP_
#define _PACLOUDCONNECTIONMODULE_HPP_

#include "PACloudConnectionPluginImportExport.h"

class PACloudConnectionClient;

/// 
/// \brief
/// Module responsible for the Cloud Service Connections
///
class PACloudConnectionModule : public IVisCallbackHandler_cl
{
public:
	PACloudConnectionModule();
	virtual ~PACloudConnectionModule();

	/// \brief
	///   IVisCallbackHandler_cl implementation  
  virtual void OnHandleCallback(IVisCallbackDataObject_cl *pData) HKV_OVERRIDE;
    
  /// \brief
  /// Gets the Global Instance of this Cloud Connection Module
	PACLOUDCONNECTIONPLUGIN_IMPEXP static PACloudConnectionModule* GetInstance() 
  {
    return &g_GlobalManager;
  }

  /// \brief Gets the Global Instance of this Cloud Connection Module
  /// \return The Cloud Connection Client for the Target Platform
  PACLOUDCONNECTIONPLUGIN_IMPEXP PACloudConnectionClient* GetClient();

protected:
  	  
	static PACloudConnectionModule g_GlobalManager; ///< one global instance of our manager

private:
  PACloudConnectionClient* m_pCloudConnClient; ///< The instance of the Cloud Connection Client for the Target Platform
};

#endif