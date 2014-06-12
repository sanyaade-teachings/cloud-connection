/**
 * 
 */
package com.havok.Vision.anttasks;

import java.io.File;
import java.io.IOException;
import java.util.Vector;

import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.DirectoryScanner;
import org.apache.tools.ant.types.FileSet;

/**
 * ANT Task
 * Clean assets dir and copy resources
 * @author Project Anarchy
 */
public class VisionCopyAssetsTask extends VisionBaseTask
{
  /** this is the profile name of the Vision build, e.g. android,ios,pcdx9 - this is used */
  private String m_profileName = "android";  
  private String m_destPath = null; 
  /** The source ANT fileset */
  private Vector<FileSet> m_srcFileSet = new Vector<FileSet>();
  
  /** ANT Attribute - Optional : defaults to "android" 
   * This is the profile name of the Vision build, e.g. android,ios,pcdx9 - this is used to file the aidlt profile file */
  public void setProfileName( String profilename )
  {
    m_profileName = profilename;
  }
  
  /** ANT Attribute - Required 
   * This is the fully qualified source path where the assets are being copied from */
  public void setDestinationPath( File destath )
  {
    m_destPath = destath.getPath();
  }
  
  /** ANT Attribute - Required 
   * This is the fully qualified source path where the assets are being copied from */
  public void addFileset(FileSet fileset) 
  {
    if ( m_srcFileSet.size() >= 1 )
    {
      throw new BuildException("Only 1 fileset is allowed in this Task");
    }
    
    m_srcFileSet.add(fileset);
  }
  
  /**
   * Check that the ANT Attributes are valid
   */
  void checkANTAttributes() throws BuildException
  {
    //check dest path
    if ( m_destPath == null )
    {
      throw new BuildException("The DestinationPath has not been set");      
    }
    else if ( new File( m_destPath ).exists() && new File( m_destPath ).isDirectory() == false )
    {
      throw new BuildException("The DestinationPath '"+m_destPath+"' is not a folder");
    }
    
    //check source path
    if ( m_srcFileSet.size() == 0 )
    {
      throw new BuildException("The Source fileset has not been set");
    }
    else
    {      
      for (FileSet file : m_srcFileSet)
      {      
        File f = file.getDir();
        if ( f == null  )
        {
          throw new BuildException("no folders have been specified in the source file set");
        }
        else
        {
          if ( file.getDir().exists() && file.getDir().isDirectory() == false )
          {
            throw new BuildException("The source '"+ file.getDir() +"' is not a directory");
          }
        }
      }
    }
  }
  
  /**
   * ANT Task Entry point
   */
  @Override
  public void execute()
  {
    checkANTAttributes();

    //get the destination folder
    final File srcFile = m_srcFileSet.get(0).getDir();
    final String srcPath = srcFile.getPath();
    File fileDest = new File(m_destPath);
    
    //# Parse the lookup table
    AssetTable currentLookupTable = null;
    
    // Check if the directory contains an .AssetCache - if so we have to take some extra care
    // (transformed assets have to be copied etc.)
    String transformedPath = getPath(srcPath, "AssetMgmt_data", "transformed");
    File transformedDir = new File( transformedPath );
    if ( transformedDir.isDirectory() )
    {
        // Check if there is a profile matching the profile name given in the options
        String profileLookupTableFileName = getPath(srcPath, "AssetMgmt_data", m_profileName + ".aidlt");         
        File profileLookupTableFileNameFile = new File(profileLookupTableFileName);           
        if ( profileLookupTableFileNameFile.exists() == false )
        {
            log("AssetMgmt_data/transformed exists but given profile doesn't ("+ profileLookupTableFileName + ")");
        }
        else
        {
            // Parse the lookup table
            try
            {
              currentLookupTable = new AssetTable(profileLookupTableFileName);
            } 
            catch (IOException e)
            {
              throw new BuildException( "Error while trying to parse the .aidlt (Asset ID Lookup Table) '"+profileLookupTableFileName+"'" ,e);
            }
        }
        
        //copy managed resources       
        FileSet fs = m_srcFileSet.get(0);
        DirectoryScanner ds = fs.getDirectoryScanner();
        
        log("Copying Asset Files:");
        String[] files = ds.getIncludedFiles();
        for (int i = 0; i < files.length; i++)
        {
          log(files[i]);
          if ( excludeFile( srcPath, files[i] ) == false && 
              excludeFileDueToAssetCache( srcPath, files[i], currentLookupTable ) == false )
          {          
            try
            {
              //the file to copy to/from
              File fromFile = new File( getPath( srcPath, files[i]) );
              File toFile = new File( getPath( fileDest.toString(), files[i]) );
              
              checkAsciiPath(fromFile);
              boolean madeFolders = ensureDirsExist(toFile);
              
              //copy the file
              if ( madeFolders ) 
              {
                copyFileUsingChannel(fromFile, toFile);
              }
              else
              {
                throw new IOException("Failed to create the folders for '" + toFile.getPath() + "'" );
              }
            } 
            catch (IOException e)
            {
              throw new BuildException("Error while copying assets: ", e);
            }
          }
        }
        
        // Reset current lookup table
        currentLookupTable = null;
    }
    else
    {
      //copy unmanaged resources      
      FileSet fs = m_srcFileSet.get(0);
      DirectoryScanner ds = fs.getDirectoryScanner();
           
      log("Copying Asset Files:");
      String[] files = ds.getIncludedFiles();
      for (int i = 0; i < files.length; i++)
      {
        log(files[i]);         
        try
        {
          //the file to copy to/from
          File fromFile = new File( getPath( srcPath, files[i]) );
          File toFile = new File( getPath( fileDest.toString(), files[i]) );
          
          checkAsciiPath(fromFile);
          boolean madeFolders = ensureDirsExist(toFile);
          
          //copy the file
          if ( madeFolders ) 
          {
            copyFileUsingChannel(fromFile, toFile);
          }
          else
          {
            throw new IOException("Failed to create the folders for '" + toFile.getPath() + "'" );
          }
        } 
        catch (IOException e)
        {
          throw new BuildException("Error while copying assets: ", e);
        }
      }
    }   
   
    log( "Copied '" + srcFile.getPath() + "' to '"+ fileDest.getPath() +"'" );
  }
  
  
  /**
   * @return True if given root and file should be excluded from resources. False otherwise.
   */
  private boolean excludeFile( String root, String curFile )
  {
    //find filename and extension
    int dot = curFile.lastIndexOf('.');
    String fileName = (dot == -1) ? curFile : curFile.substring(0, dot);
    String fileExt = (dot == -1) ? "" : curFile.substring(dot);
            
    File pvrFile = new File( getPath(root, fileName+".pvr") );
    File etcFile = new File( getPath(root, fileName+".etc") );
    File rgbaFile = new File( getPath(root, fileName+".rgba") );
    
    //find out if file is a .dds has a .pvr and .etc or .rgba equivalent, if it does then exclude it
    if ( fileExt.compareTo(".dds") == 0 
        && pvrFile.exists() 
        && (etcFile.exists() || rgbaFile.exists()) )
    {
        return true;
    }
            
    //exclude shader bin that are not GLES2.vShaderBin
    if ( fileExt.compareTo(".vShaderBin") == 0 && fileName.compareTo("GLES2") != 0 )
    {
        return true;
    }
            
    return false;
  }
  
  /**
   * Find out if we should exclude a file because it has an entry in
   * the asset cache instead
   * @param root
   * @param file The relative file to be checked
   * @param localLUT The .aidlt lookup table
   * @return True if the file should be excluded
   */
  private boolean excludeFileDueToAssetCache(String root, String file, AssetTable localLUT)
  {    
      if ( localLUT == null )
      {
          return false;
      }
  
      String fileName = getPath(root, file).replace("\\", "/");
  
      // If the asset has a transformation (and thus is in the asset cache) we exclude it
      if ( localLUT.hasAssetInLookupTable(fileName.toLowerCase()) )
      {
          return true;
      }
  
      if ( root.replace("\\", "/").endsWith("AssetMgmt_data/transformed") )
      {
          if ( localLUT.hasTransformedAssetInLookupTable(file) )
          {
              return false;
          }
          else
          {
              return true;
          }
      }
      
      return false;
  }
    
  /**
   * Verify that src file path has no unicode characters.
   * This is a restriction enforced by aapt which is used to bundle the apk
   * @throws {@link BuildException} if the src path is not ascii
   */
  private void checkAsciiPath( File src ) throws BuildException
  {
    String checkpath = src.getPath();
    if ( isPureAscii( src.getPath() ) == false  )
    {
      throw new BuildException("Non-ascii character found in resource path '"+checkpath+"'. "+
          "Only ascii filenames are supported by Android.");
    }
  }  
}
