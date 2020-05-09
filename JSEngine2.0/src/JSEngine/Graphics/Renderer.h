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

        static void OnMainWindowMinimized(uint32_t width, uint32_t height);
        static void BeginScene(const Ref<SceneData>& sceneData);
        static void EndScene();
        static void Submit(const Ref<Mesh>& mesh);

        static void Flush();
        static RendererAPI::API GetGraphicsAPI() { return RendererAPI::GetAPI(); }

    private:

    };

    class OrthographicCameraController;

    /////////////////////////2D Renderer////////////////////////////////////////////////////

    class Texture;
    class Shader;
    class VertexArray;

    struct Vertex2D
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TextCoord;
        float TextID;
    };

    struct Stats
    {
        uint32_t NumberOfQuadDrawn = 0;
        uint32_t NumberOfIndicesDrawn = 0;
        uint32_t NumberOfVerticesDrawn = 0;
        uint32_t NumberOfDrawCall = 0;

        void Reset()
        {
            NumberOfQuadDrawn = 0;
            NumberOfIndicesDrawn = 0;
            NumberOfVerticesDrawn = 0;
            NumberOfDrawCall = 0;
        }
        void UpdateQaudDrawnStats()
        {
            NumberOfQuadDrawn += 1;
            NumberOfIndicesDrawn += 6;
            NumberOfVerticesDrawn += 4;
        }
    };

    struct SceneData2D
    {

        void Reset()
        {
           LastVertexPtr = BasePtr;
           NumberOfIndicesDrawn = 0;
        }

        Ref<Shader> Shader2D;
        Ref<VertexArray> VAO;

        static const uint32_t MaxTextureSlots = 32;

        static const uint32_t MaxNumberOfQuad = 100;
        static const uint32_t QuadVertexCount = 4;
        static const uint32_t QuadIndexCount = 6;
        static const uint32_t MaxNumberVertices = MaxNumberOfQuad * QuadVertexCount;
        static const uint32_t MaxNumberIndices = MaxNumberOfQuad * QuadIndexCount;

        uint32_t NumberOfIndicesDrawn;
        uint32_t NumberOfQuadsPerDrawCall;

        Vertex2D* BasePtr = nullptr;
        Vertex2D* LastVertexPtr = nullptr;

        //stats260716
        Stats RenderingStats;

        //texture
        std::array<Ref<Texture>, MaxTextureSlots> TextureArray;
        uint32_t CurrentTextureIndex = 0;
        glm::vec2 QuadTextCoord[4];

        //model
        glm::vec4 QuadOrigin[4];



    };

    class Renderer2D 
    {
    public:

        static void Init(); 
        static void OnMainWindowMinimized(uint32_t width, uint32_t height);
        static void BeginScene(const Ref<OrthographicCameraController>& camera);
        static void EndScene();
        static void Submit(const Ref<Mesh>& mesh);
        static void DrawQuad        (const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, int textureID);
        static void DrawRotatedQuad (const glm::vec2& pos, const glm::vec2& size, float rotationAngle, const glm::vec4& color, int textureID);
        static void DrawQuad        (const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, int textureID);
        static void DrawRotatedQuad (const glm::vec3& pos, const glm::vec2& size, float rotationAngle, const glm::vec4& color, int textureID);
        static void DrawAnimatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotationAngle, const glm::vec4& color, int textureID, int index);
        static void Flush();
        static RendererAPI::API GetGraphicsAPI() { return RendererAPI::GetAPI(); }

        static const SceneData2D& GetSceneData()  { return s_Data; }
        static const Stats&       GetSceneStats() { return s_Data.RenderingStats; }

        static void Shutdown();

    private:
        static void StartNewBatch();
        static SceneData2D s_Data;
    };


}