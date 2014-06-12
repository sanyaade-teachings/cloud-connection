REM Runs the Android build for java source files

REM Build in release mode
REM call ant release

REM Build in debug mode
ECHO %1
ECHO %2
ECHO %3
ECHO %4
ECHO %5
SET ANDROID_HOME=%ADTROOT%\sdk
cd .\Platform\Android
ant debug -D%1=%2 -D%3=%4 -D%5=%6
