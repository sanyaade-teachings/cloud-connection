/**
 * 
 */
package com.havok.Vision.anttasks;

import java.io.File;
import java.io.IOException;

import org.apache.tools.ant.BuildException;

/**
 * - Copies the native library into a subfolder of the correct name for the archetecture
 * - pre-fixes the library name with "lib" if it doesn't have it already
 * - optionally can strip unneeded symbols from the lib
 * 
 * @author Project Anarchy
 */
public class VisionCopyLibTask extends VisionStripLibTask
{
  /** true to strip unneeded symbols after the lib has been copied */
  private boolean m_stripSymbols = true;
  /** The name of the folder to copy the lib into */
  private File m_toDir = null;

  /**
   * ANT attribute - Optional - defaults to true
   * @param strip true to strip symbols after the lib has been copied and renamed, false to leave as is
   */
  public void setStrip( boolean strip )
  {
    m_stripSymbols = strip;
  }
  
  /**
   * ANT attribute - required
   * The name of the folder to copy the lib into
   * The final output will be copied to ${todir}/${Arch.getSubFolderName}/xxxx.so
   * @param todir The directory to copy the 
   */
  public void setToDir( File todir )
  {    
    m_toDir = todir;
  }
  
  /*
   * (non-Javadoc)
   * @see com.havok.Vision.anttasks.VisionStripLibTask#checkANTAttributes()
   */
  @Override
  void checkANTAttributes() throws BuildException
  {
    super.checkANTAttributes();
    
    if ( m_toDir == null )
    {
      throw new BuildException("The 'ToDir' attribute has not been set");
    }
    else if ( m_toDir == null )
    {
      throw new BuildException("The 'ToDir' attribute '"+m_toDir.getPath()+"' is not a folder");
    } 
  }

  /*
   * (non-Javadoc)
   * @see com.havok.Vision.anttasks.VisionStripLibTask#execute()
   */
  @Override
  public void execute()
  {
    checkANTAttributes();
    
    //copy the lib into the folder specified, prefix with "lib" if not already
    String libName = m_library.getName();
    if ( libName.startsWith("lib") == false )
    {
      libName = "lib" + libName;
    }
    
    File libraryDestination = new File( getPath( m_toDir.getPath(), m_architecture.getSubFolderName(), libName ) );
    boolean exists = ensureDirsExist( libraryDestination );
    if ( exists )
    {
      try
      {
        copyFileUsingChannel( m_library, libraryDestination );
      } 
      catch (IOException e)
      {
        throw new BuildException("unable to copy the libary file", e);
      }
    }
    else
    {
      throw new BuildException("Couldn't make output folder for the library: '" + libraryDestination.getPath() + "'" );
    }
        
    //super call does the strip symbols if wanted
    if ( m_stripSymbols )
    {
      setLib(libraryDestination); //the library name and path has changed to reset it before calling the superclass
      super.execute();
    }       
  }
  
}
