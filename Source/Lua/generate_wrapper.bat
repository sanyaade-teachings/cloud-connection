SET MODULE_NAME=CloudConnectionLuaModule

%VISION_SDK%\ThirdParty\redistsdks\swig\2.0.3\swig -I%VISION_SDK% -c++ -lua -verbose -o %MODULE_NAME%.cpp %MODULE_NAME%.i
PAUSE

%VISION_SDK%\Build\StandaloneTools\Iswig\Exe\iswig --includePre "CloudConnectionPluginPCH.hpp" %MODULE_NAME%.cpp
PAUSE