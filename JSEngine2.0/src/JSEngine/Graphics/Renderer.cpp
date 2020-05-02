#include "PCH.h"
#include "Renderer.h"

namespace JSEngine
{
    void Renderer::BeginScene(const Ref<SceneData>& sceneData)
    {
        RenderCommand::SetUpCamera();
        RenderCommand::SetUpEnviroment(sceneData);
    }
    void Renderer::EndScene()
    {
        RenderCommand::DrawIndex(Ref<Mesh>());
    }
    void Renderer::Submit(const Ref<Mesh>& mesh)
    {
        RenderCommand::Submit(mesh); 
        //
    }

    void Renderer::Submit(const Ref<VertexArray>& vao)
    {
        RenderCommand::DrawIndex(vao);
    }

    void Renderer::Flush()
    {
        RenderCommand::ClearScene();
    }

}