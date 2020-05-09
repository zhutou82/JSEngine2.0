#include "PCH.h"
#include "Texture.h"
#include "Renderer.h"
#include "JSEngine/Platform/Opengl/OpenGLTexture.h"

namespace JSEngine
{

    Ref<Texture2D> Texture2D::Create(const std::string& fileName)
    {
        switch (Renderer::GetGraphicsAPI())
        {
            case RendererAPI::API::NONE:     return nullptr;
            case RendererAPI::API::OPENGL:   return CreateRef<OpenGLTexture2D>(fileName);
            case RendererAPI::API::DIRECT3D: return nullptr;
        }

        JS_CORE_ASSERT(false, "Graphics API not found");
        return nullptr;
    }

}