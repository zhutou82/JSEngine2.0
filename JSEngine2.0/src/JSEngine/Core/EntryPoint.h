#pragma once

#pragma warning(push)
#pragma warning(disable:4251)
//your declarations that cause 4251
#pragma warning(pop)

#include <stdio.h>
#include "Log.h"
#include "JSEngine/Debug/SimpleProfiler.h"

#ifdef JSENGINE_PLATFORM_WINDOWS

extern JSEngine::Application* JSEngine::CreateApplication();

int main(int argc, char** argv)
{
    JS_PROFILE_BEGINE_SESSION("Engine Initialization");
    JSEngine::Application* app = JSEngine::CreateApplication();
    JS_PROFILE_END_SESSION();

    JS_PROFILE_BEGINE_SESSION("Engine Update");
    app->Run();
    JS_PROFILE_END_SESSION();

    JS_PROFILE_BEGINE_SESSION("Engine Shutdown");
    delete app;
    JS_PROFILE_END_SESSION();

}


#else
#error JSEngine only supports Windows!
#endif 