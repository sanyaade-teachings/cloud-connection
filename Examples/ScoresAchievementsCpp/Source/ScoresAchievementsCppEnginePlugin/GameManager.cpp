/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include "ScoresAchievementsCppEnginePluginPCH.h"
#include "GameManager.h"

// Cloud Connection Plugin Includes - Start
#include "CloudConnectionBase.h"
#include "CloudConnectionGui.hpp"
// Cloud Connection Plugin Includes - End

// one global static instance
MyGameManager MyGameManager::g_GameManager;

void MyGameManager::OneTimeInit()
{
  m_bPlayingTheGame = false;

  // the game manager should listen to the following callbacks:
  Vision::Callbacks.OnEditorModeChanged += this;
  Vision::Callbacks.OnBeforeSceneLoaded += this;
  Vision::Callbacks.OnAfterSceneLoaded += this;
  Vision::Callbacks.OnUpdateSceneBegin += this;
  Vision::Callbacks.OnWorldDeInit += this;

    
  //Create a GUI with all the functionality to show off the cloud connection
  m_pCloudConnectionGUI = new CloudConnectionGUI();
  m_pCloudConnectionGUI->InitGUI();
}

void MyGameManager::OneTimeDeInit()
{
  Vision::Callbacks.OnEditorModeChanged -= this;
  Vision::Callbacks.OnBeforeSceneLoaded -= this;
  Vision::Callbacks.OnAfterSceneLoaded -= this;
  Vision::Callbacks.OnUpdateSceneBegin -= this;
  Vision::Callbacks.OnWorldDeInit -= this;
   
  //destroy the cloud connection GUI
  if ( m_pCloudConnectionGUI != NULL )
  {
    m_pCloudConnectionGUI->DeinitGUI();
  }
}



void MyGameManager::OnHandleCallback(IVisCallbackDataObject_cl *pData)
{

  if (pData->m_pSender==&Vision::Callbacks.OnUpdateSceneBegin)
  {
      //This callback will be triggered at the beginning of every frame
      //You can add your own per frame logic here
      // [...]
      if (m_bPlayingTheGame)
      {
        Vision::Message.Print(1, 200, 100, "The game is running");
      }
      
      //update the cloud connection GUI
      if ( m_pCloudConnectionGUI != NULL )  
      {
        m_pCloudConnectionGUI->Update();
      }

      return;
  }

  if (pData->m_pSender==&Vision::Callbacks.OnEditorModeChanged)
  {
    // when vForge switches back from EDITORMODE_PLAYING_IN_GAME, turn off our play the game mode
    if (((VisEditorModeChangedDataObject_cl *)pData)->m_eNewMode != VisEditorManager_cl::EDITORMODE_PLAYING_IN_GAME)
      SetPlayTheGame(false);
    return;
  }

  if (pData->m_pSender==&Vision::Callbacks.OnBeforeSceneLoaded)
  {
    //here you can add you specific code before the scene is loaded
    return;
  }

  if (pData->m_pSender==&Vision::Callbacks.OnAfterSceneLoaded)
  {
    //gets triggered when the play-the-game vForge is started or outside vForge after loading the scene
    if (Vision::Editor.IsPlayingTheGame()) 
      SetPlayTheGame(true);
    
    //Show the cloud connection GUI straight away
    if ( m_pCloudConnectionGUI != NULL )  
    {
      m_pCloudConnectionGUI->ShowGUI();
    }

    return;
  }

  if (pData->m_pSender==&Vision::Callbacks.OnWorldDeInit) 
  {
     // this is important when running outside vForge
    SetPlayTheGame(false);
    return;
  }
}


// switch to play-the-game mode
void MyGameManager::SetPlayTheGame(bool bStatus)
{
  if (m_bPlayingTheGame==bStatus)
    return;

  m_bPlayingTheGame = bStatus;

  if (m_bPlayingTheGame)
  {
     // Play the game mode is started
     Vision::Message.Add(1, "Play the game mode has been started");
  } 
  else
  {
    //the play the game mode has been stopped.
    //clean up all your game specific instances, like e.g. particle effects
    //VisParticleGroupManager_cl::GlobalManager().Instances().Purge();
  }
}

/*
 * Havok SDK - Base file, BUILD(#20140611)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2014
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available from salesteam@havok.com.
 * 
 */
