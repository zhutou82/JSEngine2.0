#include "PCH.h"
#include "OpenGLVertexArray.h"
#include "JSEngine/Platform/Opengl/OpenGLContext.h"

namespace JSEngine
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }
    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexArray::AddBuffer(const Ref<VertexBuffer>& vbo, bool b)
    {
        glBindVertexArray(m_RendererID);
        vbo->Bind();
        const auto& layout = vbo->GetLayout();
        const auto& elemVec = layout.GetElementVec();
        int offset = 0;
        for (int i = 0; i < elemVec.size(); ++i)
        {
            const auto& elem = elemVec[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, elem.Count, GetGLTypeByElementType(elem.Type), elem.Normalized,
                layout.GetStride(), (const void*)offset);

            offset += GetSizeByElementType(elem.Type);
        }
        m_VertexBufferVec.push_back(vbo);

    }

    void OpenGLVertexArray::AddIndexBuffer(const Ref<IndexBuffer>& ibo)
    {
        glBindVertexArray(m_RendererID);
        ibo->Bind();
        m_IndexBuffer = ibo;
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
    {
        return m_IndexBuffer;
    }

    const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffer() const
    {
        return m_VertexBufferVec;
    }

}