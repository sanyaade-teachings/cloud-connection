/**
 * 
 */
package com.havok.Vision.anttasks;

import static org.junit.Assert.*;

import java.io.File;
import java.io.IOException;

import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.BuildFileTest;
import org.apache.tools.ant.types.FileSet;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

/**
 * Unit Tests for {@link VisionBaseTask}
 * @author Project Anarchy
 */
public class VisionCopyAssetsTaskTest extends BuildFileTest
{  
  private final static String TASKDEFS_DIR = "src/unittestdata/xml/";
    
  /**
   * @throws java.lang.Exception
   */
  @BeforeClass
  public static void setUpBeforeClass() throws Exception
  {
  }

  /**
   * @throws java.lang.Exception
   */
  @AfterClass
  public static void tearDownAfterClass() throws Exception
  {
  }

  /**
   * @throws java.lang.Exception
   */
  @Before
  public void setUp() throws Exception
  {
    configureProject(TASKDEFS_DIR + "VisionCopyAssetsTask_test.xml");
  }

  /**
   * @throws java.lang.Exception
   */
  @After
  public void tearDown() throws Exception
  {
    executeTarget("cleanup");
  }
  
  @Test
  public void testCopyManagedResources()
  {
    executeTarget("copyManagedResources");
  }
  
  @Test
  public void testCopyManagedBaseResources() throws IOException
  {
    executeTarget("copyManagedBaseResources");
    
    File GLES2file = new File(TASKDEFS_DIR + "..\\toAssetTest\\copyManagedBaseResources\\S\\FFS.Shaderbin\\GLES2.vShaderBin");
    File DX9file = new File(TASKDEFS_DIR + "..\\toAssetTest\\copyManagedBaseResources\\S\\FFS.Shaderbin\\DX9.vShaderBin");
    
    assertTrue( "The GLES2File '"+ GLES2file.getCanonicalPath() +"' was not copied", GLES2file.exists() );
    assertFalse( "The DX9file '"+ DX9file.getCanonicalPath() +"' was copied and is not needed", DX9file.exists() );
    
  }

  /**
   * Test method for {@link com.havok.Vision.anttasks.VisionCopyAssetsTask#execute()}.
   */
  @Test
  public void testCopyUnManagedResources()
  {
    executeTarget("copyUnManagedResources");
  }
  
  /**
   * Test method for {@link com.havok.Vision.anttasks.VisionCopyAssetsTask#setProfileName(java.lang.String)}.
   */
  @Test ( expected = BuildException.class )
  public void testNoDestinationPathSet()
  {
    boolean buildexception = false;
    try
    {
      executeTarget("noDestinationPathSet");
    } 
    catch (BuildException e)
    {     
      buildexception = true;
    }
    
    assertTrue(buildexception);    
  }

  /**
   * Test method for {@link com.havok.Vision.anttasks.VisionCopyAssetsTask#setSourcePath(java.lang.String)}.
   */
  @Test (expected = BuildException.class )
  public void testInvalidSourcePathSet()
  {
    boolean buildexception = false;
    try
    {
      executeTarget("invalidSourcePathSet");
    } 
    catch (BuildException e)
    {     
      buildexception = true;
    }
    
    assertTrue(buildexception);  
  }
}
