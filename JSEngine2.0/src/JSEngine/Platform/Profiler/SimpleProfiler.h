#pragma once
#include "JSEngine/Core.h"
#include <chrono>
#include <fstream>
#include "JSEngine/SingletonBaseClass.h"
#include "JSEngine/FileSystem/FileSystem.h"


namespace JSEngine
{
#define g_Profiler Singleton<SimpleProfiler>::GetInstance()
#define ProfileStart(x) JS_CORE_TRACE("Start profiling function {0}", x); g_Profiler.Start(x);
#define ProfilerEnd g_Profiler.End();

    class SimpleProfiler : public Singleton<SimpleProfiler>
    {
        const char* const PROFILER_FILE_NAME = "Profiler";

    public:
        friend class Singleton<SimpleProfiler>;
        void Init(const std::string& folderPath);

        void Start(const std::string& fnName);
        void End();
       
        ~SimpleProfiler();
         
    private:
        SimpleProfiler();


    private:
        std::chrono::high_resolution_clock::time_point m_StartTime;
        std::chrono::high_resolution_clock::time_point m_EndTime;
        std::chrono::duration<float>                   m_DurationInSecond;
        JSFile m_File;
    }; 

   

}