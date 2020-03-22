#pragma once
#include "Core.h"
#include <memory>
#include "Platform/WindowsWindow.h"
#include "JSEngine/Event/Event.h"
#include "JSEngine/Event/ApplicationEvent.h"
#include "JSEngine/Event/KeyEvent.h"




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

        void OnEvent(Event& e);
        bool CloseWindowEvent(WindowCloseEvent& e);
        bool PressKeyEvent(KeyPressEvent& e);
    private:
        std::unique_ptr<Window> m_Window;

        bool m_Running = true;

    };

    Application* CreateApplication();
}


