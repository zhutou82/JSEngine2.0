#include "PCH.h"
#include "VertexBufferObject.h"

namespace JSEngine
{
    VertexBufferObject::VertexBufferObject(unsigned int size, const void* data, unsigned drawMode )
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, drawMode);
    }
    VertexBufferObject::~VertexBufferObject()
    {

    }

    void VertexBufferObject::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }
    void VertexBufferObject::UnBind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


}