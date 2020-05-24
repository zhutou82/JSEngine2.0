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


#ifdef ACTUAL_BUILD
#define JS_CORE_ASSERT(x, ...) 
#define JS_ASSERT(x, ...)      

#else
#define JS_CORE_ASSERT(x, ...) if(!(x)) { JS_CORE_ERROR("Assert Failed : {0}", __VA_ARGS__); __debugbreak(); }
#define JS_ASSERT(x, ...)      if(!(x)) { JS_ERROR("Assert Failed : {0}", __VA_ARGS__);      __debugbreak(); }

#endif

#define JS_BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)
#define BIT(x) (1 << x)


namespace JSEngine
{
    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T, class... Args>
    constexpr Scope<T> CreateScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T>
    using SoftRef = std::weak_ptr<T>;

    template <class T, class... Args>
    constexpr Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    
}

