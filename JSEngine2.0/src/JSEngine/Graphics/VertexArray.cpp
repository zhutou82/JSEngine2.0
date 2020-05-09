#include "PCH.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "JSEngine/Platform/Opengl/OpenGLVertexArray.h"

namespace JSEngine
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetGraphicsAPI())
        {
            case RendererAPI::API::NONE:     return nullptr;
            case RendererAPI::API::OPENGL:   return CreateRef<OpenGLVertexArray>();
            case RendererAPI::API::DIRECT3D: return nullptr;
        }

        JS_CORE_ASSERT(false, "Graphics API not found");
        return nullptr;
    }
}