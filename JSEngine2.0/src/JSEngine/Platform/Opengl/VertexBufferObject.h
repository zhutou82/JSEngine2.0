#pragma once
#include "JSEngine/Platform/Opengl/OpenGLContext.h"

namespace JSEngine
{
    class VertexBufferObject
    {
    public:
        VertexBufferObject(unsigned int size, const void* data, unsigned drawMode = GL_STATIC_DRAW);
        ~VertexBufferObject();
        
        void Bind() const;
        void UnBind() const;

    private:
        unsigned int m_RendererID;
    };


}