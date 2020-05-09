#pragma once
#include "Core/Core.h"
#include "Core/SingletonBaseClass.h"
#include "Platform/WindowsWindow.h"
#include "JSEngine/Event/Event.h"
#include "JSEngine/Event/ApplicationEvent.h"
#include "JSEngine/Event/KeyEvent.h"
#include "JSEngine/Core/LayerStack.h"    
#include "JSEngine/Core/Layer.h"
#include "glm/glm.hpp"
#include "JSEngine/imGui/imguiLayer.h"
#include "Serializer/Serializer.h"
#include "Core/TimeStep.h"
//#include 


#define DEBUG_ENGINE 0

#define g_Application     JSEngine::Application::GetInstance()
#define g_AppWindow       ((JSEngine::WindowsWindow*)g_Application.GetWindow())
#define g_AppWindowHandle ((GLFWwindow*)g_AppWindow->GetNativeWindow())

namespace JSEngine
{
#define g_dt              g_Application.GetDeltaTime()

    //template class JSENGINE_API std::default_delete<Window>;
    //template class JSENGINE_API std::unique_ptr<Window>;
    enum EngineSetting
    {
        PROFILER,
        TEXTURE,
        SHADER,
        FONT,
        BINARY,
        NUM_OF_ENGINE_SETTING
    };
    enum WindowSetting
    {
        TITLE,
        WIDTH,
        HEIGHT,
        FULLSCREEN,
        NUM_OF_WINDOW_SETTING
    };


    class JSENGINE_API Application 
    {
        static constexpr const char* const XML_WINDOW_SETTING_CHILD_NAME = "WindowSetting";

        struct EngineSettingStruct
        {
            std::string ResourceFolderPath;
            std::string TextureFile;
            glm::vec2 WindowResolution;
        };
    public:
        Application();
        virtual ~Application();

        /**************Engine Main Flow****************/
        void Init   ();
        void Load   ();
        void Run    ();
        void Unload ();
        void Release();

        /******************** Layering ****************/
        void PushLayer  (Layer* layer  );
        void PushOverLay(Layer* overlay);

        /********************** Event ****************/
        void OnEvent          (Event& e);
        bool CloseWindowEvent (WindowCloseEvent& e);
        bool WindowsResizeEvent(WindowReSizeEvent& e);

        bool PressKeyEvent    (KeyPressEvent& e);

        /******************** Gettor ****************/
        static Application& GetInstance()                   { return *s_Instance;     }
        Window* GetWindow()  const                          { return m_Window.get();  }
        const EngineSettingStruct& GetEngineSetting() const { return m_EngineSetting; }
        const float GetDeltaTime() const                    { return m_AppDeltaTime;  }



    private:

        static Application*      s_Instance;
        LayerStack               m_LayerStack;
        std::unique_ptr<Window>  m_Window;
        bool                     m_Running = true;
        bool                     m_IsWindowMinimized = false;
        bool                     m_IsFullScreen = false;
        float                    m_AppDeltaTime;
        float                    m_LastTime;
        imguiLayer*              m_ImguiLayer;
        Serializer               m_Serializer;
        EngineSettingStruct      m_EngineSetting;
        std::vector<std::string> m_WindowSettingVec;
        


    };

    Application* CreateApplication();


//#ifdef DEBUG_ENGINE
//    Application* CreateApplication() { return new Application; }
//#else
//    Application* CreateApplication();
//#endif 

}

