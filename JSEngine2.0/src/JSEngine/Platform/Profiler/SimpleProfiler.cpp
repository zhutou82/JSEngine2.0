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
        //fwrite(fnName.c_str(), fnName.size(), 1, m_File.GetFile());
        m_FnNameTimeStck.push({ fnName, std::chrono::high_resolution_clock::now() });
    }

    void SimpleProfiler::End()
    {
        JS_CORE_ASSERT(!m_FnNameTimeStck.empty(), "Profiler does not have proper start");
        const auto& pair = m_FnNameTimeStck.top();
        //std::string endStr = "\nEnd profile, duration: " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(m_DurationInSecond).count());
        //fwrite(endStr.c_str(), endStr.size(), 1, m_File.GetFile());
        //JS_CORE_TRACE("End profile, duration: {0} ms", std::chrono::duration_cast<std::chrono::microseconds>(m_DurationInSecond).count() * 0.001f);
        m_FnNameTimeMap[pair.first] = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - pair.second).count() * 0.001f;
        m_FnNameTimeStck.pop();
    }

    SimpleProfiler::~SimpleProfiler()
    {
        
    }

}