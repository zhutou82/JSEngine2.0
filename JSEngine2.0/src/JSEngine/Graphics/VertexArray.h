#pragma once
#include "Buffer.h"
#include "glad/glad.h"

namespace JSEngine
{
    class VertexArray
    {
    public:

        virtual ~VertexArray() {};

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void AddBuffer(const Ref<VertexBuffer>& vbo, bool = false) = 0;
        virtual void AddIndexBuffer(const Ref<IndexBuffer>& vbo) = 0;

        virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
        virtual const std::vector<Ref<VertexBuffer> >& GetVertexBuffer() const = 0;

        static Ref<VertexArray> Create();

    };
}