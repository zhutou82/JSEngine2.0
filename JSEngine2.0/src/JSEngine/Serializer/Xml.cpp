#include "PCH.h"
#include "Xml.h"

namespace JSEngine
{
    void XMLSerializer::Init()
    {

        //std::string s = "123";
        SerializeEngineSetting();

    }

    void XMLSerializer::LoadXMLFile(const std::string & file)
    {

    }

    void XMLSerializer::SerializeEngineSetting()
    {
        tinyxml2::XMLDocument xmlDoc;
        xmlDoc.LoadFile(m_EngineSetting.EngineSettingFile.c_str()); 
        JS_CORE_ASSERT(xmlDoc.ErrorID(), "Failed to open XML file");

    }



}