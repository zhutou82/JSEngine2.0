#pragma once
#include "JSEngine/Core.h"
#include "JSEngine/SingletonBaseClass.h"
#include "tinyxml2.h"
#include "Serializer.h"

#include <string>

namespace JSEngine
{
#define g_XMLSer Singleton<XMLSerializer>::GetInstance()
    class JSENGINE_API XMLSerializer : public Singleton<XMLSerializer>
    {
        static constexpr const char* const XML_FOLDER_PATH = "../Resource/";
        static constexpr const char* const XML_ENGINE_SETTING_FILE_NAME = "Engine";
        static constexpr const char* const XML_EXTENSION = ".xml";

        struct EngineSettingStruct
        {
            //std::string_literals ;-
            std::string EngineSettingFile = std::string(XML_FOLDER_PATH) + "Engine.xml";
            std::string TextureFile;
            
        };

    public:



        friend class Singleton<XMLSerializer>;

        void Init();
        void Shutdown();

    private:
        XMLSerializer() {}
        void LoadXMLFile(const std::string& file);
        void SerializeEngineSetting();

    private:

        EngineSettingStruct m_EngineSetting;
        
        


    };
}