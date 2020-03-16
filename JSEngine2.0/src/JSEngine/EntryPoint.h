#pragma once
#include <stdio.h>
#ifdef JSENGINE_PLATFORM_WINDOWS

extern JSEngine::Application* JSEngine::CreateApplication();

int main(int argc, char** argv)
{
    printf("Welcome to JSEngine 2.0\n");
    JSEngine::Application* app = JSEngine::CreateApplication();
    app->Run();
    delete app;
}




#else
    #error JSEngine only supports Windows!
#endif 