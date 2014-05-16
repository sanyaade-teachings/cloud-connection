mkdir jni
"%JDK_ROOT%\bin\javah.exe" -d ../../  -classpath ./bin/classes;%ADTROOT%sdk\platforms\android-10\android.jar com.havok.Vision.CloudConnectionLifeCycleSupport
PAUSE