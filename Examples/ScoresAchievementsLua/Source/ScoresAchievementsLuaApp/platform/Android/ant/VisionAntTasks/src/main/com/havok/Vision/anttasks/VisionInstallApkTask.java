/**
 * 
 */
package com.havok.Vision.anttasks;

import java.io.File;
import java.io.IOException;
import java.util.Vector;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import org.apache.tools.ant.BuildException;

/**
 * Task to install a .apk on an android device.
 * Not using the Google Android "install" target in their ANT script
 * because it waits forever if no devices are plugged into the system
 * then crashes if you do plug one in a later time.
 * @author Project Anarchy
 */
public class VisionInstallApkTask extends VisionBaseTask
{
  /** The default timeout to wait for the .apk installer to finish (in seconds) */
  private final static int DEFAULT_TIMEOUT = 1200;
  
  /** the list of devices to install onto */
  private Vector<Device> m_devices = null;
  /** The .apk file to be installed */
  private File m_apk = null;
  /** The timeout to wait for the .apk installer to finish (in seconds) */
  private Integer m_timeout = DEFAULT_TIMEOUT;

  
  /**
   * ANT Nested Element - Optional - names a device to install to  
   * @return The device that was created
   */
  public Device createDevice() 
  {
    //create the devices list if it has not been made already
    if ( m_devices == null )
    {
      m_devices = new Vector<Device>();
    }
    
    // add the device   
    Device device = new Device();
    m_devices.add(device);     
    return device;
  }
  
  /**
   * ANT Attribute - Required
   * @param apk The file name of the .apk file to be installed on the device(s)
   */
  public void setApk( File apk )
  {
    m_apk = apk;
  }
  
  /**
   * ANT Attribute - Optional - The timeout in seconds
   * @param timeout The time to wait for the adb process to finish in seconds
   */
  public void setTimeout( Integer timeout )
  {
    m_timeout = timeout;
  }
  
  /**
   * Check that the ANT Attributes are valid
   * @throws BuildException if any attributes are invalid
   */
  void checkANTAttributes() throws BuildException
  {
    if ( m_apk == null )
    {
      throw new BuildException("The apk file has not been specified");
    }
    else if ( m_apk.exists() == false )
    {
      throw new BuildException("The apk file '"+ m_apk.getPath() +"' does not exist.");
    }
    else if ( m_apk.isDirectory() )
    {
      throw new BuildException("The apk specified '"+ m_apk.getPath() +"' appears to be a folder, not a file.");
    }
    
    if ( m_devices != null )
    {
      if ( m_devices.size() == 0 )
      {
        throw new BuildException("You did not specify any devices to install to.");
      }
      
      for (Device device : m_devices)
      {
        if ( device.getName() == null )
        {
          throw new BuildException("The name of the device to install to cannot be null");
        }
        else if ( device.getName().trim().length() == 0 )
        {
          throw new BuildException("The name of the device to install to cannot be zero length");
        }
      }
    }  
    
    if ( m_timeout == null || m_timeout <= 0 )
    {
      m_timeout = DEFAULT_TIMEOUT;
    }
  }
  
  /* (non-Javadoc)
   * @see org.apache.tools.ant.Task#execute()
   */
  @Override
  public void execute() throws BuildException
  {
    checkANTAttributes();
    
    if (m_devices == null)
    {
      // no devices were specified so install to the first one we find
      try
      {
        String[] devices = connectedDevices();
        if (devices.length > 0)
        {
          installApk(m_apk.getPath(), devices[0]);
        }
        else
        {
          log("No devices found, skipping installation of the .apk file!");
        }
      } 
      catch (IOException e)
      {
        throw new BuildException(e);
      } 
      catch (SDKNotFoundException e)
      {
        throw new BuildException(e);
      }
    } 
    else if (m_devices != null)
    {
      // copy to the list of devices specified by the user in the ANT attributes   
      
      // get the device names as a string array
      String[] devicesStr = new String[m_devices.size()];
      int idx = 0;
      for (Device device : m_devices)
      {
        devicesStr[idx] = device.getName();
        idx++;
      }

      try
      {
        installApk(m_apk.getPath(), devicesStr);
      } 
      catch (SDKNotFoundException e)
      {
        throw new BuildException(e);
      }      
    }
  }
  
  /***
   * Install given apk to the default device. Accepts an optional comma
   * separated list of devices. If uninstall is True the apk will be uninstalled
   * from the devices before being installed. If uninstall is False the apk will
   * be reinstalled. Note If the install fails in this case it will
   * automatically be retried by uninstalling the apk first.
   * 
   * @throws SDKNotFoundException
   */
  private boolean installApk(String apkFile, String device) throws SDKNotFoundException
  {
    String[] devices = { device };
    return installApk(apkFile, devices);
  }

  /***
   * reInstalls given apk to the given devices. Accepts an optional comma
   * separated list of devices.
   * 
   * @throws SDKNotFoundException
   */
  private boolean installApk( String apkFile, String[] devices ) throws SDKNotFoundException
  {
    boolean result = true;

    log( "Installing '"+apkFile+"' on "+devices.length+" device(s)" );    
    for ( String device : devices )
    {
        log( "Installing the package '"+apkFile+"' on device '"+device+"'" );
        String[] cmd = {getAdbPath(), "-s", device, "install", "-r", apkFile};
            
                     
        ExecutorService executor = Executors.newSingleThreadExecutor();
        CallCmdProcInThread cmdProc = new CallCmdProcInThread(cmd);
        Future<Integer> future = executor.submit(cmdProc);
        
        try
        {
          future.get( m_timeout, TimeUnit.SECONDS );
        }
        catch( TimeoutException e )
        {
          cmdProc.kill();
          log("Terminated adb due to timeout!");
        } 
        catch (InterruptedException e)
        {
          cmdProc.kill();
          log("Terminated adb due to interrupted! :" + e.getMessage());
        } 
        catch (ExecutionException e)
        {
          cmdProc.kill();
          log("Terminated adb due to exception! :" + e.getMessage());
        }             
        
        executor.shutdownNow();
    }

    return result;
  }
}
