#pragma once
#include "JSEngine/Graphics/Buffer.h"
#include "glad/glad.h"
#include <vector>
#include <string>

namespace JSEngine
{
    enum class DrawMode : uint32_t
    {
        STREAM_DRAW,
        STREAM_READ,
        STREAM_COPY,
        STATIC_DRAW,
        STATIC_READ,
        STATIC_COPY,
    };

    static uint32_t GetGLTypeByElementType(ElementType type)
    {
        switch (type)
        {
            case JSEngine::ElementType::FLOAT: return GL_FLOAT;
            case JSEngine::ElementType::VEC2:  return GL_FLOAT;
            case JSEngine::ElementType::VEC3:  return GL_FLOAT;
            case JSEngine::ElementType::VEC4:  return GL_FLOAT;
        }
        JS_CORE_ASSERT(false, "Unknow type")
            return 0;
    }

    static uint32_t GetOpenglDrawByDrawMode(DrawMode mode)
    {
        switch (mode)
        {
            case DrawMode::STREAM_DRAW: return GL_STREAM_DRAW;
            case DrawMode::STREAM_READ: return GL_STREAM_READ;
            case DrawMode::STREAM_COPY: return GL_STREAM_COPY;
            case DrawMode::STATIC_DRAW: return GL_STATIC_DRAW;
            case DrawMode::STATIC_READ: return GL_STATIC_READ;
            case DrawMode::STATIC_COPY: return GL_STATIC_COPY;
        }

        JS_CORE_ASSERT(false, "Unknown draw mode");
        return 0;
    }

    //Vertex buffer/////////////////////////////////
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(const void* data, uint32_t size);
        ~OpenGLVertexBuffer();

        virtual void Bind()   const override;
        virtual void UnBind() const override;

        const Layout& GetLayout() const override { return m_Layout; }
        virtual void SetLayout(const Layout& layout) override { m_Layout = layout;}

    private:
        unsigned int m_RendererID;
        Layout m_Layout;
    };


    //Index buffer/////////////////////////////////
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(const uint32_t* data, uint32_t  count);
        ~OpenGLIndexBuffer();


        virtual void Bind()         const override;
        virtual void UnBind()       const override;
        virtual uint32_t GetCount() const override;

    private:

        unsigned int m_RendererID;
        unsigned int m_Count;
    };

}