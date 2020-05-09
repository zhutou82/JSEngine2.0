#include "PCH.h"
#include "RenderCommand.h"
#include "JSEngine/Platform/Opengl/OpenGLRenderAPI.h"

namespace JSEngine
{
    RendererAPI * RenderCommand::s_RenderAPI = new OpenGLRendererAPI;

    void RenderCommand::SetMainViewPort(uint32_t width, uint32_t height)
    {
        s_RenderAPI->SetMainViewPort(width, height);
    }

    void RenderCommand::Clear(const glm::vec4& color)
    {
        s_RenderAPI->Clear(color);
    }

    void RenderCommand::DrawIndex(const Ref<Mesh>& mesh)
    {
        s_RenderAPI->DrawIndexd(mesh);
    }

    void RenderCommand::AttachShader(const Ref<Shader>& shader)
    {
        s_RenderAPI->AttachShader(shader);
    }

    void RenderCommand::SetUpCamera()
    {
        s_RenderAPI->SetUpCamera();
    }

    void RenderCommand::SetUpEnviroment(const Ref<SceneData>& sceneData)
    {
        s_RenderAPI->SetUpEnviroment(sceneData);
    }

    void RenderCommand::ClearScene()
    {
        s_RenderAPI->ClearSceneData();
    }

    void RenderCommand::Submit(const Ref<Mesh>& mesh)
    {
        s_RenderAPI->Submit(mesh);
    }

    //Renderer 2D

    void RenderCommand::DrawIndex(const Ref<VertexArray>& VAO, uint32_t count)
    {
        s_RenderAPI->DrawIndexd(VAO, count);
    }
    //void RenderCommand::SetUpEnviroment(const Ref<SceneData2D>& sceneData)
    //{
    //    s_RenderAPI->SetUpEnviroment(sceneData);
    //}


    
}