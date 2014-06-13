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
 * Unit Tests for {@link VisionInstallApkTask}
 * @author Project Anarchy
 */
public class VisionInstallApkTaskTest extends BuildFileTest
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
    configureProject(TASKDEFS_DIR + "VisionInstallApkTask_test.xml");
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
  public void testNoParameters()
  {    
    boolean buildexception = false;
    try
    {
      executeTarget("noParameters");
    } 
    catch (BuildException e)
    {     
      buildexception = true;
    }
    
    assertTrue(buildexception);     
  }
  
  @Test
  public void testApkDoesNotExist()
  {       
    boolean buildexception = false;
    try
    {
      executeTarget("apkDoesNotExist");
    } 
    catch (BuildException e)
    {     
      buildexception = true;
    }
    
    assertTrue(buildexception); 
  }
  
  @Test
  public void testApkDoesExist()
  {       
     executeTarget("apkDoesExist");
  }
  
  @Test
  public void testDeviceDoesNotExist()
  {       
     executeTarget("deviceDoesNotExist");
  }
  
  @Test
  public void testDeviceDoesExist()
  {       
     executeTarget("deviceDoesExist");
  }
}
