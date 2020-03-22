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



#define JS_CORE_ASSERT(x, ...) if(!x) { JS_CORE_ERROR("Assert Failed : {0}", __VA_ARGS__); __debugbreak; }
#define JS_ASSERT(x, ...)      if(!x) { JS_ERROR("Assert Failed : {0}", __VA_ARGS__); __debugbreak; }

#define BIT(x) (1 << x)

