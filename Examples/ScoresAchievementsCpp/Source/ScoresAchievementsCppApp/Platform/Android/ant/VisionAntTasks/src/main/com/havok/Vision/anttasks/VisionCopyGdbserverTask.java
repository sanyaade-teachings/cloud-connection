/**
 * 
 */
package com.havok.Vision.anttasks;

import java.io.File;
import java.io.IOException;

import org.apache.tools.ant.BuildException;

/**
 * Copies the gdbserver so that native code can be remotely debugged
 * @author Project Anarchy
 */
public class VisionCopyGdbserverTask extends VisionBaseTask
{
  /* This is the name of the processor architecture that we need to copy the gdbserver for */
  protected Architecture m_architecture = null;
  /** The name of the folder to copy gdbserver into */
  private File m_toDir = null;
  
  /** ANT Attribute - Required 
   * This is the name of the processor architecture that we need to copy the gdbserver for */
  public void setArch( String architecture )
  {
    if ( architecture.contains("x86") )
    {
      m_architecture = Architecture.ARCH_X86;
    }
    else
    {
      m_architecture = Architecture.ARCH_ARM;
    }
  }
  
  /**
   * ANT attribute - required
   * The name of the folder to copy gdbserver into
   * The final output will be copied to ${todir}/${Arch.getSubFolderName}/gdbserver
   * @param todir The directory to copy the gdbserver to
   */
  public void setToDir( File todir )
  {    
    m_toDir = todir;
  }
  
  /**
   * Check that the ANT Attributes are valid
   * @throws BuildException if any attributes are invalid
   */
  void checkANTAttributes() throws BuildException
  {
    if ( m_architecture == null )
    {
      throw new BuildException("The 'Arch' attribute has not been set, use 'x86' or 'arm'");
    }
    
    if ( m_toDir == null )
    {
      throw new BuildException("The 'ToDir' attribute has not been set");
    }
    else if ( m_toDir == null )
    {
      throw new BuildException("The 'ToDir' attribute '"+m_toDir.getPath()+"' is not a folder");
    } 
  }

  /* (non-Javadoc)
   * @see org.apache.tools.ant.Task#execute()
   */
  @Override
  public void execute() throws BuildException
  {
    checkANTAttributes();
    
    String archFolder = null;
    if ( m_architecture == Architecture.ARCH_X86 )
    {
      archFolder = "android-x86";
    }
    else
    {
      archFolder = "android-arm";
    }
    
    String gdbserverSource = getPath(getNdkRoot(), "prebuilt", archFolder, "gdbserver", "gdbserver");     
    File gdbserverDest = new File( getPath( m_toDir.getPath(), m_architecture.getSubFolderName(), "gdbserver" ) );
    boolean exists = ensureDirsExist( gdbserverDest );
    if ( exists )
    {
      try
      {
        copyFileUsingChannel( new File(gdbserverSource), gdbserverDest );
      } 
      catch (IOException e)
      {
        throw new BuildException("unable to copy the gdbserver file", e);
      }
    }
    else
    {
      throw new BuildException("Couldn't make output folder for the gdbserver: '" + gdbserverDest.getPath() + "'" );
    }    
  }
}
