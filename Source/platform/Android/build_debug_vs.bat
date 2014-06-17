REM Runs the Android build for java source files
REM This file is designed to be called as a post build event in Visual Studio
SET ANDROID_HOME=%ADTROOT%\sdk

REM Make sure the adb daemon is started or it can cause the ANT script to pause inside visual studio
%ANDROID_HOME%\platform-tools\adb.exe start-server

REM Build and install in debug mode
cd .\Platform\Android
ant debug -D%1=%2 -D%3=%4 -D%5=%6
