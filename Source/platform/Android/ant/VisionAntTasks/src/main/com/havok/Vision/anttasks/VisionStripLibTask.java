/**
 * 
 */
package com.havok.Vision.anttasks;

import java.io.File;

import org.apache.tools.ant.BuildException;

/**
 * ANT Task to strip all symbols from the native library to reduce size and obfuscate file
 * @author Project Anarchy
 */
public class VisionStripLibTask extends VisionBaseTask
{
  /* This is the fully name of the processor architecture for the compiled native binary we are going to process */
  protected Architecture m_architecture = null;
  /** this is the library that we are going to process */
  protected File m_library = null;
  
  /** ANT Attribute - Required 
   * This is the fully name of the processor architecture for the compiled native binary we are going to process */
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
  
  /** ANT Attribute - Required 
   * This is the fully qualified path to the the compiled native binary we are going to strib of symbols */
  public void setLib( File lib )
  {
    m_library = lib;
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
    
    if ( m_library == null )
    {
      throw new BuildException("The 'Lib' attribute has not been set");
    }
    else if ( m_library.exists() == false )
    {
      throw new BuildException("The Lib +"+ m_library.getPath() +"' does not exist");
    }
    else if ( m_library.isDirectory() )
    {
      throw new BuildException("The Lib +"+ m_library.getPath() +"' appears to be a folder, not a file!");
    }
  }
  
  /**
   * ANT Task Entry point
   */
  @Override
  public void execute()
  {
    checkANTAttributes();    
    try
    {
      int retval = stripLib(m_architecture, m_library.getParent(), m_library.getName() );    
      if ( retval != 0 )
      {
        throw new BuildException("There was an error when stripping the native lib: " + retval);
      }
    } 
    catch (Exception e)
    {
      throw new BuildException("There was an error when stripping the native lib", e);
    }
  } 
}
