REM Cleans the Android buil
REM This file is designed to be called as a post build event in Visual Studio
SET ANDROID_HOME=%ADTROOT%\sdk
cd .\Platform\Android

REM Clean the build
ant clean