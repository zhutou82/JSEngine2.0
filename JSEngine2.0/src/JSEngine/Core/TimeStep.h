#pragma once
#pragma once
#include "Core.h"

namespace JSEngine
{
    class TimeStep
    {
    public:
        TimeStep(float deltaTime);
        operator float() { return m_DeltaTime; }

    //private:
        float m_DeltaTime;

    };
}
