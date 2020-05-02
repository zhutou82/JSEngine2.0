#include "PCH.h"
#include "Application.h"
#include "Core/Window.h"
#include "Platform/WindowsInput.h"
#include "Managers/InputManager.h"
#include "JSEngine/Serializer/Xml.h"
#include "JSEngine/Platform/Profiler/SimpleProfiler.h"


namespace JSEngine
{
    Application* Application::     s_Instance             = NULL;
    const std::string Application::s_RECOUSE_FOLDER_PATH  = "../Resource/";
    const std::string Application::s_XML_FOLDER_PATH      = "../Resource/XML/";
    const std::string Application::s_PROFILER_FOLDER_PATH = "../Resource/Profiler/";

    Application::Application()
        : m_AppDeltaTime(0.f),
          m_LastTime(0.f),
        m_Serializer(XML_ENGINE_SETTING_FILE_NAME)
    {
        JS_CORE_ASSERT(!s_Instance, "Application has been created!");

        m_EngineSettingVec.reserve(EngineSetting::NUM_OF_ENGINE_SETTING);
        m_WindowSettingVec.reserve(WindowSetting::NUM_OF_WINDOW_SETTING);

        //init all systems
        g_Logger.Init();

        //init simple profiler
        g_Profiler.Init(s_PROFILER_FOLDER_PATH);

        Init();
    }

   
    void Application::OnEvent(Event& e)
    {
        //JS_CORE_INFO("{0}", e);
        for (std::vector<Layer*>::iterator it = m_LayerStack.end(); it != m_LayerStack.begin();)
        { 
            (*--it)->OnEvent(e);
            if (e.IsHanlded()) break;
        }
        
    }
    bool Application::CloseWindowEvent(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
    bool Application::PressKeyEvent(KeyPressEvent& e)
    {
        if (e.GetKeyCode() == GLFW_KEY_ESCAPE)
            m_Running = false;

        return true;
    }

    bool Application::CursorEvent(MouseMoveEvent& e)
    {
        //g_Camera.CursorPosCallBack(e.GetMouseXCoordinate(), e.GetMouseYCoordinate());
        return true;
    }

    bool Application::CursorScrollEvent(MouseScrollEvent& e)
    {
        //g_Camera.CursorScrollCallBack(e.GetMouseXOffSet(), e.GetMouseYOffSet());
        return false;
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverLay(Layer* overLay)
    {
        m_LayerStack.PushOverlay(overLay);
        overLay->OnAttach();
    }


    Application::~Application()
    {

    }

    void Application::Init()
    {
        //ProfileStart(__FUNCTION__);
        //init engine serializer
        m_Serializer.Init(s_XML_FOLDER_PATH);
        m_Serializer.DeSerialize(m_EngineSettingVec, "RecourseFolderPath");
        m_Serializer.DeSerialize(m_WindowSettingVec, "WindowSetting");

        //init winodw handle
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->AddCallBackFn(JS_BIND_EVENT(Application::OnEvent));
        s_Instance = this;

        //init imgui
        m_ImguiLayer = new imguiLayer;
        PushLayer(m_ImguiLayer);
        //ProfilerEnd
    }
    
    void Application::Run()
    { 
        while (m_Running)
        {
            
            float currentTime = (float)glfwGetTime();
            TimeStep delta(currentTime - m_LastTime);
            m_AppDeltaTime = delta;
            m_LastTime = currentTime;

            

            //exit window
            if (g_Input.IsKeyPressed(GLFW_KEY_ESCAPE))
            {
                m_Running = false;
            }

            for (auto& layer : m_LayerStack)
            {
                layer->OnUpdate(delta);
            }
           
            //will be put into render thread
            m_ImguiLayer->Begin();
            for (auto& imguiLayer : m_LayerStack)
            {
                imguiLayer->OnRenderUpdate();
            }
            m_Window->OnUpdate();
            m_ImguiLayer->End();


            
            glfwSwapBuffers(g_AppWindowHandle);
        }
    }
}

//#if DEBUG_ENGINE  1
//int main()
//{
//    printf("Welcome to JSEngine2.0\n");
//    JSEngine::Application* app = JSEngine::CreateApplication();
//    app->Init();
//    JS_CORE_INFO("Log initialized");
//    CLIENT_INFO("Welcome to JSEngine2.0");
//    int a = 10;
//    CLIENT_INFO("Varialbe = {0}", a);
//    app->Run();
//    delete app;
//}
//#endif