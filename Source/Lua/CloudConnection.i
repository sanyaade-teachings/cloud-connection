%nodefaultctor CloudConnection;
%nodefaultdtor CloudConnection;

/// 
/// \brief
/// Module responsible for the Cloud Service Connections
///
class CloudConnection : public VTypedObject
{
public: 
  /// \brief
  /// Gets the Global Instance of this Cloud Connection Module
  static CloudConnection* GetInstance();

    //Vision specific extension:
  %extend {
    VSWIG_CREATE_CAST(CloudConnection)
  }
};