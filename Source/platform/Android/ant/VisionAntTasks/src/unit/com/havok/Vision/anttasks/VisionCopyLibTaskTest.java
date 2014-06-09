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
 * unit tests for {@link VisionCopyAssetsTask}
 * @author Project Anarchy
 */
public class VisionCopyLibTaskTest extends BuildFileTest
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
    configureProject(TASKDEFS_DIR + "VisionCopyLibTask_test.xml");
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
}
