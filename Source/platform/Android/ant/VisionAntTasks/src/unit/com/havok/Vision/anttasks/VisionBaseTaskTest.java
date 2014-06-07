package com.havok.Vision.anttasks;

import static org.junit.Assert.*;

import java.io.File;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import com.havok.Vision.anttasks.VisionBaseTask.Architecture;

public class VisionBaseTaskTest
{

  @BeforeClass
  public static void setUpBeforeClass() throws Exception
  {
  }

  @AfterClass
  public static void tearDownAfterClass() throws Exception
  {
  }

  @Before
  public void setUp() throws Exception
  {
  }

  @After
  public void tearDown() throws Exception
  {
  }
  
  @Test
  public void testGetPath()
  {
    String path = VisionBaseTask.getPath("c:\\testfolder", "folder1", "folder2", "filename.txt" );    
    assertTrue( path + " is invalid", path.startsWith("c:\\testfolder") );
    assertTrue( path + " is invalid", path.endsWith("\\filename.txt") );
    assertTrue( path + " is invalid", path.compareTo("c:\\testfolder\\folder1\\folder2\\filename.txt") == 0 );
  }

  @Test
  public void testGetNdkRoot()
  {
    String ndkroot = VisionBaseTask.getNdkRoot();    
    assertTrue( ndkroot + " is invalid", ndkroot.contains("ndk") );
  }
  

  @Test
  public void testGetSdkRoot()
  {
    String sdkroot = VisionBaseTask.getSdkRoot();    
    assertTrue( sdkroot + " is invalid", sdkroot.contains("adt") );
  }

  @Test
  public void testGetAndroidNDKToolchainPath_Arm() throws SDKNotFoundException
  {
    String ndkroot = VisionBaseTask.getNdkRoot();
    String ndk_arm_path = VisionBaseTask.getAndroidNDKToolchainPath( Architecture.ARCH_ARM );
    
    assertTrue( ndk_arm_path + " is null", ndk_arm_path != null );
    assertTrue( ndk_arm_path + " is zero length", ndk_arm_path.length() > 0 );
    assertTrue( ndk_arm_path + " is not in the NDK root", ndk_arm_path.startsWith(ndkroot) );
    assertTrue( ndk_arm_path + " is doesn't look like an arm path", ndk_arm_path.contains("arm") );
    assertTrue( ndk_arm_path + " doesnt not exist", new File(ndk_arm_path).exists() );
  }
  
  @Test
  public void testGetAndroidNDKToolchainPath_x86() throws SDKNotFoundException
  {
    String ndkroot = VisionBaseTask.getNdkRoot();
    String ndk_x86_path = VisionBaseTask.getAndroidNDKToolchainPath( Architecture.ARCH_X86 );
    
    assertTrue( ndk_x86_path + " is null", ndk_x86_path != null );
    assertTrue( ndk_x86_path + " is zero length", ndk_x86_path.length() > 0 );
    assertTrue( ndk_x86_path + " is not in the NDK root", ndk_x86_path.startsWith(ndkroot) );
    assertTrue( ndk_x86_path + " is doesn't look like an x86 path", ndk_x86_path.contains("x86") );
    assertTrue( ndk_x86_path + " doesnt not exist", new File(ndk_x86_path).exists() );    
  }
  
  @Test ( expected = Exception.class )
  public void testStripLib_x86_NotExist() throws Exception
  {
    VisionBaseTask.stripLib( Architecture.ARCH_X86, "testBin_Does_Not_exist", "doesnotexisttest.so");
  }
  
  @Test ( expected = Exception.class )
  public void testStripLib_Arm_NotExist() throws Exception
  {
    VisionBaseTask.stripLib( Architecture.ARCH_ARM, "testBin_Does_Not_exist", "doesnotexisttest.so");
  }
  
  @Test
  public void testStripLib_Arm() throws Exception
  {
    VisionBaseTask.stripLib( Architecture.ARCH_ARM, "./binDir", "TestLibToBeStripped.so");
  }
  
  @Test
  public void testIsPureAscii_True()
  {
    assertTrue( "String should be detected as pure ascii",  VisionBaseTask.isPureAscii("abcdefghijklmnop1234567890" ) );
  }
  
  @Test
  public void testIsPureAscii_False()
  {
    assertFalse( "String should not be detected as pure ascii",  VisionBaseTask.isPureAscii("abcdefghijklmnop1234567890É" ) );
  }
}
