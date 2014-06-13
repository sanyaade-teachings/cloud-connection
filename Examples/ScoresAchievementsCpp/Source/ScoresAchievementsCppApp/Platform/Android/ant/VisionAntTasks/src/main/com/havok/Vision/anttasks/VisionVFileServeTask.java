/**
 * 
 */
package com.havok.Vision.anttasks;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.net.Inet4Address;
import java.util.Vector;

import org.apache.tools.ant.BuildException;

/**
 * Task to create the vFileServe.txt file and then install it onto an Android device or devices
 * @author Project Anarchy
 */
public class VisionVFileServeTask extends VisionBaseTask
{
  /**
   * Represents a nested element that is the name of a device to copy to
   * @author Project Anarchy
   */
  public class Device
  {                                           
      String m_name;
      /**
       * ANT Attribute - required
       * @param name The name of the device
       */
      public void setName(String name) { m_name = name; }
      public String getName() { return m_name; }
  }
  
  /** The name of the file serve config file to create */
  private final static String VFILESERVECONFIG = "vFileServeHost.txt";
  /** The default vForge port used for file transfer */
  private final static int DEFAULT_PORT = 4225;
  
  /** the network address of the host where we are loading from */  
  private String m_ip = null;  
  /** the network port on the host where we are loading from */ 
  private int m_port = DEFAULT_PORT;
  /** the list of devices to copy the vFileServe.txt onto */
  private Vector<Device> m_devices = null;                                  
  
  /**
   * ANT Attribute - Optional - defaults to {@value #DEFAULT_PORT} 
   * @param port The port that the files should be loaded from
   */
  public void setPort(int port)
  {
    m_port = port;
  }

  /**
   * ANT Attribute - Optional - defaults to value picked from the host 
   * @param ip The network IP address of the host machine
   */
  public void setIP(String ip)
  {
    m_ip = ip;
  }  
  
  /**
   * ANT Nested Element - Option - names a device 
   * @return
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
   * Check that the ANT Attributes are valid
   * @throws BuildException if any attributes are invalid
   */
  void checkANTAttributes() throws BuildException
  {
    if ( m_devices != null )
    {
      if ( m_devices.size() == 0 )
      {
        throw new BuildException("You did not specify any devices to copy to.");
      }
      
      for (Device device : m_devices)
      {
        if ( device.getName() == null )
        {
          throw new BuildException("The name of the device cannot be null");
        }
        else if ( device.getName().trim().length() == 0 )
        {
          throw new BuildException("The name of the device cannot be zero length");
        }
      }
    }    
  }
  
  /*
   * (non-Javadoc)
   * @see org.apache.tools.ant.Task#execute()
   */
  @Override
  public void execute() throws BuildException
  {
    checkANTAttributes();
    
    if (m_devices == null)
    {
      // no devices were specified so copy to the first one we find
      try
      {
        String[] devices = connectedDevices();
        if (devices.length > 0)
        {
          createAndCopyConfig(devices[0]);
        }
        else
        {
          log("No devices found, not coping the vFileServe config to any devices!");
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

      createAndCopyConfig(devicesStr);
    }
  }
  
  /**
   * 
   * @return true if successful, false if failed 
   */
  private boolean createAndCopyConfig( String device )
  {
    String[] defaultdevice = {device};
    return createAndCopyConfig( defaultdevice );
  }
  
  /**
   * 
   * @param devices
   * @return true if successful, false if failed 
   */
  private boolean createAndCopyConfig( String[] devices )
  {
    log( "Configure for vFileServe" );
    String configDest = "/mnt/sdcard/" + VFILESERVECONFIG;    
    // allow vFileServer.txt create to fail, as could be read only when on a system with > 1 IP
    // (connected to a VPN etc).
    try
    {
      //create the vFileServe file
      if ( m_ip == null )
      {
        //get the system ip if one was not specified
        m_ip = Inet4Address.getLocalHost().getHostAddress();
      }
      
      final FileOutputStream fout = new FileOutputStream( new File(VFILESERVECONFIG) );
      final PrintStream printStream = new PrintStream(fout);
      printStream.print( m_ip + ":" + m_port);
      log("Wrote IP addr of ["+m_ip+":"+m_port+"]" );
      printStream.close();
      fout.close();
    }
    catch ( Throwable e )
    {
      throw new BuildException("Could not write to vFileServeHost.txt. Is it read only?", e);        
    }
    finally
    {
        //copy the created file to the device
        try
        {
            String[] failedDevices = copyToDevice(VFILESERVECONFIG, configDest, devices);
            if ( failedDevices.length > 0 )
            {
                log( "'There were copy errors for the next devices. Aborting process..." );
                for (String device : failedDevices)
                {
                  log( "Device: " + device );
                }
                return false;
            }
                    
            log( "vFileServeHost copied" );
        }
        catch ( Throwable e )
        {
            throw new BuildException( e.getMessage() + "\nvFileServeHost failed to copy to the SD card. Does the device have one?", e );
        }
    }
    
    return true;
  }

}
