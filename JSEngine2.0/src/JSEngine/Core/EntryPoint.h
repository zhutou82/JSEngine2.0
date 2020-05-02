#pragma once

#pragma warning(push)
#pragma warning(disable:4251)
//your declarations that cause 4251
#pragma warning(pop)

#include <stdio.h>
#include "Log.h"
#ifdef JSENGINE_PLATFORM_WINDOWS


extern JSEngine::Application* JSEngine::CreateApplication();

int main(int argc, char** argv)
{
    printf("Welcome to JSEngine2.0\n");
    JSEngine::Application* app = JSEngine::CreateApplication();
    //app->Init();
    JS_CORE_INFO("Log initialized");
    CLIENT_INFO("Welcome to JSEngine2.0");
    int a = 10;
    CLIENT_INFO("Varialbe = {0}", a);
    app->Run();
    delete app;
}




#else
    #error JSEngine only supports Windows!
#endif 