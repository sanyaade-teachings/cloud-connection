//For the vision includes to work, must specify the -I%VISION_SDK% parameter when running swig at the command line

//get access to windows and Vision specific data types...
%include <windows.i>
%include <Source/Vision/Runtime/EnginePlugins/VisionEnginePlugin/Scripting/Lua/vision_types.i>
 
//common base classes
%include <Source/Vision/Runtime/EnginePlugins/VisionEnginePlugin/Scripting/Lua/VColor.i>
%include <Source/Vision/Runtime/EnginePlugins/VisionEnginePlugin/Scripting/Lua/VTypedObject.i>
%include <Source/Vision/Runtime/EnginePlugins/VisionEnginePlugin/Scripting/Lua/VisApiTypedEngineObject.i>
 
//classes required for custom object components
%include <Source/Vision/Runtime/EnginePlugins/VisionEnginePlugin/Scripting/Lua/VisApiObjectComponent.i>
 
//classes required for custom entities
%include <Source/Vision/Runtime/EnginePlugins/VisionEnginePlugin/Scripting/Lua/VisApiObject3D.i>
%include <Source/Vision/Runtime/EnginePlugins/VisionEnginePlugin/Scripting/Lua/VisApiBaseEntity.i>
 
//custom headers for generated source file
%module CloudConnectionLuaModule
%{
  //we need to define the C++ headers here
  #include "../CloudConnectionClient.hpp"
  #include "../CloudConnection.hpp"  
%}
 
%include <CloudConnectionClient.i>
%include <CloudConnection.i>