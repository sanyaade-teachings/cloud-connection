# Project Anarchy Cloud Connection Plugin

This plugin for the [Project Anarchy game engine](http://www.projectanarchy.com) allows you to interact with the [Google Play Games services](https://developers.google.com/games/services/) on Android or iOS.

# Table of Contents
 - [Overview](#overview) 
 - [Requirements](#requirements)
 - [Configure Your Game Service](#configure-your-game-service) 
 - [Add Achievements and Leaderboards](#add-achievements-and-leaderboards)
 - [Plugin Installation](#plugin-installation)
 - [Using the Plugin](#using-the-plugin)
 - [Building for Android](#building-for-android)
 - [Buidling for iOS](#building-for-ios)

## Overview
The Project Anarchy Cloud Connection Plugin provides several clients to allow you to access the Google Play Games API using either a C++ or Lua interface. The plugin provides support for the following features of the Google Play Games API:

### Google Play Games Client (Android & iOS) 
* sign in
* sign out
* unlock/reveal/increment achievements
* submit scores to leaderboards
* show achievements
* show leaderboards
* get a specific achievement

### Dummy Client (Win32 / vForge)
This client performs no actions and creates no connections. It is used for testing and development. This will allow you to prototype code in Win32 & vForge before testing it out on either iOS or Android.
The Dummy Client attempts to maintain a signed-in/signed-out state and will try to perform authentication callbacks similar to what would be expected in a functional client.
Calls to methods in the client will output debug information to the Vision log file. 

## Requirements

### Project Anarchy
* Build 2014.1 or greater

### Android
* Android NDK r9d or greater (NDK previous to r9d will not work)
* [Apache Ant](http://ant.apache.org/) 1.8 or later
* Build	**MUST** be compiled with C++11 support ( -std=c++11 )
* Build **MUST** to be compiled with RTTI support ( -frtti )

### iOS
* Xcode version 5.0.1 or higher.
* A mobile device running iOS 6.0 or higher.


## Configure Your Game Service

To use the plugin, you must first [configure your 
game](https://developers.google.com/games/services/console/enabling) in the 
Google Play Developer Console. Follow the instructions on creating a client ID 
for Android and/or iOS (depending on what platforms you intend to deploy or game 
on). Be particularly careful when entering your package name and your 
certificate fingerprints, since mistakes on those screens can be difficult to 
recover from.

Please note the following pieces of information when creating your client IDs, 
as they will be necessary later:

**Android**

* Your package name (e.g. "com.example.awesomegame")
* Your application ID (e.g. 123456789012)

**iOS**

* Your bundle identifier (e.g. "com.example.AwesomeGame")
* Your application ID (e.g. 123456789012)*
* Your client ID (e.g. "46798138751-afwa4iejsfjskj.apps.googleusercontent.com")

_[*] The application ID is the number that Google Play Developer Console 
assigns to your project. Please note that is not the same as your Apple 
application ID._

**Note:** Do not forget to add your test accounts (the accounts with which you 
will try signing in) to the **Testing** section of the Developer Console, 
otherwise you will not be able to sign in to your game.

There is an excellect video here from Google that points out the [Top 7 Google Play game services setup mistakes](https://developers.google.com/live/shows/5936979195723776)

## Add Achievements and Leaderboards

Add 
[achievements](https://developers.google.com/games/services/common/concepts/achievements) 
and 
[leaderboards](https://developers.google.com/games/services/common/concepts/leaderboards) 
to your game in the Google Play Developer Console. For each achievement and 
leaderboard you configure, make sure to note the corresponding **achievement ID** or **leaderboard ID**, as those will be needed when making the API calls. 
Achievement and leaderboard IDs are alphanumeric strings (e.g. "Cgkx9eiuwi8_AQ").

## Plugin Installation

Please refer to one of the following readme files on how to install the plugin:

[Android Installation](README_Installation_Android.md)

[iOS Installation](README_Installation_iOS.md)

## Using the Plugin

## Initialisation

To initialise the plugin whether you wish to use it via C++ or Lua you must add the following code into your PluginMain.cpp

```C++

	#include "CloudConnectionBase.h"
	#include "com_havok_Vision_CloudConnectionLifeCycleSupport.inl"
	...
	
	// inside your OnInitEnginePlugin() method
  	VISION_PLUGIN_ENSURE_LOADED(CloudConnectionPlugin);  
	#if defined(_VISION_ANDROID)
  		StateManager::InitServices(AndroidApplication); //Set up platform intiialization of Google Play Services
		DummyJNIFunction();   //Dummy - don't let the compiler strip JNI functions for < Android 4.0
	#endif
```

**TODO - WHERE TO PUT THE GOOGLE APPLICATION ID ON ANDROID AND IOS**

## Getting Access to the Client

After initialisation a "Cloud Connection Client" is now available to either C++ or Lua script in the following manner from anywhere in your own code:

### C++
Make sure to include `CloudConnectionBase.h` in any file you wish to access the client.

```C++
	
	#include "CloudConnectionBase.h"
	...
	//Get the instance of the cloud connection client  
	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();
```

### Lua

Access to plugin is via the global "CloudConnection"

```Lua

	--Get the instance of the cloud connection client
	local ccClient = CloudConnection:GetClient()
```

## Sign-In

`BeginUserInitiatedSignIn` will show the required consent dialogs to Sign-In. If the user has already signed into the game in the past, this process will be silent and the user will not have to interact with any dialogs.

### C++

```C++
  
	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();
	pCClient->BeginUserInitiatedSignIn();
```

### Lua

```Lua

	local ccClient = CloudConnection:GetClient()
	ccClient:BeginUserInitiatedSignIn()
```

## Sign-Out

To sign the user out, use the `SignOut` method.
After signing out, no further API calls can be made until the user authenticates again.

### C++

```C++
  
	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();
	pCClient->SignOut();
```

### Lua

```Lua

	local ccClient = CloudConnection:GetClient()
	ccClient:SignOut()
```

## Checking Player Authentication

To check whether the player is currently authenticated use the `IsAuthenticated` method.
This will return true if the player is authenticated and calls to the API can be made.
Note: It is also possible to listen for changes to authentication by using callbacks.

### C++

```C++

	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();
	bool auth = pCClient->IsAuthenticated();
```
### Lua

```Lua

	local ccClient = CloudConnection:GetClient()
	local auth = ccClient:IsAuthenticated()
```


## Revealing/Unlocking an Achievement

To unlock or reveal an achievement use the `UnlockAchievement` or `RevealAchievement` methods.

These methods work with the Achievement state, if you are not familiar with the concept then please see the Google documentation on [Achievement State](https://developers.google.com/games/services/common/concepts/achievements#state)

### C++

Reveals a hidden Achievement to the player but does not reward it: 

```C++
  
	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();
	pCClient->RevealAchievement("Cfjewijawiu_QA"); 
```

Unlocks the Achievement that the player has successfully earned:

```C++
  
	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();
	pCClient->UnlockAchievement("Cfjewijawiu_QA"); 
```

### Lua

Reveals a hidden Achievement to the player but does not reward it: 

```Lua

	local ccClient = CloudConnection:GetClient()
	ccClient:RevealAchievement("Cfjewijawiu_QA")		
```

Unlocks the Achievement that the player has successfully earned:


```Lua

	local ccClient = CloudConnection:GetClient()
	ccClient:UnlockAchievement("Cfjewijawiu_QA")
```

## Incrementing an Achievement

To update an incremenatial Achievement use the `IncrementAchievement` or `SetAchievementStepsAtLeast` methods.

See the Google documentation on [Incremental Achievements](https://developers.google.com/games/services/common/concepts/achievements#incremental_achievements) if you not familiar with the concept.

### C++

Increments number of steps towards finishing the achievement by 89 steps: 

```C++
  
	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();
	//increments the achievement by 89 steps further
	pCClient->IncrementAchievement("Cfjewijawiu_QA", 89);	 
```

Sets the number of steps to towards finishing the achievement to at least 32 steps:

```C++
  
	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();
	//Sets the achievement to at least 32 steps
	pCClient->SetAchievementStepsAtLeast("Cfjewijawiu_QA", 32);	 
```

### Lua

Increments number of steps towards finishing the achievement by 89 steps:

```Lua

	local ccClient = CloudConnection:GetClient()
	--increments the achievement by 89 steps further
	ccClient:IncrementAchievement("Cfjewijawiu_QA", 89)		
```

Sets the number of steps to towards finishing the achievement to at least 32 steps:


```Lua

	local ccClient = CloudConnection:GetClient()
	--Sets the achievement to at least 32 steps
	ccClient:SetAchievementStepsAtLeast("Cfjewijawiu_QA", 32)		
```

## Submitting a Score to a Leaderboard

To submit a high score to a leaderboard use the `SubmitScore` methods.

Note that the platform and the server will automatically discard scores that are lower than the player's existing high score, so you can submit scores freely without any checks to test whether or not the score is greater than the player's existing score.

### C++

```C++
  
	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();

	//submit a high score of 1337 points to the leaderboard "Cfji293fjsie_QA" without metadata 
	pCClient->SubmitScore("Cfji293fjsie_QA", 1337);

	...

	//submit a high score of 1337 points to the leaderboard "Cfji293fjsie_QA" with metadata "stage3"
	pCClient->SubmitScore("Cfji293fjsie_QA", 1337, "stage3");
```

### Lua

```Lua

	local ccClient = CloudConnection:GetClient()

	--submit a high score of 1337 points to the leaderboard "Cfji293fjsie_QA" without metadata
	ccClient:SubmitScore("Cfji293fjsie_QA", 1337)

	...

	--submit a high score of 1337 points to the leaderboard "Cfji293fjsie_QA" with metadata "stage3"
	ccClient:SubmitScore("Cfji293fjsie_QA", 1337, "stage3")
```


## Showing the Achievements UI

To show the built-in UI for achievements use the `ShowAchievements` method.
This will show a standard UI appropriate for the look and feel of the platform (Android or iOS).

### C++

```C++
  
	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();
	pCClient->ShowAchievements();
```

### Lua

```Lua

	local ccClient = CloudConnection:GetClient()
	ccClient:ShowAchievements()
```

## Showing the Leaderboard UI

To show the built-in UI for all leaderboards use the `ShowLeaderboards` method.
This will show a standard UI appropriate for the look and feel of the platform (Android or iOS).

### C++

```C++
  
	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();
	pCClient->ShowLeaderboards();
```

### Lua

```Lua

	local ccClient = CloudConnection:GetClient()
	ccClient:ShowLeaderboards()
```

If you wish to show a particular leaderboard instead of all leaderboards, you use the `ShowLeaderboard` method and pass in the ID of the leaderboard you wish to show.

### C++

```C++
  
	...
	pCClient->ShowLeaderboard("Cfji293fjsie_QA");
```

### Lua

```Lua

	...
	ccClient:ShowLeaderboard("Cfji293fjsie_QA")
```

## Getting the Players Name

To get the signed-in players name from the client by use the `GetUserDisplayName` method.
This method will only return a valid value if the player data has been successfully retrieved from the on-line services. The player data is requested automatically by the plugin as soon as sign-in has finished successfully. However, the player data may not arrive in a timely manner (See the Callbacks section).

### C++

```C++
  
	CloudConnection* paccm = CloudConnection::GetInstance();  
	CloudConnectionClient* pCClient = paccm->GetClient();
	const char* displayName = pCClient->GetUserDisplayName();
```

### Lua

```Lua

	local ccClient = CloudConnection:GetClient()
  	local displayName = ccClient:GetUserDisplayName()
```

## Callbacks

### C++

The Cloud Connection Plugin provides several callbacks to C++.
You can listen for these via the Vision callback system in any class that extends from `IVisCallbackHandler_cl`.
See the Project Anarchy Programmers documentation section on `Engine.Callbacks` for more details on how to use the callback system.

The following callbacks are provided to C++

* CloudConnection::Callbacks.OnAuthActionStarted - called when a player sign-in has started  
* CloudConnection::Callbacks.OnAuthActionFinished - called when a player sign-in or sign-out has finished (successfully or unsuccessfully)
* CloudConnection::Callbacks.OnPlayerDataFetched - called when the signed-in player's data has been retrieved
* CloudConnection::Callbacks.OnAchievementFetchedCallback  - called when a single achievement has been succesfully fetched from the network


### Using C++ the callbacks

Register the callbacks you want to listen for:

```C++

	...
	//Listen for callbacks from the cloud connection plugin
	CloudConnection::Callbacks.OnAuthActionStarted += this;
	CloudConnection::Callbacks.OnAuthActionFinished += this;
	CloudConnection::Callbacks.OnPlayerDataFetched += this;
	CloudConnection::Callbacks.OnAchievementFetched += this;
	...
```

Handle the callbacks in your `OnHandleCallback` method:  
```C++

	void MyAwesomeGame::OnHandleCallback( IVisCallbackDataObject_cl* pData )  
	{    	 
	  if( pData->m_pSender == &CloudConnection::Callbacks.OnAuthActionStarted )
	  {
	    hkvLog::Debug("Cloud Connection Plugin Callback - OnAuthActionStarted");
		//The authorisation process has been started
	  }
	  else if( pData->m_pSender==&CloudConnection::Callbacks.OnAuthActionFinished )
	  {                
	    hkvLog::Debug("Cloud Connection Plugin Callback - OnAuthActionFinished");
		//The authorisation process has finished either successfully or unsuccessfully
	  }
	  else if( pData->m_pSender==&CloudConnection::Callbacks.OnPlayerDataFetched )
	  {                
	    hkvLog::Debug("Cloud Connection Plugin Callback - OnPlayerDataFetched");
		//The player data has been fetched from the online service
	  }
	  else if( pData->m_pSender==&CloudConnection::Callbacks.OnAchievementFetched )
	  {                
	    hkvLog::Debug("Cloud Connection Plugin Callback - OnAchievementFetched");
		//The achievement data has been fetched from the online service
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
```

De-Register the callbacks when you are disposing of your class:
```C++

	...
	//UnListen for callbacks from the cloud connection plugin
	CloudConnection::Callbacks.OnAuthActionStarted -= this;
	CloudConnection::Callbacks.OnAuthActionFinished -= this;
	CloudConnection::Callbacks.OnPlayerDataFetched -= this;
	CloudConnection::Callbacks.OnAchievementFetched -= this;
	...
```

### Lua

The following lua functions can be implemented to listen for callbacks

* OnAuthActionStarted - called when a player sign-in has started  
* OnAuthActionFinished - called when a player sign-in or sign-out has finished (successfully or unsuccessfully)
* OnPlayerDataFetched - called when the signed-in player's data has been retrieved
* OnAchievementFetched - called when valid data for the signed-in player from the `GetAchievement( id )` call has been retrieved

### Using Lua the callbacks

Call the `AddScriptCallbackListener` function in the script that you want to listen for the callbacks in.

```Lua

	function OnAfterSceneLoaded()  
  		-- adding listener for CloudConnection callbacks for to this script
  		local ccClient = CloudConnection:GetClient()
  		ccClient:AddScriptCallbackListener()
	end
```

You should remove the callback listeners when the script is unloaded using `RemoveScriptCallbackListener`

```Lua

	function OnBeforeSceneUnloaded()
	  
	  -- removing listener for CloudConnection callbacks for to this script
	  local ccClient = CloudConnection:GetClient()
	  ccClient:RemoveScriptCallbackListener()    
	end
```   

Implement the following Lua functions that will get called when CloudConnection events happen

```Lua

	--This callback is made to the script when the Cloud Connection
	--Client has started the authorisation process
	function OnAuthActionStarted()
	  ...
	end
	
	--This callback is made to the script when the Cloud Connection
	--Client has finsihed the authorisation process, either successfully or unsuccessfully
	function OnAuthActionFinished()
	  ...
	end
	
	--This callback is made to the script when the Cloud Connection
	--Client has retrieved the player data, this means that calls
	--to GetUserDisplayName() will now return a valid value
	function OnPlayerDataFetched()
	  ...
	end

	--This callback is made to the script when the Cloud Connection
	--Client has retrived achievement data via the GetAchievement( id ) call
	function OnAchievementFetched( id, name, description, achtype, achstate, totalsteps, currentsteps )
		...
	end
```


## Building for Android

When you are signing your APK file, please make sure that you are signing it with the correct certificate, that is, the one that corresponds to the SHA1 certificate fingerprint you entered in the Developer Console during the setup.

## Buidling for iOS

**TODO**

## Extending or Customising the Plugin

If you wish to extend this plugin for your own purposes or implement a connection to a another service that is not Google Games Services, you can do so in the following way.

Create your own class that extends from `CloudConnectionClient` - this class has several pure virtual functions that you must implement in your new class (such as `ShowAchievements` or `BeginUserInitiatedSignIn`).

Once you have your own class that implements the `CloudConnectionClient` then you should alter the static method `ClientFactory::CreateCloudConnectionClient()` to return an instance of your client under the correct circumstances e.g. only for Win32 platform. 

See `DummyClient` for an example of an implementation of `CloudConnectionClient` that performs no actions other than debug logging and callbacks.

## Known Issues

### Android

When compiling for Android you may see the warning `warning : command line option '-std=c++11' is valid for C++/ObjC++ but not for C [enabled by default]` - C++11 is required by the Google Native Games SDK and it is not used by the plugin itself.

`__LP64__` warnings when compiling with Android NDK r9d - [Please see this issue](https://code.google.com/p/android/issues/detail?id=69975) which is being resolved in a future release of the Android NDK

### All Platforms

`CCAchievemet::LastModified()` - This call returns invalid values for any Google Game Services, it appears this is not implemented by Google.






