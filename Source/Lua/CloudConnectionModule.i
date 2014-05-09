%nodefaultctor CloudConnectionModule;
%nodefaultdtor CloudConnectionModule;

/// 
/// \brief
/// Module responsible for the Cloud Service Connections
///
class CloudConnectionModule : public VTypedObject
{
public: 
  /// \brief
  /// Gets the Global Instance of this Cloud Connection Module
  static CloudConnectionModule* GetInstance();

    //Vision specific extension:
  %extend {
    VSWIG_CREATE_CAST(CloudConnectionModule)
  }
};