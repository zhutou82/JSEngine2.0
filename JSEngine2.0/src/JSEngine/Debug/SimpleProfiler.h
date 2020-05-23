#pragma once
#include <chrono>
#include <fstream>
#include <string>
#include <thread>
#include <iomanip>

#include "JSEngine/Core/Core.h"
#include "JSEngine/FileSystem/FileSystem.h"
#include "JSEngine/Core/SingletonBaseClass.h"
#include "JSEngine/FileSystem/FileSystem.h"
#include "JSEngine/Managers/ResourceManager.h"


#define g_Instrumentor JSEngine::Singleton<JSEngine::Instrumentor>::GetInstance()

#ifdef ACUTAL_BUILD

#define JS_PROFILE_BEGINE_SESSION(name) 
#define JS_PROFILE_END_SESSION()

#define JS_PROFILE_SCOPE_START(name) 
#define JS_PROFILE_SCOPE_END() 
#define JS_PROFILE_FUNCTION() 

#else

//use "chrome://tracing/" for visualize result
#define JS_PROFILE_BEGINE_SESSION(name) g_Instrumentor.BeingSession(name);
#define JS_PROFILE_END_SESSION()        g_Instrumentor.EndSession();

#define JS_PROFILE_SCOPE_START(name) { JSEngine::InstrumentTimer timer##__LINE__(name);
#define JS_PROFILE_SCOPE_END() }
#define JS_PROFILE_FUNCTION() JSEngine::InstrumentTimer timer##__LINE__(__FUNCSIG__);

#define JS_FLUSH_PROFILE_FILE() g_Instrumentor.Flush()
 #endif

namespace JSEngine
{

    struct ProflierResult
    {
        std::string FunctionName;
        std::chrono::duration<double, std::micro> Start;
        std::chrono::microseconds Duration;
        std::thread::id ThreadID;
    };


    class Instrumentor : public Singleton<Instrumentor>
    {

        const std::string ProfilerFolderPath = "../Resource/Profiler/";
        const std::string ProfilerFileType = ".json";
         
    public:
        friend class Singleton<Instrumentor>;

        void BeingSession(const std::string& sessionName)
        {
            //m_JSONFile.Init("../Resource/Profiler/");
            m_File = ProfilerFolderPath + sessionName + ProfilerFileType;
            m_OutputFile.open(m_File, std::ofstream::out);
            m_HasStartSession = true;
            WriteHeader();
        }

        void EndSession()
        {
            m_HasStartSession = false;
            WriteFooter();
            m_OutputFile.close();
        }

        void Flush()
        {
            if (m_HasStartSession)
            {
                m_OutputFile.close();
                BeingSession(m_File);
            }
        }

        void WriteToProfiler(const ProflierResult& result)
        {
            std::lock_guard lock(m_Mutex);
            if (m_HasStartSession)
            {
                m_OutputFile << "{"
                             << "\"name\": \"" << result.FunctionName << "\","
                             << "\"cat\": \"" << "JSEngine profling" << "\","
                             << "\"ph\": \"" << "X" << "\","
                             << "\"ts\":  " << result.Start.count() << ","
                             << "\"dur\": " << result.Duration.count() << ","
                             << "\"pid\": " << 0 << ","
                             << "\"tid\": " << result.ThreadID
                             << "}";

                m_OutputFile.flush();
            }
        }
        
    private:

        void WriteHeader()
        {
            std::lock_guard lock(m_Mutex);
            m_OutputFile << "{\"otherData\": {},\"traceEvents\":[{},";
            m_OutputFile.flush();
        }


        void WriteFooter()
        {
            std::lock_guard lock(m_Mutex);
            m_OutputFile << "]}";
            m_OutputFile.flush();
        }

        Instrumentor() 
            : m_HasStartSession(false)
        {}

    private:

        std::ofstream m_OutputFile;
        bool m_HasStartSession;
        std::mutex m_Mutex;

        std::string m_File;

    };


    class InstrumentTimer
    {

    public:

        InstrumentTimer(const std::string& fnName)
            : m_FunctionName(fnName)
        {
            m_Start = std::chrono::steady_clock::now();
        }

        ~InstrumentTimer()
        {
            Stop();
        }

        void Stop()
        {
            std::chrono::steady_clock::time_point m_End = std::chrono::steady_clock::now();
            auto duration = std::chrono::time_point_cast<std::chrono::microseconds>(m_End).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_Start).time_since_epoch();
            g_Instrumentor.WriteToProfiler({ m_FunctionName, m_Start.time_since_epoch(), duration, std::this_thread::get_id()});
        }
       
    private:

        std::string m_FunctionName;
        std::chrono::steady_clock::time_point m_Start;
        bool m_HasStart;
    }; 

   

}