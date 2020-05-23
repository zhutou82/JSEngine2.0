#include "PCH.h"
#include "Texture.h"
#include "Renderer.h"
#include "JSEngine/Platform/Opengl/OpenGLTexture.h"

namespace JSEngine
{

    Ref<Texture2D> Texture2D::Create(const std::string& fileName, const glm::ivec2& dim)
    {
        switch (Renderer::GetGraphicsAPI())
        {
            case RendererAPI::API::NONE:     return nullptr;
            case RendererAPI::API::OPENGL:   return CreateRef<OpenGLTexture2D>(fileName, dim);
            case RendererAPI::API::DIRECT3D: return nullptr;
        }

        JS_CORE_ASSERT(false, "Graphics API not found");
        return nullptr;
    }

    std::string Texture::GetTextureNameByType(TextureType type)
    {
        switch (type)
        {
            case DIFFUSE:  return "texture_diffuse";
            case SPECULAR: return "texture_specular";

        }
        JS_CORE_ASSERT(false, "Texture type not found");
        return "";
    }

}