#pragma once
#include <string>
#include <vector>
#include "Binary.h"
#include "Xml.h"
#include "JSEngine/Core/Core.h"
#include "JSEngine/FileSystem/FileSystem.h"
namespace JSEngine
{
    class JSENGINE_API Serializer
    {

    public:
        Serializer();
        Serializer(const std::string& fileName);
        ~Serializer() {};

        void Init(const std::string& xmlFolderPath);
        void Init(const std::string& fileName, const std::string& xmlFolderPath);
        void DeSerialize(std::vector<std::string>& vec, const std::string& childName); 
        void Serialize(const std::vector<std::string>& vec);

    private:
        JSFile m_File;
        tinyxml2::XMLDocument m_XMLDoc;

    };


}