#include "PCH.h"
#include "OpenGLBuffer.h"

namespace JSEngine
{

    OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, uint32_t size)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }



    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }
    void OpenGLVertexBuffer::UnBind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    //Index buffer////////////////////////////////////////////
    OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* data, uint32_t count)
        : m_Count(count)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }



    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }
    void OpenGLIndexBuffer::UnBind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    uint32_t OpenGLIndexBuffer::GetCount() const
    {
        return m_Count;
    }


}