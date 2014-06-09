package com.havok.Vision.anttasks;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.FileChannel;
import java.nio.charset.Charset;
import java.nio.charset.CharsetEncoder;

import org.apache.tools.ant.Task;

/**
 * Base for All Vision ANT Tasks
 * 
 * @author Project Anarchy
 */
public abstract class VisionBaseTask extends Task
{
  /** The Vision environment variable to the Android NDK Root */
  public final static String ENV_VAR_NDKROOT = "NDKROOT";
  /** The Vision environment variable to the Android SDK Root */
  public final static String ENV_VAR_SDKROOT = "ADTROOT";
  /** The Vision environment variable to the Android SDK Root (alternative) */
  public final static String ENV_VAR_SDKROOT2 = "ANDROID_SDK_ROOT";
  
  /** caches the NDK toolchain path for ARM */
  private static String _NDK_TOOLCHAIN_ARM = null;
  /** caches the NDK toolchain path for X86 */
  private static String _NDK_TOOLCHAIN_X86 = null;

  /** used to check path names are ascii */
  private static CharsetEncoder ASCII_ENCODER = Charset.forName("US-ASCII").newEncoder(); // or "ISO-8859-1" for ISO Latin 1
  
  /**
   * Processor Architecture x86, Arm ...
   */
  public enum Architecture
  {
    ARCH_ARM("armeabi-v7a"), 
    ARCH_X86("x86");
        
    private Architecture( String libFolder )
    {
      m_libFolder = libFolder;
    }
        
    /** the name of the sub-folder where the lib's for this arch will be stored in the jar 'armeabi-v7a' or 'x86'*/
    private String m_libFolder;
    
    /**
     * @return  the name of the sub-folder where the lib's for this arch will be stored in the jar 'armeabi-v7a' or 'x86'
     */
    public String getSubFolderName()
    {
      return m_libFolder;
    }
  }

  /**
   * Emulates the Java 1.7 functionality provided by 
   * <code>Path p4 = FileSystems.getDefault().getPath("/users/sally");</code>
   * @param dir The folders in the path to concatenate
   * @return The concatenated path
   */
  public static String getPath( String... dir )
  {
    String outputPath = "";
    for (int i = 0; i < dir.length; i++)
    {
      outputPath += dir[i];
      if ( i != dir.length-1 )  //don't append separator to the last entry
      {
        outputPath += File.separatorChar; 
      }
    }
    
    return outputPath;
  }
  
  /**
   * Returns the path to the android NDK if it can be found asserts otherwise.
   * 
   * @return The path to the Android NDK Root
   * @throws NullPointerException if the {@value #ENV_VAR_NDKROOT} environment variable was not found
   * @throws IllegalArgumentException if the {@value #ENV_VAR_NDKROOT} environment variable was zero length
   */
  public static String getNdkRoot()
  {
    String ndkroot = System.getenv(ENV_VAR_NDKROOT);
    if (ndkroot == null || ndkroot.length() == 0)
    {
      throw new NullPointerException("Couldn't find the '" + ENV_VAR_NDKROOT + "' environment variable");
    }
    return ndkroot;
  }

  /**
   * Returns the path to the android SDK if it can be found asserts otherwise.
   * 
   * @return The path to the Android SDK Root
   * @throws NullPointerException if the {@value #ENV_VAR_SDKROOT} environment variable was not found
   * @throws IllegalArgumentException if the {@value #ENV_VAR_SDKROOT} environment variable was zero length
   */
  public static String getSdkRoot()
  {
    String sdkroot = System.getenv(ENV_VAR_SDKROOT);
    if (sdkroot == null || sdkroot.length() == 0)
    {
      sdkroot = System.getProperty(ENV_VAR_SDKROOT2);
    }

    // check it
    if (sdkroot == null || sdkroot.length() == 0)
    {
      throw new NullPointerException("Couldn't find the '" + ENV_VAR_SDKROOT + "' environment variable");
    }

    return sdkroot;
  }
  
  /**
   * Retreive path to Android toolchain.
   * @param architecture (ARCH_ARM|ARCH_X86) - Android architecture
   * @return str
   * @throws SDKNotFoundException
  */
  public static String getAndroidNDKToolchainPath( Architecture architecture ) throws SDKNotFoundException
  {        
    String toolchain = null;
    
    if ( architecture == Architecture.ARCH_ARM )
    {
        if ( _NDK_TOOLCHAIN_ARM == null )
        {                                         
            String path_ndk_arm = getPath( getNdkRoot(),"toolchains", "arm-linux-androideabi-4.8","prebuilt","windows");
            File file_ndk_arm  = new File(path_ndk_arm);
            if ( file_ndk_arm.exists() == false )
            {
              path_ndk_arm = getPath( getNdkRoot(), "toolchains", "arm-linux-androideabi-4.8","prebuilt", "windows-x86_64");                            
            }
            
            file_ndk_arm  = new File(path_ndk_arm.toString());
            
            if ( file_ndk_arm.exists() == false )
            {
                throw new SDKNotFoundException("Was not able to locate ndk toolchain for Arm." +
                       " Ensure that NDKROOT is defined and equals the path of the android sdk." +
                       " NDK version r8d or later is required.");
            }
            
            _NDK_TOOLCHAIN_ARM = path_ndk_arm.toString();
        }
        
        toolchain = _NDK_TOOLCHAIN_ARM;
    }
    else if ( architecture == Architecture.ARCH_X86 )
    {
        if ( _NDK_TOOLCHAIN_X86 == null )
        {          
          String path_ndk_x86 = getPath( getNdkRoot(), "toolchains", "x86-4.8", "prebuilt", "windows");
          File file_ndk_x86  = new File(path_ndk_x86);
          
            if ( file_ndk_x86.exists() == false )
            {
              path_ndk_x86 = getPath( getNdkRoot(), "toolchains", "x86-4.8","prebuilt", "windows-x86_64");
              file_ndk_x86  = new File(path_ndk_x86);
            }
            
            if ( file_ndk_x86.exists() == false )
            {
                throw new SDKNotFoundException("Was not able to locate ndk toolchain for x86." + 
                       " Ensure that NDKROOT is defined and equals the path of the android sdk." +
                       " NDK version r8d or later is required.");
            }
            
            _NDK_TOOLCHAIN_X86 = path_ndk_x86;
        }
        
        toolchain = _NDK_TOOLCHAIN_X86;        
    }
    else
    {
      throw new IllegalArgumentException("Processor Architecture '" + architecture + "' is not supported");
    }
    
    return toolchain;
  }

  /**
   * Strip all symbols from the native library to reduce size and obfuscate file 
   * @param architecture arm or x86 native library type
   * @param binDir the folder where the library is located
   * @param soDisplayName The name of the library to be stripped
   * @return the value returned from the stripper command line process
   * @throws Exception 
   */ 
  public static int stripLib(Architecture architecture, String binDir, String soDisplayName ) throws Exception
  {
    System.out.println("Stripping the debug symbols to keep the size down...");
    
    String stripper = null;
    if ( architecture == Architecture.ARCH_X86 )
    {
        stripper = getPath(
            getAndroidNDKToolchainPath(Architecture.ARCH_X86), "bin", "i686-linux-android-strip");
    }
    else
    {
        stripper = getPath(
            getAndroidNDKToolchainPath(Architecture.ARCH_ARM), "bin", "arm-linux-androideabi-strip");
    }
        
    if ( stripper == null )
    {
      throw new NullPointerException("Was unable to locate an Arm or x86 path to the libary stripper tool");
    }
    
    String libToStripPath = getPath(binDir, soDisplayName);
    File libToStripFile = new File( libToStripPath.toString() );
    if ( libToStripFile.exists() == false )
    {
      throw new FileNotFoundException("The file '" + libToStripPath.toString() + "' was not found" );
    }
    
    //call the stripper
    String cmd = stripper + " --strip-unneeded " + libToStripPath.toString();
    return callCmd(cmd);
  }
  
  /**
   * Ensures that the folders in the path of the file all exist
   * @param file The path to file or folder that should all of it's parent folders created
   * @return true if all folders were create
   */
  public boolean ensureDirsExist(File file)
  {
    //make the dest folder(s)
    boolean madeFolders = false;
    if ( file.isDirectory() == false )
    {
      if ( file.getParentFile().exists() == false )
      {
        madeFolders = file.getParentFile().mkdirs();
      }
      else
      {
        madeFolders = true;
      }
    }
    else
    {
      if ( file.exists() == false )
      {
        madeFolders = file.mkdirs();
      }
      else
      {
        madeFolders = true;
      }
    }
    return madeFolders;
  }  
  
  /**
   * Copy file from source to dest
   * @param source
   * @param dest
   * @throws IOException
   */
  public static void copyFileUsingChannel(File source, File dest) throws IOException
  {
    FileChannel sourceChannel = null;
    FileChannel destChannel = null;
    try
    {
      sourceChannel = new FileInputStream(source).getChannel();
      destChannel = new FileOutputStream(dest).getChannel();
      destChannel.transferFrom(sourceChannel, 0, sourceChannel.size());
    } 
    finally
    {
      if ( sourceChannel != null )
      {
        sourceChannel.close();
      }
      
      if ( destChannel != null )
      {
        destChannel.close();
      }
    }
  }
  
  /**
   * Deep copy one folder to another (recursive)
   * @param src The source folder
   * @param dest The destination folder
   * @throws IOException
   */
  public static void copyFolder_r(File src, File dest) throws IOException
  {
    if (src.isDirectory())
    {
      // if directory not exists, create it
      if (!dest.exists())
      {
        dest.mkdir();
        System.out.println("Directory copied from " + src + "  to " + dest);
      }

      // list all the directory contents
      String files[] = src.list();
      for (String file : files)
      {
        // construct the src and dest file structure
        File srcFile = new File(src, file);
        File destFile = new File(dest, file);
        // recursive copy
        copyFolder_r(srcFile, destFile);
      }

    } else
    {
      // if file, then copy it
      // Use bytes stream to support all file types
      copyFileUsingChannel(src, dest);
      System.out.println("File copied from " + src + " to " + dest);
    }
  }  
  
  /**
   * Is a string pure ascii
   * @param v The string to be checked
   * @return true if the string is pure ascii
   */
  public static boolean isPureAscii(String v) 
  {
    return ASCII_ENCODER.canEncode(v);
  }
  
  /*
  def getBinDir(options=None, makingFatApk=False):
    """
    Return the path where apk binaries will be/are stored.
    """
    if options:
        tempDir = getTempDir(options.arch, makingFatApk=makingFatApk)
        binDir = os.path.join(tempDir, "bin", "lib", options.arch)
    else:
        tempDir = getTempDir("armeabi-v7a", makingFatApk=makingFatApk)
        binDir = os.path.join(tempDir, "bin", "lib", "armeabi-v7a")
    return binDir
        */
  
  /**
   * Exectutes a command line program
   * @param cmd The command line to execute
   * @return The return value from the process, 0 == success
   * @throws Exception if any errors occured while executing the command
   */
  public static int callCmd( String cmd ) throws Exception
  {
    Runtime rt = Runtime.getRuntime();
    Process pr = rt.exec(cmd);
    int retval = pr.waitFor();
    if ( retval != 0 )
    {
      //abnormal ternimation
      throw new Exception(" Error while executing the command: '" + cmd + "'");
    }
    return retval;
  }
}