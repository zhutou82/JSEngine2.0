#pragma once
#include "OpenGLBuffer.h"
#include "JSEngine/Graphics/VertexArray.h"
#include "JSEngine/Core/Core.h"

namespace JSEngine
{

    class OpenGLVertexArray : public VertexArray
    {
    public:

        OpenGLVertexArray();
        ~OpenGLVertexArray();

        virtual void AddBuffer(const Ref<VertexBuffer>& vbo, bool) override;
        virtual void AddIndexBuffer(const Ref<IndexBuffer>& ibo) override;
        virtual void Bind() const override;
        virtual void UnBind() const override;
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const override;
        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const override;

    private:

        uint32_t m_RendererID;
        uint32_t m_VertexBufferIndex = 0;
        std::vector<Ref<VertexBuffer>> m_VertexBufferVec;
        Ref<IndexBuffer> m_IndexBuffer;


    };

}