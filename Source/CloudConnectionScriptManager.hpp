#ifndef _CLOUDCONNECTIONSCRIPTMANAGER_H_
#define _CLOUDCONNECTIONSCRIPTMANAGER_H_

/// \brief
/// Handles the registration of our custom Lua script bindings
class CloudConnectionScriptMananger : public IVisCallbackHandler_cl 
{
public:
  CloudConnectionScriptMananger();
  ~CloudConnectionScriptMananger();

  /// \brief registers all the callbacks required
  void OneTimeInit();
  /// \brief unregisters all the callbacks required
  void OneTimeDeInit();

  /// \brief native override
  virtual void OnHandleCallback( IVisCallbackDataObject_cl* pData ) HKV_OVERRIDE;
protected:
private:
};

#endif