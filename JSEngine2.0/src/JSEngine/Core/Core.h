#pragma once
#include <memory>

#ifdef JSENGINE_PLATFORM_WINDOWS
    #ifdef JSENGINE_BUILD_DLL
        #define JSENGINE_API 
    #else
        #define JSENGINE_API 
    #endif 
#else
    #error JSEngine only supports Windows!
#endif 



#define JS_CORE_ASSERT(x, ...) if(!x) { JS_CORE_ERROR("Assert Failed : {0}", __VA_ARGS__); __debugbreak(); }
#define JS_ASSERT(x, ...)      if(!x) { JS_ERROR("Assert Failed : {0}", __VA_ARGS__); __debugbreak(); }
#define JS_BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

#define BIT(x) (1 << x)

constexpr float FRAME_RATE = 60.f;
constexpr float FRAME_RATE_PER_SEC = 1.0f / FRAME_RATE;


namespace JSEngine
{
    template <typename T>
    using Scope = std::unique_ptr<T>;

    //template <typename T>
    //using Make_Scope = std::make_unique<T>;

    template <typename T>
    using Ref = std::shared_ptr<T>;

    
    //#define Make_Ref(T) std::make_shared<T>;

}

