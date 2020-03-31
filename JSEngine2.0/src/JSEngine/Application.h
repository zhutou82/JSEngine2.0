#pragma once
#include "Core.h"
#include <memory>
#include "SingletonBaseClass.h"
#include "Platform/WindowsWindow.h"
#include "JSEngine/Event/Event.h"
#include "JSEngine/Event/ApplicationEvent.h"
#include "JSEngine/Event/KeyEvent.h"
#include "JSEngine/LayerStack.h"
#include "JSEngine/Layer.h"
#define DEBUG_ENGINE 0

namespace JSEngine
{
#define g_Application     Application::GetInstance()
#define g_AppWindow       ((WindowsWindow*)g_Application->GetWindow())
#define g_AppWindowHandle ((GLFWwindow*)g_AppWindow->GetNativeWindow())

    class JSENGINE_API Application 
    {
        static constexpr float FRAME_RATE = 60.f;
        static constexpr float FRAME_RATE_PER_SEC = 1.0f / FRAME_RATE;
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
        Window* GetWindow()  const { return m_Window.get(); }

        void PushLayer(Layer* layer);
        void PushOverLay(Layer* overlay);

        static Application* GetInstance() { return s_Instance;  }

    private:
        static Application* s_Instance;
        LayerStack m_LayerStack;
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        float m_AppDeltaTime;
        float m_Time;

    };

#if DEBUG_ENGINE  1
    Application* CreateApplication() { return new Application; }
#else
    Application* CreateApplication();
#endif 
}

