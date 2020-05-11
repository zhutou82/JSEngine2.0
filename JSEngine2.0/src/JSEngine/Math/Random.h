#pragma once
#include <random>

namespace JSEngine
{
    class Random
    {
    public:

        static float Float()
        {
            return (float)s_Range(s_Engine)/ (float)std::numeric_limits<uint32_t>::max();
        }

        static void Init()
        {
            s_Engine.seed(std::random_device()());
        }

    private:

        static std::mt19937 s_Engine;
        static std::uniform_int_distribution<std::mt19937::result_type> s_Range;
    };


}

