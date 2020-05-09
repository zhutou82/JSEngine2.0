#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "VertexArray.h"
#include "JSEngine/Core/Core.h"


namespace JSEngine
{
    class Mesh;
    class Shader;
    struct SceneData;
    struct SceneData2D;

    class RendererAPI
    {
    public:
        
        enum class API
        {
            NONE = 0,
            OPENGL = 1,
            DIRECT3D = 2
        };

        virtual void SetMainViewPort(uint32_t width, uint32_t height) = 0;

        virtual void Clear(const glm::vec4& color) = 0;

        virtual void DrawIndexd(const Ref<Mesh>& mesh) = 0;
        virtual void Submit(const Ref<Mesh>& mesh) = 0;

        virtual void AttachShader(const Ref<Shader>& ) = 0;
        virtual void SetUpCamera() = 0;
        virtual void SetUpEnviroment(const Ref<SceneData>& sceneData) = 0;

        virtual void ClearSceneData() = 0;

        static API GetAPI() { return s_API; }
        static void SetAPI(API api) { s_API = api; }

        //Renderer 2D API
        virtual void DrawIndexd(const Ref<VertexArray>& VAO, uint32_t count) = 0;

    private:

        static API s_API;

    };

    

}