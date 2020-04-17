#pragma once
#include "glad/glad.h"
struct GLFWwindow;

namespace JSEngine
{
    class GraphicsConext
    {

        virtual void Init(GLFWwindow*) = 0;
        virtual void SwapBuffer()      = 0;
        virtual void Render()          = 0;

    };
}

