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
public class VisionVFileServeTaskTest extends BuildFileTest
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
    configureProject(TASKDEFS_DIR + "VisionVFileServeTask_test.xml");
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
    executeTarget("noParameters");
  }
  
  @Test
  public void testSingleDeviceNamed()
  {
    executeTarget("singleDeviceNamed");
  }  
  
  @Test
  public void testInvalidDeviceNamed()
  {       
     executeTarget("invalidDeviceNamed");
  } 
  
  @Test
  public void testSpecifyIP()
  {
    executeTarget("specifyIP");
  }  
  
  @Test
  public void testSpecifyIPandPort()
  {
    executeTarget("specifyIPandPort");
  }
}
