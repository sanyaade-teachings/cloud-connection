#include "CloudConnectionPluginPCH.hpp"
#include "GPGIOSClient.hpp"

#if defined(_VISION_IOS)

/** RTTI definitions */
V_IMPLEMENT_DYNAMIC( GPGIOSClient, CloudConnectionClient, &g_CloudConnectionModule );
   
GPGIOSClient::GPGIOSClient()
{

}

GPGIOSClient::~GPGIOSClient()
{

}

#endif