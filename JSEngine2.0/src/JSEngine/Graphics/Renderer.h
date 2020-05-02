#pragma once
#include <memory>
#include <vector>
#include "RenderCommand.h"

namespace JSEngine
{
    class Light;
    class Camera;
    class VertexArray;
    class Mesh;

    struct SceneData
    {
        std::vector<Ref<Light>> Lights;
        std::vector <Ref<Mesh>> Meshes;

    };

    class Renderer
    {

    public:
        
        static void BeginScene(const Ref<SceneData>& sceneData);
        static void EndScene();
        static void Submit(const Ref<Mesh>& mesh);
        static void Submit(const Ref<VertexArray>& vao);
        static void Flush();
        static RendererAPI::API GetGraphicsAPI() { return RendererAPI::GetAPI(); }

    private:



    };

}