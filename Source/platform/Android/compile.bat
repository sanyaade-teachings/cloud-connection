mkdir classes
"%JDK_ROOT%\bin\javac.exe" -sourcepath src -d classes -classpath classes -classpath %ADTROOT%sdk\platforms\android-10\android.jar src\com\havok\Vision\*.java
PAUSE