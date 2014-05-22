SET MODULE_NAME=CloudConnectionLuaModule

%VISION_SDK%\ThirdParty\redistsdks\swig\2.0.3_VisionRTTI\swig -I%VISION_SDK% -c++ -lua -verbose -o ./Lua/%MODULE_NAME%.cpp ./Lua/%MODULE_NAME%.i
PAUSE

%VISION_SDK%\Build\StandaloneTools\Iswig\Exe\iswig --includePre "CloudConnectionPluginPCH.hpp" ./Lua/%MODULE_NAME%.cpp
PAUSE