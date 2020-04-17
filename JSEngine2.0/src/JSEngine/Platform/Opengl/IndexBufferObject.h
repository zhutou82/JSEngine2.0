#pragma once
#include "JSEngine/Platform/Opengl/OpenGLContext.h"

namespace JSEngine
{
    class IndexBufferObject
    {
    public:
        IndexBufferObject(unsigned int size, const void* data, unsigned int drawMode = GL_STATIC_DRAW);
        ~IndexBufferObject();

        void Bind() const;
        void UnBind() const;

    private:

        unsigned int m_RendererID;
    };


}