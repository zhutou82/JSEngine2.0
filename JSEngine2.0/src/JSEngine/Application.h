#pragma once
#include "Core.h"




namespace JSEngine
{
    class JSENGINE_API Application
    {
    public:
        Application();
        virtual ~Application();
        void Init();
        void Load();
        void Run();
        void Unload();
        void Release();
    };

    Application* CreateApplication();
}


