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

    public:
        friend class Singleton<Instrumentor>;

        void BeingSession(const std::string& sessionName)
        {
            //m_JSONFile.Init("../Resource/Profiler/");
            m_OutputFile.open(g_ResourceMgr.GetCoreFolderPaths(CoreFolderPath::PROFILER) + sessionName + ".json", std::ofstream::out);
            m_HasStartSession = true;
            WriteHeader();
        }

        void EndSession()
        {
            m_HasStartSession = false;
            WriteFooter();
            m_OutputFile.close();
        }

        void WriteToProfiler(const ProflierResult& result)
        {
         
            //std::stringstream json;

            //std::string name = result.FunctionName;
            //std::replace(name.begin(), name.end(), '"', '\'');

            //json << std::setprecision(3) << std::fixed;
            //json << ",{";
            //json << "\"cat\":\"function\",";
            //json << "\"dur\":" << (result.Duration.count()) << ',';
            //json << "\"name\":\"" << name << "\",";
            //json << "\"ph\":\"X\",";
            //json << "\"pid\":0,";
            //json << "\"tid\":" << result.ThreadID << ",";
            //json << "\"ts\":" << result.Start.count();
            //json << "}";

            ////std::lock_guard lock(m_Mutex);
            ////if (m_CurrentSession) {
            //m_OutputFile << json.str();
            //m_OutputFile.flush();

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