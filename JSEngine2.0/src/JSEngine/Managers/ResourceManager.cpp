#include "PCH.h"
#include "ResourceManager.h"


namespace JSEngine
{
    RecourcesManager::RecourcesManager()
    {
        
    }

    void RecourcesManager::DeseralizeCoreFolderPath()
    {
        m_Serializer.Init(RESOURCE_XML_FILE_NAME, RESOURCE_XML_FOLDER_PATH);

        m_CoreFolderPaths.reserve((int)CoreFolderPath::MAX_NUM_OF_FOLDER_PATH);
        m_CoreFileNames.reserve((int)CoreFilerName::MAX_NUM_OF_FILE_NAME);

        m_Serializer.DeSerialize(m_CoreFolderPaths, RESOURCE_XML_CORE_FOLDER_CHILD_NAME);
        m_Serializer.DeSerialize(m_CoreFileNames, RESOURCE_XML_CORE_FILE_NAME_CHILD_NAME);
    }

    void RecourcesManager::Init()
    {
        
        DeseralizeCoreFolderPath();
    }

    Ref<Texture> RecourcesManager::AcquireTexture(const std::string& fileName)
    {
        return Ref<Texture>();
    }
    Ref<Texture2D> RecourcesManager::Acquire2DTexture(const std::string& fileName)
    {
        auto it = m_2DTexturePathPtrMap.find(fileName);
        if (it != m_2DTexturePathPtrMap.end())
        {
            return it->second;
        }
        auto newTexture = Texture2D::Create(fileName);
        m_2DTexturePathPtrMap.insert({ fileName, newTexture });
        return newTexture;
    }
    Ref<Shader> RecourcesManager::AcquireShader(const std::string& fileName)
    {
        auto it = m_ShaderIDPtrMap.find(fileName);
        if (it != m_ShaderIDPtrMap.end())
        {
            return it->second;
        }

        auto shader = Shader::Create(fileName);
        m_ShaderIDPtrMap.insert({ fileName, shader });
        return shader;
    }
}

