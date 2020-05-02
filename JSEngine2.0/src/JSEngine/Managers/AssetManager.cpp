#include "PCH.h"
#include "AssetManager.h"


namespace JSEngine
{
    Ref<Texture> AssertManager::AcquireTexture(const std::string& fileName)
    {

        return Ref<Texture>();
    }
    Ref<Texture2D> AssertManager::Acquire2DTexture(const std::string& fileName)
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
}

