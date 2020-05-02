#pragma once
#include "JSEngine/Core/Core.h"
#include <chrono>
#include <fstream>
#include <unordered_map>
#include <string>
#include <stack>

#include "JSEngine/Core/SingletonBaseClass.h"
#include "JSEngine/FileSystem/FileSystem.h"



#define g_Profiler JSEngine::Singleton<JSEngine::SimpleProfiler>::GetInstance()
#define ProfileStart(x) g_Profiler.Start(x);
#define ProfilerEnd     g_Profiler.End();

namespace JSEngine
{


    class SimpleProfiler : public Singleton<SimpleProfiler>
    {
        const char* const PROFILER_FILE_NAME = "Profiler";

    public:
        friend class Singleton<SimpleProfiler>;
        void Init(const std::string& folderPath);

        void Start(const std::string& fnName);
        void End();
       
        const std::unordered_map<std::string, float >& GetProfilerCollectionVec() { return m_FnNameTimeMap; }

        ~SimpleProfiler();
         
    private:
        SimpleProfiler();


    private:
        JSFile m_File;

        std::stack<std::pair<std::string, std::chrono::high_resolution_clock::time_point> > m_FnNameTimeStck;
        std::unordered_map<std::string, float> m_FnNameTimeMap;
    }; 

   

}