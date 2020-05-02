#pragma once
#include "glm/glm.hpp"
#include "RendererAPI.h"

namespace JSEngine
{

    class Shader;

    class RenderCommand
    {

    public:
        
        static void Clear(const glm::vec4& color);
        static void DrawIndex(const Ref<Mesh>& VAO);
        static void DrawIndex(const Ref<VertexArray>& VAO);
        static void AttachShader(const Ref<Shader>& shader);
        static void SetUpCamera();
        static void SetUpEnviroment(const Ref<SceneData>& sceneData);
        static void ClearScene();
        static void Submit(const Ref<Mesh>& mesh);

    private:

        static RendererAPI* s_RenderAPI;

        
    };


}