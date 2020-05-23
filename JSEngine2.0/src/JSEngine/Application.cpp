#include "PCH.h"
#include "Application.h"
#include "Core/Window.h"
#include "Platform/WindowsInput.h"
#include "Managers/InputManager.h"
#include "Graphics/Renderer.h"

namespace JSEngine
{
    Application* Application::s_Instance = NULL;
    Application::Application()
        : m_AppDeltaTime(0.f),
          m_LastTime(0.f),
        m_Serializer()
    {
        JS_PROFILE_FUNCTION();

        JS_CORE_ASSERT(!s_Instance, "Application has been created!");

        //init all systems
        g_Logger.Init();
        //init math library

        Init();
    }

   
    void Application::OnEvent(Event& e)
    {
        //JS_CORE_INFO("{0}", e);
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowReSizeEvent>(JS_BIND_EVENT(Application::WindowsResizeEvent));


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
    bool Application::WindowsResizeEvent(WindowReSizeEvent& e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
            m_IsWindowMinimized = true;

        Renderer::OnMainWindowMinimized(e.GetWidth(), e.GetHeight());
        Renderer2D::OnMainWindowMinimized(e.GetWidth(), e.GetHeight());

        g_AppWindow->SetWidth(e.GetWidth());
        g_AppWindow->SetHeight(e.GetHeight());

        return false;
    }
    bool Application::PressKeyEvent(KeyPressEvent& e)
    {
        if (e.GetKeyCode() == GLFW_KEY_ESCAPE)
            m_Running = false;

        return true;
    }

    void Application::ProfileUpdateLoop()
    {

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
        JS_PROFILE_FUNCTION();

        g_ResourceMgr.Init();
        //read engine setting
        m_Serializer.Init(g_ResourceMgr.GetCoreFileNames(CoreFilerName::ENGINEXML), g_ResourceMgr.GetCoreFolderPaths(CoreFolderPath::XML));
        m_WindowSettingVec.reserve(WindowSetting::NUM_OF_WINDOW_SETTING);
        m_Serializer.DeSerialize(m_WindowSettingVec, XML_WINDOW_SETTING_CHILD_NAME);

        //init winodw handle
        m_Window = std::unique_ptr<Window>(Window::Create({uint32_t(stoi(m_WindowSettingVec[WindowSetting::WIDTH])), 
                                                           uint32_t(stoi(m_WindowSettingVec[WindowSetting::HEIGHT])), 
                                                                         m_WindowSettingVec[WindowSetting::TITLE]}));

        m_Window->AddCallBackFn(JS_BIND_EVENT(Application::OnEvent));
        s_Instance = this;

        //init imgui
        m_ImguiLayer = new imguiLayer;
        PushLayer(m_ImguiLayer);
    }
    
    void Application::Run()
    { 
        while (m_Running)
        {
            JS_PROFILE_FUNCTION();

            if (m_CurrentFrameCount >= m_FrameCountToFlushProfiler)
            {
                JS_FLUSH_PROFILE_FILE();
                m_CurrentFrameCount = 0;
            }

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
                imguiLayer->OnRenderUpdate(delta);
            }
            m_Window->OnUpdate();
            m_ImguiLayer->End();

            
            glfwSwapBuffers(g_AppWindowHandle);
            ++m_CurrentFrameCount;
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