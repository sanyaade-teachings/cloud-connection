#ifndef _CLOUDCONNECTIONPLUGIN_HPP_
#define _CLOUDCONNECTIONPLUGIN_HPP_

#include "VisionBaseIncludes.h"
#include "CloudConnection.hpp"

#define PACCP_PLUGIN_NAME "CloudConnectionPlugin"

class CloudConnectionPlugin : public IVisPlugin_cl
{
public:
	CloudConnectionPlugin() {}

	void OnInitEnginePlugin() HKV_OVERRIDE;    
	void OnDeInitEnginePlugin() HKV_OVERRIDE;  

	const char *GetPluginName() HKV_OVERRIDE
	{
		return PACCP_PLUGIN_NAME;  // must match DLL name
	}
	
private:
};

CloudConnectionPlugin g_CloudConnectionPlugin;  ///< global plugin instance

// A module for the serialization (g_PACloudConnectionModule is defined in the pre-compiled header)
DECLARE_THIS_MODULE( g_CloudConnectionModule, MAKE_VERSION(1,0),
					 "Cloud Connection Plugin", "Havok",
					 "Module for the Connection to Cloud Services e.g. Google Play Games", &g_CloudConnectionPlugin );

//  Use this to get and initialize the plugin when you link statically
VEXPORT IVisPlugin_cl* GetEnginePlugin_CloudConnectionPlugin()
{
  return &g_CloudConnectionPlugin;
}

#if ((defined _DLL) || (defined _WINDLL)) && !defined(VBASE_LIB)
//  The engine uses this to get and initialize the plugin dynamically
VEXPORT IVisPlugin_cl* GetEnginePlugin()
{
  return GetEnginePlugin_CloudConnectionPlugin();
}
#endif // _DLL or _WINDLL

void CloudConnectionPlugin::OnInitEnginePlugin()
{
  // register our module when the plugin is initialized
  Vision::RegisterModule(&g_CloudConnectionModule);

  CloudConnection* ccm = CloudConnection::GetInstance();
  ccm->OneTimeInit();
}

void CloudConnectionPlugin::OnDeInitEnginePlugin()
{
  // de-register our module when the plugin is de-initialized
  Vision::UnregisterModule(&g_CloudConnectionModule);

  CloudConnection* ccm = CloudConnection::GetInstance();
  ccm->OneTimeDeInit();
}

#endif