package com.havok.Vision.anttasks;

import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.BuildFileTest;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

public class VisionCopyGdbserverTaskTest extends BuildFileTest
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
    configureProject(TASKDEFS_DIR + "VisionCopyGdbserverTask_test.xml");
  }

  /**
   * @throws java.lang.Exception
   */
  @After
  public void tearDown() throws Exception
  {
    executeTarget("cleanup");
  }

  /**
   * Test can successfully copy the gdbserver
   */
  @Test
  public void testCopyGdbserverArm()
  {
    executeTarget("copyGdbserverArm");
  }
  
  /**
   * Test can successfully copy the gdbserver
   */
  @Test
  public void testCopyGdbserverX86()
  {
    executeTarget("copyGdbserverX86");
  } 
  
  /**
   * Test when ToDir hasnt been specified
   */
  @Test
  public void testToDirNotSpecified()
  {
    boolean buildexception = false;
    try
    {
      executeTarget("testToDirNotSpecified");
    } 
    catch (BuildException e)
    {     
      buildexception = true;
    }
    
    assertTrue(buildexception);   
  }  
}
