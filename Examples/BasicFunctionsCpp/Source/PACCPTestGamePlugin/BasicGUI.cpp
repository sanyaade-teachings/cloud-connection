#include "PACCPTestGamePluginPCH.h"
#include "BasicGui.hpp"
#include "CloudConnectionBase.h"

//this is the ID of the achievement that this demo unlocks
//get this from the google developer console when you create your achievements
#define ACHIEVEMENT_ID "CggI9__cunsQAhAB"     

//this is the ID of the leaderboard that this demo will submit a score to
//get this from the google developer console when you create your leaderboard
#define LEADERBOARD_ID "CggI9__cunsQAhAC"

void BasicGUI::InitGUI()
{
  spGUIContext = new VGUIMainContext(NULL);
  spGUIContext->SetActivate(true);

  //Listen for callbacks from the cloud connection plugin
  CloudConnection::Callbacks.OnAuthActionStarted += this;
  CloudConnection::Callbacks.OnAuthActionFinished += this;
  CloudConnection::Callbacks.OnPlayerDataFetched += this;
  CloudConnection::Callbacks.OnAchievementFetched += this;
}

void BasicGUI::DeinitGUI()
{
  //spMainDlg = NULL; // destroy the MainDlg Object (don't call this if the xml has a script defined or get an object already disposed error on exit)
  spGUIContext->SetActivate(false); // Don't forget to deinit the GUI context
  spGUIContext = NULL; // destroy the GUI context

  //stop Listening for callbacks from the cloud connection plugin
  CloudConnection::Callbacks.OnAuthActionStarted -= this;
  CloudConnection::Callbacks.OnAuthActionFinished -= this;
  CloudConnection::Callbacks.OnPlayerDataFetched -= this;
  CloudConnection::Callbacks.OnAchievementFetched -= this;
}

void BasicGUI::ShowGUI()
{        
  Vision::File.AddSearchPath( ":template_root/Assets" );

    // Load some default resource (like the image for our cursor)
  VGUIManager::GlobalManager().LoadResourceFile("Dialogs\\MenuSystem.xml");

  // Load and Show the Main Menu
  spMainDlg = spGUIContext->ShowDialog("Dialogs\\MainMenu.xml");
  VASSERT(spMainDlg);
    
  //enables disable/signin-out buttons accoding to the player sign-in status
  AuthenticationChanged();

   
  //Get the instance of the cloud connection client
  CloudConnection* paccm = CloudConnection::GetInstance();
  VASSERT_MSG( paccm != NULL, "The Cloud Connection Module cannot be null" );
  CloudConnectionClient* pCClient = paccm->GetClient();   
  pCClient->GetAchievement( ACHIEVEMENT_ID );

}

void BasicGUI::Update() 
{
	if ( spMainDlg != NULL ) 
  {      
    //Get the instance of the cloud connection client
    CloudConnection* paccm = CloudConnection::GetInstance();
    VASSERT_MSG( paccm != NULL, "The Cloud Connection Module cannot be null" );
    CloudConnectionClient* pCClient = paccm->GetClient();

    //Get the result of the user input from the GUI
		const int result = spMainDlg->GetDialogResult();
		if ( result == VGUIManager::GetID("UserSignIn") ) 
    {
      //Shows the UI to sign-in the user if they are not already authenticated
      if ( pCClient->IsAuthenticated() == false ) 
      {              
        Vision::Message.Add(1, "BasicGUI - Begin User Initiated Sign-In Process");
        pCClient->BeginUserInitiatedSignIn();
      }       
      else
      {
        Vision::Message.Add(1, "BasicGUI - User is already signed in so we are not showing the sign-in UI");
        hkvLog::Debug("BasicGUI - User is already signed in so we are not showing the sign-in UI" );
      }

		} 
    else if ( result == VGUIManager::GetID("AllAchievements") ) 
    {
      //Shows all the acheivements for this game if the user is authenticated
      if ( pCClient->IsAuthenticated() ) 
      {
        pCClient->ShowAchievements();
      }
      else
      {
        hkvLog::Debug("BasicGUI - User is not signed in" );
        Vision::Message.Add(1, "BasicGUI - User is not signed in");
      }
		} 
    else if ( result == VGUIManager::GetID("UnlockAchievement") ) 
    {
      //Unlocks a single acheivement for this game if the user is authenticated
      if ( pCClient->IsAuthenticated() ) 
      {
        pCClient->UnlockAchievement( ACHIEVEMENT_ID );
        Vision::Message.Add(1, "BasicGUI - Request made to unlock Achievement 'CggI9__cunsQAhAB'");
      }
      else
      {
        hkvLog::Debug("BasicGUI - User is not signed in" );
        Vision::Message.Add(1, "BasicGUI - User is not signed in");
      }
		} 
    else if ( result == VGUIManager::GetID("AllLeaderboards") ) 
    {
      //Shows all the leaderboards for this game if the user is authenticated
      if ( pCClient->IsAuthenticated() ) 
      {
        pCClient->ShowLeaderboards();
      }
      else
      {
        hkvLog::Debug("BasicGUI - User is not signed in" );
        Vision::Message.Add(1, "BasicGUI - User is not signed in");
      }
		} 
    else if ( result == VGUIManager::GetID("SubmitScore") ) 
    {
      //Submits a score to the leaderboard if the user is authenticated
      if ( pCClient->IsAuthenticated() ) 
      {
        int highScore = 12345;
        pCClient->SubmitScore( LEADERBOARD_ID, highScore );
        Vision::Message.Add(1, "BasicGUI - A highscore was submitted to a leaderboard" );
      }
      else
      {
        hkvLog::Debug("BasicGUI - User is not signed in" );
        Vision::Message.Add(1, "BasicGUI - User is not signed in");
      }
		} 
    else if ( result == VGUIManager::GetID("SignOut") )     
    {      			            
      //signs the user out of cloud services if they are authenticated
      if ( pCClient->IsAuthenticated() ) 
      {
        hkvLog::Debug("BasicGUI - Signing user out");
        Vision::Message.Add(1, "BasicGUI - Signing user out");
        pCClient->SignOut();
      }
      else
      {
        hkvLog::Debug("BasicGUI - User is not signed in" );
        Vision::Message.Add(1, "BasicGUI - User is not signed in");
      }
		} 
    else if ( result != 0 ) 
    {
			VASSERT_MSG(!true, "unhandled message from BasicGUI")
		}

		spMainDlg->SetDialogResult(0);	//handled the result
	}
}

void BasicGUI::OnHandleCallback( IVisCallbackDataObject_cl* pData ) 
{    
  //Get the instance of the cloud connection client
  CloudConnection* paccm = CloudConnection::GetInstance();
  VASSERT_MSG( paccm != NULL, "The Cloud Connection Module cannot be null" );
  CloudConnectionClient* pCClient = paccm->GetClient();

  //Listen here for sign-in/sign-out callbacks
  hkvLog::Debug("BasicGUI - OnHandleCallback");      
  if( pData->m_pSender == &CloudConnection::Callbacks.OnAuthActionStarted )
  {
    hkvLog::Debug("BasicGUI - OnAuthActionStarted");
  }
  else if( pData->m_pSender==&CloudConnection::Callbacks.OnAuthActionFinished )
  {                
    hkvLog::Debug("BasicGUI - OnAuthActionFinished");

    if ( pCClient->IsAuthenticated() )
    {
      Vision::Message.Add(1, "BasicGUI - Authentication Finished - User is signed in" );
    }
    else
    {
      Vision::Message.Add(1, "BasicGUI - Authentication Finished - User is not authenticated" );
    }

    AuthenticationChanged();
  }
  else if( pData->m_pSender==&CloudConnection::Callbacks.OnPlayerDataFetched )
  {                
    hkvLog::Debug("BasicGUI - OnPlayerDataFetched");
     
    if ( pCClient->IsAuthenticated() )
    {
      Vision::Message.Add(1, "BasicGUI - Welcome User '%s'", pCClient->GetUserDisplayName() );
    }
  }
  else if( pData->m_pSender==&CloudConnection::Callbacks.OnAchievementFetched )
  {                
    hkvLog::Debug("Cloud Connection Plugin Callback - OnAchievementFetched");
    //The achievement data has been fetched from the online service        
    VASSERT_MSG(pData != NULL, "The Achievement data was null!!!" );
    CCAchievement* pAch = (CCAchievement*)pData;
    if ( pAch->Valid() )
    {
      //You have now retrieved your valid achivement and can access data from it such
      //as name, description, steps completed etc...             
      hkvLog::Debug("Achievement Id='%s'", pAch->Id() );
      hkvLog::Debug("Achievement Name='%s'", pAch->Name() );
      hkvLog::Debug("Achievement Desc='%s'", pAch->Description() );
      hkvLog::Debug("Achievement Type='%d'", pAch->Type() );
      hkvLog::Debug("Achievement State='%d'", pAch->State() );
      hkvLog::Debug("Achievement CurrentSteps='%d'", pAch->CurrentSteps() );
      hkvLog::Debug("Achievement TotalSteps='%d'", pAch->TotalSteps() );
      hkvLog::Debug("Achievement LastModified='%d'", pAch->LastModified() );
    }
  }
}

void BasicGUI::AuthenticationChanged()
{  
  if ( spMainDlg != NULL )
  {      
    //Get the instance of the cloud connection client
    CloudConnection* paccm = CloudConnection::GetInstance();
    VASSERT_MSG( paccm != NULL, "The Cloud Connection Module cannot be null" );
    CloudConnectionClient* pCClient = paccm->GetClient();     

    SetButtonStatus("SIGNIN", !pCClient->IsAuthenticated() );          
    SetButtonStatus("ALLACH", pCClient->IsAuthenticated() );        
    SetButtonStatus("UNLOCKACH", pCClient->IsAuthenticated() );
    SetButtonStatus("ALLLEAD", pCClient->IsAuthenticated() );
    SetButtonStatus("SUBMITSCORE", pCClient->IsAuthenticated() );
    SetButtonStatus("SIGNOUT", pCClient->IsAuthenticated() );
  }
}

void BasicGUI::SetButtonStatus(const char* buttonID, bool enabled )
{
  if ( spMainDlg != NULL )
  {      
        //find the text label to display the text in
	  VMenuItemCollection* items = &spMainDlg->Items();

    //enable the signout button if we are authenticated
	  VDlgControlBasePtr vdlg = items->FindItem( VGUIManager::GetID( buttonID ) );
	  VASSERT_MSG( vdlg != NULL, "The dialog does not have a label with ID '%s'", buttonID );
	  VPushButton* pButton = vstatic_cast<VPushButton*>(vdlg);      	//check this is a VPushButton and set enable/disable
	  pButton->SetEnabled( enabled ); 
  }
}
