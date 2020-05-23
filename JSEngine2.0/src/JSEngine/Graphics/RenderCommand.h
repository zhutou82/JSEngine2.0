#pragma once
#include "glm/glm.hpp"
#include "RendererAPI.h"

namespace JSEngine
{

    class Shader;

    class RenderCommand
    {

    public:
        
        static void SetMainViewPort(uint32_t width, uint32_t height);
        static void Clear(const glm::vec4& color);
        static void AttachShader(const Ref<Shader>& shader);
        static void SetUpCamera();
        static void SetUpEnviroment(const Ref<SceneData>& sceneData);
        static void ClearScene();
        static void Submit(const Ref<Mesh>& mesh);
        static void DrawIndex(const Ref<Mesh>& mesh);

        //2D renderer commond
        static void DrawIndex(const Ref<VertexArray>& VAO, uint32_t count = 0);
        //static void SetUpEnviroment(const Ref<SceneData2D>& sceneData2D);

    private:

        static RendererAPI* s_RenderAPI;

        
    };


}