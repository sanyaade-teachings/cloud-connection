/**
 * 
 */
package com.havok.Vision.anttasks;

import static org.junit.Assert.*;

import java.io.FileNotFoundException;
import java.io.IOException;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

/**
 * Unit Tests for {@link AssetTable}
 * @author Project Anarchy
 */
public class AssetTableTest
{

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
  }

  /**
   * @throws java.lang.Exception
   */
  @After
  public void tearDown() throws Exception
  {
  }

  /**
   * Test method for {@link com.havok.Vision.anttasks.AssetTable#AssetTable(java.lang.String)}.
   * @throws IOException 
   */
  @Test (expected = FileNotFoundException.class )
  public void testAssetTable_InvalidFile() throws IOException
  {
    AssetTable at = new AssetTable("c:\\invalidfile.txt");
    assertNotNull( "The Asset table was null", at );
  }

  /**
   * Test method for {@link com.havok.Vision.anttasks.AssetTable#AssetTable(java.lang.String)}.
   * @throws IOException 
   */
  @Test
  public void testAssetTable_ValidFile() throws IOException
  {
    AssetTable at = new AssetTable("src\\unittestdata\\fromAssetTest\\AssetMgmt_data\\android.aidlt");
    assertNotNull( "The Asset table was null", at );
    assertEquals( "The number of entries in the table is not correct", 307, at.getNumberOfEntries() );
  }
  
  /**
   * Test method for {@link com.havok.Vision.anttasks.AssetTable#hasAssetInLookupTable(java.lang.String)}.
   * @throws IOException 
   */
  @Test
  public void testHasAssetInLookupTable() throws IOException
  {
    AssetTable at = new AssetTable("src\\unittestdata\\fromAssetTest\\AssetMgmt_data\\android.aidlt");
    assertFalse( at.hasAssetInLookupTable("notinthetable.png") );
    assertTrue( at.hasAssetInLookupTable("src/unittestdata/fromassettest/dialogs/checkmark_off.png") );    
  }

  /**
   * Test method for {@link com.havok.Vision.anttasks.AssetTable#hasTransformedAssetInLookupTable(java.lang.String)}.
   * @throws IOException 
   */
  @Test
  public void testHasTransformedAssetInLookupTable() throws IOException
  {
    AssetTable at = new AssetTable("src\\unittestdata\\fromAssetTest\\AssetMgmt_data\\android.aidlt");
    assertTrue( at.hasAssetInLookupTable("src/unittestdata/fromassettest/dialogs/gametitle.png") );
    assertFalse( at.hasAssetInLookupTable("src/unittestdata/fromassettest/fonts/gilgongo_large_00.dds") );
  }

}
