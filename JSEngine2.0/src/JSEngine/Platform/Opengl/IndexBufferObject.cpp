#include "PCH.h"
#include "IndexBufferObject.h"

namespace JSEngine
{
    IndexBufferObject::IndexBufferObject(unsigned int size, const void* data, unsigned int drawMode)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, drawMode);
    }

    IndexBufferObject::~IndexBufferObject()
    {

    }

    void IndexBufferObject::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }
    void IndexBufferObject::UnBind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}