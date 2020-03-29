#include "Application.h"
#include "Log.h"
#include "Window.h"
#include <vector>



namespace JSEngine
{
    Application* Application::s_Instance = NULL;

#define BIND_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)
    Application::Application()
    {
        g_Logger.Init();
        JS_CORE_ASSERT(s_Instance, "Application has been created!");
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->AddCallBackFn(BIND_EVENT(OnEvent));
        s_Instance = this;
    }

   
    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        //dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(CloseWindowEvent));
        dispatcher.Dispatch<KeyPressEvent>(BIND_EVENT(PressKeyEvent));
        JS_CORE_INFO("{0}", e);

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

    }
    
    void Application::Run()
    { 
        while (m_Running)
        {
            m_Window->OnUpdate();
            for (auto& elem : m_LayerStack)
            {
                elem->OnUpdate();
            }
        }
    }
}

#if DEBUG_ENGINE  1
int main()
{
    printf("Welcome to JSEngine2.0\n");
    JSEngine::Application* app = JSEngine::CreateApplication();
    app->Init();
    JS_CORE_INFO("Log initialized");
    CLIENT_INFO("Welcome to JSEngine2.0");
    int a = 10;
    CLIENT_INFO("Varialbe = {0}", a);
    app->Run();
    delete app;
}
#endif