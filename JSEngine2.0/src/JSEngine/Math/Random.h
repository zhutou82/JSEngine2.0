#pragma once
#include <random>

namespace JSEngine
{
    class Random
    {
    public:

        static float Float(float min = 0.f, float max = 1.f)
        {
            return std::uniform_real_distribution<float>(min, max)(s_Engine);
        }

        static void Init()
        {
            s_Engine.seed(std::random_device()());
        }

    private:

        static std::mt19937 s_Engine;
    };


}

