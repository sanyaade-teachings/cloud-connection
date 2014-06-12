#ifndef _BASICGUI_HPP_
#define _BASICGUI_HPP_

#include <Vision/Runtime/EnginePlugins/VisionEnginePlugin/GUI/vGUI.hpp>

/// \brief
/// Creates a Simple GUI to be used to test the Sign-In/Out fucntionality of the Cloud Connection Plugin
class CloudConnectionGUI : public IVisCallbackHandler_cl
{
public:
  /// \brief initialise our GUI
  void InitGUI();
  /// \brief destroy our GUI
  void DeinitGUI();
  /// \brief show the menu to log-in/out
  void ShowGUI();
  /// \brief call once each while the menu is diplayed to process user input
  void Update();    
  /// \brief IVisCallbackHandler_cl override to listen for Callbacks
  virtual void OnHandleCallback( IVisCallbackDataObject_cl* pData ) HKV_OVERRIDE;
protected:
private:
  /// \brief IVisCallbackHandler_cl enables\disables buttons in the GUI depending on whether the user is authenticated or not
  void AuthenticationChanged();

  /// \brief IVisCallbackHandler_cl enables\disables GUI buttons
  /// \param buttonID The ID of the button to be changed
  /// \param enabled true to enable the button, false to disable it
  void SetButtonStatus(const char* buttonID, bool enabled );

  VSmartPtr<VGUIMainContext> spGUIContext;
  VDialogPtr spMainDlg;
};

#endif
