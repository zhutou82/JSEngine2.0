#pragma once
#include "JSEngine/Platform/Opengl/OpenGLContext.h"
#include "VertexBufferObject.h"
#include "Layout.h"

namespace JSEngine
{
    class VertexArrayObject
    {
    public:
        void foo(VertexBufferObject vbo) {}

        VertexArrayObject();
        ~VertexArrayObject();

        void AddToBuffer(const VertexBufferObject& vbo, const Layout& layout) const;

        

        void Bind() const;
        void UnBind() const;

    private:

        unsigned int m_RendererID;
    };

}