#include "PCH.h"
#include "Renderer.h"
#include "Buffer.h"
#include "JSEngine/Platform/Opengl/OpenGLBuffer.h"

namespace JSEngine
{

    Ref<VertexBuffer> VertexBuffer::Create(const void* data, uint32_t size)
    {
        
        switch (Renderer::GetGraphicsAPI())
        {
        case RendererAPI::API::NONE:     return nullptr;
        case RendererAPI::API::OPENGL:   return std::make_shared<OpenGLVertexBuffer>(data, size);
        case RendererAPI::API::DIRECT3D: return nullptr;
        }

        JS_CORE_ASSERT(false, "Graphics API not found");
        return nullptr;
    }


    Ref<IndexBuffer> IndexBuffer::Create(const uint32_t* data, uint32_t count )
    {
        switch (Renderer::GetGraphicsAPI())
        {
        case RendererAPI::API::NONE:     return nullptr;
        case RendererAPI::API::OPENGL:   return std::make_shared<OpenGLIndexBuffer>(data, count);
        case RendererAPI::API::DIRECT3D: return nullptr;
        }


        JS_CORE_ASSERT(false, "Graphics API not found");

        return nullptr;
    }

}