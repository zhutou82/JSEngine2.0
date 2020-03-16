#pragma once

#ifdef JSENGINE_PLATFORM_WINDOWS
    #ifdef JSENGINE_BUILD_DLL
        #define JSENGINE_API __declspec(dllexport)
    #else
        #define JSENGINE_API __declspec(dllimport)
    #endif 
#else
    #error JSEngine only supports Windows!
#endif 