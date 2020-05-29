#include "PCH.h"
#include "Shader.h"
#include "Renderer.h"
#include "JSEngine/Platform/Opengl/OpenGLShader.h"

namespace JSEngine
{
    //Ref<Shader> Shader::Create(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName)
    //{
    //    switch (Renderer::GetGraphicsAPI())
    //    {
    //        case RendererAPI::API::NONE: return nullptr;
    //        case RendererAPI::API::OPENGL: return std::make_shared<OpenGLShader>(vertexShaderFileName, fragmentShaderFileName);
    //        case RendererAPI::API::DIRECT3D: return nullptr;

    //    }
    //    JS_CORE_ASSERT(false, "Unknow type");
    //    return nullptr;
    //}


    //for multi-platform, will be comment out for now, only focus on OPENGL
    Ref<Shader> Shader::Create(const std::string& glslShaderFileName)
    {
        switch (Renderer::GetGraphicsAPI())
        {
            case RendererAPI::API::NONE: return nullptr;
            case RendererAPI::API::OPENGL: return CreateRef<OpenGLShader>(glslShaderFileName);
            case RendererAPI::API::DIRECT3D: return nullptr;

        }
        JS_CORE_ASSERT(false, "Unknow type");
        return nullptr;
    }

}