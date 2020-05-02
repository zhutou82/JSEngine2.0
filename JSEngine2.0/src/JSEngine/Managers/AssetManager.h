#pragma once
#include "JSEngine/Core/SingletonBaseClass.h"
#include "JSEngine/Graphics/Texture.h"
#include "JSEngine/Graphics/Meterial.h"
#include "JSEngine/Core/Core.h"


#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#define g_AssertMgr JSEngine::Singleton<JSEngine::AssertManager>::GetInstance()

namespace JSEngine
{

    class AssertManager : Singleton<AssertManager>
    {
        


    public:
        friend class Singleton<AssertManager>;
        void Init();
        
        Ref<Texture>   AcquireTexture  (const std::string& fileName = "Bobo");
        Ref<Texture2D> Acquire2DTexture(const std::string& fileName = "Bobo");
        
        Ref<Meterial> AcquireMeterial(int ID = 0);  
     
    private:

        void InitDefaultTexture();
        void InitDefaultMeterial();


    private:
        AssertManager() {}
        std::unordered_map<std::string, Ref<Texture2D>> m_2DTexturePathPtrMap;
        std::unordered_map<int, Ref<Meterial>> m_MeterialIDhPtrMap;
        
    };

}