#pragma once
#include "JSEngine/Core/SingletonBaseClass.h"
#include "JSEngine/Graphics/Texture.h"
#include "JSEngine/Graphics/Meterial.h"
#include "JSEngine/Core/Core.h"
#include "JSEngine/Serializer/Xml.h"
#include "JSEngine/Graphics/Shader.h"


#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#define g_ResourceMgr JSEngine::Singleton<JSEngine::RecourcesManager>::GetInstance()

namespace JSEngine
{
    enum class CoreFolderPath
    {
        RESOURCE,
        XML,
        ASSETS,
        SHADER,
        PROFILER,
        MODEL,
        MAX_NUM_OF_FOLDER_PATH
    };

    enum class CoreFilerName
    {
        //XML
        ENGINEXML,
        //Shader
        SHADER,
        //assert
        ASSERTS,
        MAX_NUM_OF_FILE_NAME
    };



    class RecourcesManager : Singleton<RecourcesManager>
    {
        
        static constexpr const char* const RESOURCE_XML_FILE_NAME   = "Resource";
        static constexpr const char* const RESOURCE_XML_FOLDER_PATH = "../Resource/";
        static constexpr const char* const RESOURCE_XML_CORE_FOLDER_CHILD_NAME = "CoreFolderPath";
        static constexpr const char* const RESOURCE_XML_CORE_FILE_NAME_CHILD_NAME = "CoreFilerName";

    public:
        friend class Singleton<RecourcesManager>;
        void Init();
        
        Ref<Texture>   AcquireTexture  (const std::string& fileName = "Bobo");
        Ref<Texture2D> Acquire2DTexture(const std::string& fileName = "Bobo");
        Ref<Texture2D> Acquire2DTexture(uint32_t textureID);


        Ref<Shader>    AcquireShader(const std::string& filename);

        const std::unordered_map<std::string, Ref<Shader>>& GetShaders() const { return m_ShaderIDPtrMap; }

        Ref<Material>  AcquireMeterial(int ID = 0);      

        const std::string& GetCoreFolderPaths(CoreFolderPath folderName) const { return m_CoreFolderPaths[(uint32_t)folderName]; }
        const std::string& GetCoreFileNames(CoreFilerName folderName) const    { return m_CoreFileNames[(uint32_t)folderName];   }
     
    private:

        RecourcesManager();
        void InitDefaultTexture();
        void InitDefaultMeterial();

        void DeseralizeCoreFolderPath();

    private:
        
        std::unordered_map<std::string, Ref<Texture2D>> m_2DTexturePathPtrMap;
        std::unordered_map<int, Ref<Texture2D>> m_2DTextureIDPtrMap;

        std::unordered_map<int, Ref<Material>>          m_MeterialIDhPtrMap;
        std::unordered_map<std::string, Ref<Shader>>    m_ShaderIDPtrMap;

        std::vector<std::string> m_CoreFolderPaths;
        std::vector<std::string> m_CoreFileNames;

        Serializer               m_Serializer;

        
    };

}