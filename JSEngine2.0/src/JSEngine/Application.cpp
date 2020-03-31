#include "Application.h"
#include "Log.h"
#include "Window.h"
#include "Platform/WindowsInput.h"

namespace JSEngine
{
    Application* Application::s_Instance = NULL;

#define BIND_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)
    Application::Application()
        : m_AppDeltaTime(0.f), m_Time(FRAME_RATE_PER_SEC)
    {
        g_Logger.Init();
        JS_CORE_ASSERT(!s_Instance, "Application has been created!");
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->AddCallBackFn(BIND_EVENT(OnEvent));
        s_Instance = this;
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
            float currentTime = (float)glfwGetTime();
            for (auto& elem : m_LayerStack)
            {
                elem->OnUpdate();
            }
            m_Window->OnUpdate();
            //if(g_Input.IsKeyReleased(GLFW_KEY_Y))
            //{
            //    JS_CORE_TRACE("Released {0}", GLFW_KEY_Y);
            //}
            if (g_Input.IsKeyPressed(JS_KEY_ESCAPE))
            {
                m_Running = false;
            } 
            if (g_Input.IsLeftMouseButtonPressed())
            {
                JS_CORE_TRACE("Mouse left button Pressed");
            }
            if (g_Input.IsRightMouseButtonPressed())
            {
                JS_CORE_TRACE("Mouse right button Pressed");
            } 

            m_AppDeltaTime = currentTime - m_Time;
            m_Time = currentTime;
            
            JS_CORE_TRACE("engine_frame_rate : {0}",  1.0f / m_AppDeltaTime);
            //maintain frame rate to 60 per second
            if (m_AppDeltaTime < FRAME_RATE_PER_SEC)
            {

                //while()
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