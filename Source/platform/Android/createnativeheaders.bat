mkdir jni
"%JDK_ROOT%\bin\javah.exe" -d jni -classpath ./classes;%ADTROOT%sdk\platforms\android-10\android.jar com.havok.Vision.CloudConnectionLifeCycleSupport
PAUSE