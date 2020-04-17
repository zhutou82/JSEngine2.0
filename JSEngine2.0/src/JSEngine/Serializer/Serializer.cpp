#include "PCH.h"
#include "Serializer.h"

namespace JSEngine
{
    using namespace tinyxml2;
    Serializer::Serializer(const std::string & fileName)
        : m_File(fileName, XML, READ)
    {
        
    }

    void Serializer::Init(const std::string & xmlFolderPath)
    {
        m_File.Init(xmlFolderPath);
        m_XMLDoc.LoadFile(m_File.GetFileFullPath().c_str());
        JS_CORE_ASSERT(m_XMLDoc.ErrorID() == 0, "Failed to open XML file");
    }

    void Serializer::DeSerialize(std::vector<std::string>& vec, const std::string& childName)
    {
        XMLElement* element = m_XMLDoc.FirstChildElement(childName.c_str());
        JS_CORE_ASSERT(element, "Title not found");
        XMLNode* node = element->FirstChild();
        while (node) 
        {
            JS_CORE_INFO("{0}", node->FirstChild()->Value());
            vec.push_back(node->FirstChild()->Value());
            node = node->NextSibling(); 
        }
    }



}