#include "Application.h"
#include "Log.h"
#include "Window.h"



namespace JSEngine
{
#define BIND_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)
    Application::Application()
    {
        g_Logger.Init();
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->AddCallBackFn(BIND_EVENT(OnEvent));
    }


    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(CloseWindowEvent));
        dispatcher.Dispatch<KeyPressEvent>(BIND_EVENT(PressKeyEvent));
        JS_CORE_INFO("{0}", e);
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
        }
    }

}


