REM Runs the Android build for java source files
REM This file is designed to be called as a post build event in Visual Studio
SET ANDROID_HOME=%ADTROOT%\sdk
cd .\Platform\Android

REM Build in release mode
ant release -D%1=%2 -D%3=%4 -D%5=%6