#ifndef _PACLOUDCONNECTIONPLUGIN_HPP_
#define _PACLOUDCONNECTIONPLUGIN_HPP_

#include "VisionBaseIncludes.h"

#define PACCP_PLUGIN_NAME "PACloudConnectionPlugin"

class PACloudConnectionPlugin : public IVisPlugin_cl
{
public:
	PACloudConnectionPlugin() {}

	void OnInitEnginePlugin() HKV_OVERRIDE;    
	void OnDeInitEnginePlugin() HKV_OVERRIDE;  

	const char *GetPluginName() HKV_OVERRIDE
	{
		return PACCP_PLUGIN_NAME;  // must match DLL name
	}
	
private:
};

PACloudConnectionPlugin g_PACloudConnectionPlugin;  ///< global plugin instance

// A module for the serialization (g_PACloudConnectionModule is defined in the pre-compiled header)
DECLARE_THIS_MODULE( g_PACloudConnectionModule, MAKE_VERSION(1,0),
					 "PA Cloud Conncetion Plugin", "Havok",
					 "Module for the Connection to Cloud Services e.g. Google Play Games", &g_PACloudConnectionPlugin );

//  Use this to get and initialize the plugin when you link statically
VEXPORT IVisPlugin_cl* GetEnginePlugin_PACloudConnectionPlugin()
{
  return &g_PACloudConnectionPlugin;
}

#if ((defined _DLL) || (defined _WINDLL)) && !defined(VBASE_LIB)
//  The engine uses this to get and initialize the plugin dynamically
VEXPORT IVisPlugin_cl* GetEnginePlugin()
{
  return GetEnginePlugin_PACloudConnectionPlugin();
}
#endif // _DLL or _WINDLL


void PACloudConnectionPlugin::OnInitEnginePlugin()
{
  hkvLog::Debug("PACloudConnectionPlugin:OnInitEnginePlugin()");

  // register our module when the plugin is initialized
  Vision::RegisterModule(&g_PACloudConnectionModule);
}

void PACloudConnectionPlugin::OnDeInitEnginePlugin()
{
  hkvLog::Debug("PACloudConnectionPlugin:OnDeInitEnginePlugin()");

  // de-register our module when the plugin is de-initialized
  Vision::UnregisterModule(&g_PACloudConnectionModule);
}


#endif