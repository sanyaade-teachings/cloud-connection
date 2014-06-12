/**
 * 
 */
package com.havok.Vision.anttasks;

/**
 * Thrown if a platform SDK coudln't be located
 * @author Project Anarchy
 */
public class SDKNotFoundException extends Exception
{

  /**
   * 
   */
  private static final long serialVersionUID = 3696060801398804782L;

  /**
   * 
   */
  public SDKNotFoundException()
  {
  }

  /**
   * @param message
   */
  public SDKNotFoundException(String message)
  {
    super(message);
  }

  /**
   * @param cause
   */
  public SDKNotFoundException(Throwable cause)
  {
    super(cause);
  }

  /**
   * @param message
   * @param cause
   */
  public SDKNotFoundException(String message, Throwable cause)
  {
    super(message, cause);
  }
}
