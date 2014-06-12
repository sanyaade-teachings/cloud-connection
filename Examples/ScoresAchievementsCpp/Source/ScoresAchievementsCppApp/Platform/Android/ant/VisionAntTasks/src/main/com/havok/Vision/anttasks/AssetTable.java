package com.havok.Vision.anttasks;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Vector;

/**
 * This class encapsulates an asset lookup table (.aidlt)
 * @author Project Anarchy
 */
public class AssetTable
{  
  class AssetTableEntry
  {
    AssetTableEntry( String src, String dest )
    {
      m_src = src;
      m_dest = dest;
    }
    
    public String m_src;
    public String m_dest;
  }
  
  private Vector<AssetTableEntry> m_lookupTable = null;
  
  /**
   * Create and Asset Table for a Asset ID Lookup Table File
   * @param fileName The filename of the .aidlt file
   * @throws IOException  if cannot parse the .aidlt file
   */
  public AssetTable(String fileName) throws IOException
  {
    parseAssetLookupTable(fileName);
  }
  
  /**
   * @return The number of entries int the asset table, or 0 if it has not been parsed
   */
  public int getNumberOfEntries()
  {
    int numEntries = 0;
    if ( m_lookupTable != null )
    {
      numEntries = m_lookupTable.size();
    }
    return numEntries;
  }

  /**
   * parse the values in the .aidlt file
   * @param lookupTableFileName The filename of the .aidlt file
   * @throws IOException if cannot read from the .aidlt file
   * @return The number of entries in the parsed lookup table
   */
  private int parseAssetLookupTable(String lookupTableFileName) throws IOException
  {
    //create or clear the asset table lookup entries
    if ( m_lookupTable == null )
    {
      m_lookupTable = new Vector<AssetTable.AssetTableEntry>();
    }
    else
    {
      m_lookupTable.clear();
    }
    
    // the lookUpTable is /AssetMgmt_data/[profile].aidlt thus we need to go two folders up.
    String srcPath = VisionBaseTask.getPath(lookupTableFileName);
    File srcFile = new File(srcPath);
    srcPath = srcFile.getParent();
    srcFile = new File(srcPath);
    srcPath = srcFile.getParent();
    
    //parse each line in the .aidlt file
    File lookupTableFile = new File(lookupTableFileName);
    BufferedReader br = new BufferedReader(new FileReader(lookupTableFile));
    try 
    {      
      String line = null;
      while( (line = br.readLine()) != null )
      {        
        String[] srcDest = line.split("\t");
        String srcAsset = srcDest[0];
        String dest = srcDest[1];
        
        String tableEntrySrc = VisionBaseTask.getPath( srcPath.toLowerCase(), srcAsset.split("#")[0] );
        tableEntrySrc = tableEntrySrc.replace("\\", "/");
        m_lookupTable.add( new AssetTableEntry(tableEntrySrc,dest) );
      }
    } 
    finally 
    {
      if ( br != null )
      {    
        br.close();
      }
    }
    
    return m_lookupTable.size();
  }

  public boolean hasAssetInLookupTable(String fileName)
  {
    boolean hasAsset = false;
    for ( AssetTableEntry entry : m_lookupTable )
    {
      if ( entry.m_src.compareTo(fileName) == 0 )
      {
        if ( entry.m_dest.startsWith("|") == false && 
            entry.m_src.toLowerCase().endsWith( entry.m_dest.toLowerCase() ) == false  )
        {
          hasAsset = true;
        }
      }
    }
    
    return hasAsset;
  }


  public boolean hasTransformedAssetInLookupTable(String fileName)
  {
    boolean hasTransAsset = false;
    for ( AssetTableEntry entry : m_lookupTable )
    {
      String[] destSplit = entry.m_dest.split("/");
      if ( destSplit[destSplit.length-1].compareTo( fileName ) == 0  )
      {
        if ( entry.m_dest.startsWith("|") == false )
        {
          hasTransAsset = true;
        }
      }
    }
    
    return hasTransAsset;
  }
}
  

