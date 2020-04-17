#include "PCH.h"
#include "VertexArraryObject.h"

namespace JSEngine
{

    VertexArrayObject::VertexArrayObject()
    {
        glGenBuffers(1, &m_RendererID);
        glBindVertexArray(m_RendererID);
    }
    VertexArrayObject::~VertexArrayObject()
    {

    }

    void VertexArrayObject::AddToBuffer(const VertexBufferObject& vbo, const Layout& layout) const
    {
        vbo.Bind();
        Bind();
        const auto& elemVec = layout.GetElementVec();
        int offset = 0;
        for (int i = 0; i < elemVec.size(); ++i)
        {
            
            const auto& elem = elemVec[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, elem.Count, elem.Type, elem.Normalized,
                                  layout.GetStride() ,(const void*)offset);
            
            offset += elem.Count * Element::GetGLTypeSize(elem.Type);
        }

    }

    void VertexArrayObject::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void VertexArrayObject::UnBind() const
    {
        glBindVertexArray(0);
    }

}