#include "PCH.h"

namespace JSEngine
{
    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        m_EngineLogger = spdlog::stdout_color_mt("JSEngine2.0");
        m_EngineLogger->set_level(spdlog::level::trace);

        m_ApplicationLogger = spdlog::stdout_color_mt("APP");
        m_ApplicationLogger->set_level(spdlog::level::trace);

    }
}