#pragma once
#include "SingletonBaseClass.h"
#include "Core.h"
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace JSEngine
{
    #define g_Logger JSEngine::Singleton<JSEngine::Log>::GetInstance()
    #define g_EngineLogger g_Logger.GetCoreLogger()
    #define g_ClientLogger g_Logger.GetApplicationLogger()

    class JSENGINE_API Log  : JSEngine::Singleton<JSEngine::Log>
    {
    public:
        friend class JSEngine::Singleton<JSEngine::Log>;
        
        void Init();
        std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_EngineLogger; }
        std::shared_ptr<spdlog::logger>& GetApplicationLogger() { return m_ApplicationLogger; }
          
    private:
        Log() {} ;
        std::shared_ptr<spdlog::logger> m_EngineLogger;
        std::shared_ptr<spdlog::logger> m_ApplicationLogger;

    };
}

#ifdef ACTUAL_BUILD
#define JSENGINE_CORE_TRACE(...) g_EngineLogger->trace(__VA_ARGS__)
#define CLIENT_TRACE(...)        g_ClientLogger->trace(__VA_ARGS__)

#define JSENGINE_CORE_INFO(...)  g_EngineLogger->info(__VA_ARGS__)
#define CLIENT_INFO(...)         g_ClientLogger->info(__VA_ARGS__)

#define JSENGINE_CORE_WARN(...)  g_EngineLogger->warn(__VA_ARGS__)
#define CLIENT_WARN(...)         g_ClientLogger->warn(__VA_ARGS__)

#define JSENGINE_CORE_ERROR(...) g_EngineLogger->error(__VA_ARGS__)
#define CLIENT_ERROR(...)        g_ClientLogger->error(__VA_ARGS__)

#define JSENGINE_CORE_FATAL(...) g_EngineLogger->fatal(__VA_ARGS__)
#define CLIENT_FATAL(...)        g_ClientLogger->fatal(__VA_ARGS__)
#else
//Log macro
#define JS_CORE_TRACE(...) g_EngineLogger->trace(__VA_ARGS__)
#define CLIENT_TRACE(...)        g_ClientLogger->trace(__VA_ARGS__)

#define JS_CORE_INFO(...)  g_EngineLogger->info(__VA_ARGS__)
#define CLIENT_INFO(...)         g_ClientLogger->info(__VA_ARGS__)

#define JS_CORE_WARN(...)  g_EngineLogger->warn(__VA_ARGS__)
#define CLIENT_WARN(...)         g_ClientLogger->warn(__VA_ARGS__)

#define JS_CORE_ERROR(...) g_EngineLogger->error(__VA_ARGS__)
#define CLIENT_ERROR(...)        g_ClientLogger->error(__VA_ARGS__)

#define JS_CORE_FATAL(...) g_EngineLogger->fatal(__VA_ARGS__)
#define CLIENT_FATAL(...)        g_ClientLogger->fatal(__VA_ARGS__)
#endif 
