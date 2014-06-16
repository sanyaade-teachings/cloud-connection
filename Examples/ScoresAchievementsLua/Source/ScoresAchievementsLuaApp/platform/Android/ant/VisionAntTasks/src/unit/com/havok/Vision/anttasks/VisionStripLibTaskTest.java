/**
 * 
 */
package com.havok.Vision.anttasks;


import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.BuildFileTest;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

/**
 * @author Project Anarchy
 *
 */
public class VisionStripLibTaskTest extends BuildFileTest
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
    configureProject(TASKDEFS_DIR + "VisionStripLibTask_test.xml");
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
   * Test can successfully strip an arm library
   */
  @Test
  public void testStripArmLib()
  {
    executeTarget("stripArmLib");
  }
  
  /**
   * Test when lib file doesn't exist
   */
  @Test
  public void testLibFileDoesntExist()
  {
    boolean buildexception = false;
    try
    {
      executeTarget("libFileDoesntExist");
    } 
    catch (BuildException e)
    {     
      buildexception = true;
    }
    
    assertTrue(buildexception);   
  }
  
  /**
   * Test when lib is arm but x86 parameter was given in arch
   */
  @Test
  public void testStripArmLibUsingx86Parameter()
  {
    boolean buildexception = false;
    try
    {
      executeTarget("stripArmLibUsingx86Parameter");
    } 
    catch (BuildException e)
    {     
      buildexception = true;
    }
    
    assertTrue(buildexception);   
  }
  
  
}
