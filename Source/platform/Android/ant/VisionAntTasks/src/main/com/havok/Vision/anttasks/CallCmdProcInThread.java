package com.havok.Vision.anttasks;

import java.util.concurrent.Callable;

/**
 * Call a command inside a Callable so we can put a timeout on it
 * @author Project Anarchy
 */
class CallCmdProcInThread implements Callable<Integer>
{
  private String[] m_cmdArray = null;
  private Process m_proc = null;
  
  /**
   * @param cmdArray The command array to be called see Runtime#exec(String[])
   */
  public CallCmdProcInThread( String[] cmdArray )
  {
    m_cmdArray = cmdArray;
  }
  
  /*
   * (non-Javadoc)
   * @see java.util.concurrent.Callable#call()
   */
  @Override
  public Integer call() throws Exception
  {
    Runtime rt = Runtime.getRuntime();
    Process m_proc = rt.exec(m_cmdArray);
    int retval = m_proc.waitFor();
    if ( retval != 0 )
    {
      //abnormal ternimation
      throw new Exception("Error while executing the command");
    }
    else
    {
      System.out.println("Success!!");
    }
    return retval;
  }
  
  /**
   * Kill the process if one exists 
   */
  public void kill()
  {
    if ( m_proc != null )
    {
      m_proc.destroy();
    }
  }
}
