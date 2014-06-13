package com.havok.Vision.anttasks;

/**
 * Represents a nested element that is the name of a device to copy to
 * @author Project Anarchy
 */
public class Device
{                                           
    private String m_name;
    /**
     * ANT Attribute - required
     * @param name The name of the device
     */
    public void setName(String name) { m_name = name; }
    public String getName() { return m_name; }
}
