#include "PCH.h"
#include "SimpleProfiler.h"

namespace JSEngine
{
    SimpleProfiler::SimpleProfiler()
        :m_File(PROFILER_FILE_NAME, TEXT, WRITE)
    {
       
    }

    void SimpleProfiler::Init(const std::string & folderPath)
    {
        m_File.Init(folderPath);
    }

    void SimpleProfiler::Start(const std::string& fnName)
    {
        fwrite(fnName.c_str(), fnName.size(), 1, m_File.GetFile());
        m_StartTime = std::chrono::high_resolution_clock::now();
    }

    void SimpleProfiler::End()
    {
        m_DurationInSecond = std::chrono::high_resolution_clock::now() - m_StartTime;
        std::string endStr = "\nEnd profile, duration: " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(m_DurationInSecond).count());
        fwrite(endStr.c_str(), endStr.size(), 1, m_File.GetFile());
        JS_CORE_TRACE("End profile, duration: {0} ms", std::chrono::duration_cast<std::chrono::milliseconds>(m_DurationInSecond).count());
    }

    SimpleProfiler::~SimpleProfiler()
    {
        
    }

}