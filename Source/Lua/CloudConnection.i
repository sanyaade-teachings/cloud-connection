%nodefaultctor CloudConnection;
%nodefaultdtor CloudConnection;

/// 
/// \brief
/// Module responsible for the Cloud Service Connections
///
class CloudConnection : public VTypedObject
{
public:   

  /// \brief Gets the Cloud Connection Client
  /// \return The Cloud Connection Client for the Target Platform
  CloudConnectionClient* GetClient();

  //Vision specific extension:
  %extend 
  {
    VSWIG_CREATE_CAST_UNSAFE(CloudConnection);
  }
};