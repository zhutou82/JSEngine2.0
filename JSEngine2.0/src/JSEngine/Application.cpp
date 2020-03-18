#include "Application.h"
#include "Log.h"
#include "Event/Event.h"


namespace JSEngine
{
    Application::Application()
    {

    }
    Application::~Application()
    {

    }

    void Application::Init()
    {
        g_Logger.Init();
    }

    void Application::Run()
    {
        JSENGINE_CORE_INFO("Engine loop");
        while (true)
        {

        }
    }
}


