REM Cleans the Android buil
REM This file is designed to be called as a post build event in Visual Studio
SET ANDROID_HOME=%ADTROOT%\sdk

REM Make sure the adb daemon is started or it can cause the ANT script to pause inside visual studio
%ANDROID_HOME%\platform-tools\adb.exe start-server

REM Clean the build
cd .\Platform\Android
ant clean