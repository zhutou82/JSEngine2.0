#include "PCH.h"
#include "Renderer.h"
#include "JSEngine/Managers/ResourceManager.h"
#include "JSEngine/Platform/CameraController.h"

namespace JSEngine
{
    void Renderer::OnMainWindowMinimized(uint32_t width, uint32_t height)
    {
        RenderCommand::SetMainViewPort(width, height);
    }
    void Renderer::BeginScene(const Ref<SceneData>& sceneData)
    {
        RenderCommand::SetUpEnviroment(sceneData);
        RenderCommand::SetUpCamera();
    }
    void Renderer::EndScene()
    {
        RenderCommand::DrawIndex(Ref<Mesh>());
    }

    void Renderer::Submit(const Ref<Mesh>& mesh)
    {
        RenderCommand::Submit(mesh); 
    }

    void Renderer::Flush()
    {
        RenderCommand::ClearScene();
    }


/////////////////////////2D Renderer////////////////////////////////////////////////////
    SceneData2D Renderer2D::s_Data;
    void Renderer2D::Init()
    {
        //create quad
        s_Data.VAO = JSEngine::VertexArray::Create();
        JSEngine::Ref<JSEngine::VertexBuffer> vbo = JSEngine::VertexBuffer::Create(s_Data.MaxNumberVertices * sizeof(Vertex2D));

        JSEngine::Layout layout
        {
            {JSEngine::ElementType::VEC3, 0, "Pos"},
            {JSEngine::ElementType::VEC4, 1, "Color"},
            {JSEngine::ElementType::VEC2, 2, "TextCoord"},
            {JSEngine::ElementType::FLOAT, 3, "TextureID"},
        };

        vbo->SetLayout(layout);
        s_Data.VAO->AddBuffer(vbo);

        s_Data.BasePtr = new Vertex2D[s_Data.MaxNumberVertices];

        uint32_t* indexBufferData = new uint32_t[s_Data.MaxNumberIndices];

        //indice buffer
        int offset = 0;
        for (uint32_t i = 0; i < s_Data.MaxNumberIndices; i += s_Data.QuadIndexCount)
        {
            indexBufferData[i + 0] = offset + 0;
            indexBufferData[i + 1] = offset + 1;
            indexBufferData[i + 2] = offset + 2;

            indexBufferData[i + 3] = offset + 0;
            indexBufferData[i + 4] = offset + 2;
            indexBufferData[i + 5] = offset + 3;

            offset += s_Data.QuadVertexCount;
        }
        JSEngine::Ref<JSEngine::IndexBuffer> ibo = JSEngine::IndexBuffer::Create(indexBufferData, s_Data.MaxNumberIndices);
        s_Data.VAO->AddIndexBuffer(ibo);
        delete[] indexBufferData;

        s_Data.Shader2D = g_ResourceMgr.AcquireShader("2DShader");
        s_Data.TextureArray[s_Data.CurrentTextureIndex++] = g_ResourceMgr.Acquire2DTexture("awesomeface");
        s_Data.TextureArray[s_Data.CurrentTextureIndex++] = g_ResourceMgr.Acquire2DTexture("Bobo");
        s_Data.TextureArray[s_Data.CurrentTextureIndex++] = g_ResourceMgr.Acquire2DTexture("blue_ninja");

        int textureSlots[8] = { 0 };

        for (uint32_t i = 0; i < s_Data.CurrentTextureIndex; ++i)
        {
            textureSlots[i] = s_Data.TextureArray[i]->GetTextureID();
        }

        s_Data.Shader2D->Bind();
        s_Data.Shader2D->SetIntArrary("u_Textures", 8, textureSlots);

        s_Data.QuadOrigin[0] = { -0.5f, -0.5f, 0.f, 1.f };
        s_Data.QuadOrigin[1] = {  0.5f, -0.5f, 0.f, 1.f };
        s_Data.QuadOrigin[2] = {  0.5f,  0.5f, 0.f, 1.f };
        s_Data.QuadOrigin[3] = { -0.5f,  0.5f, 0.f, 1.f };



        s_Data.NumberOfQuadsPerDrawCall = s_Data.MaxNumberOfQuad;
    }

    void Renderer2D::BeginScene(const Ref<OrthographicCameraController>& camera) 
    {
        s_Data.Shader2D->UnloadUniformVec();

        s_Data.Shader2D->AddToUniformVec("u_ViewProjMat", camera->GetCamera().GetViewProjectMatrix());
        s_Data.RenderingStats.Reset();

        s_Data.Reset();
        
    }
    void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, int textureID)
    {
        DrawRotatedQuad(pos, size, 0.f, color, textureID);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotationAngle, const glm::vec4& color, int textureID)
    {
        DrawRotatedQuad(glm::vec3(pos.x, pos.y, 0.f), size, rotationAngle, color, textureID);
    }

    void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, int textureID)
    {
        DrawRotatedQuad(pos, size, 0.f, color, textureID);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotationAngle, const glm::vec4& color, int textureID)
    {
        if (s_Data.NumberOfIndicesDrawn >= s_Data.NumberOfQuadsPerDrawCall * s_Data.QuadIndexCount)
        {
            StartNewBatch();
        }

        glm::mat4 Transform = glm::translate(glm::mat4(1.f), glm::vec3(pos.x, pos.y, pos.z)) *
                              glm::rotate(glm::mat4(1.f), rotationAngle, glm::vec3(0, 0, 1.f)) *
                              glm::scale(glm::mat4(1.f), glm::vec3(size.x, size.y, 1.f));

        for (uint32_t i = 0; i < s_Data.QuadVertexCount; ++i)
        {
            s_Data.LastVertexPtr->Position = Transform * s_Data.QuadOrigin[i];
            s_Data.LastVertexPtr->Color = color;
            s_Data.LastVertexPtr->TextCoord = s_Data.QuadTextCoord[i];
            s_Data.LastVertexPtr->TextID = (float)textureID;
            ++s_Data.LastVertexPtr;
        }
        s_Data.RenderingStats.UpdateQaudDrawnStats();
        s_Data.NumberOfIndicesDrawn += s_Data.QuadIndexCount;
    }

    void Renderer2D::DrawAnimatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotationAngle, const glm::vec4& color, int textureID, int index)
    {
        glm::mat4 Transform = glm::translate(glm::mat4(1.f), glm::vec3(pos.x, pos.y, pos.z)) *
            glm::rotate(glm::mat4(1.f), rotationAngle, glm::vec3(0, 0, 1.f)) *
            glm::scale(glm::mat4(1.f), glm::vec3(size.x, size.y, 1.f));

        //glm::ivec2 dim{ 10, 2 };
        //index = 12;
        //glm::vec4 uvs;
        //int xTile = index % dim.x;
        //int yTile = index / dim.x;

        //uvs.x = xTile / (float)dim.x;
        //uvs.y = yTile / (float)dim.y;
        //uvs.z = 1.f / dim.x;
        //uvs.w = 1.f / dim.y;

        //s_Data.QuadTextCoord[0] = { uvs.x        , uvs.y };
        //s_Data.QuadTextCoord[1] = { uvs.x + uvs.z, uvs.y };
        //s_Data.QuadTextCoord[2] = { uvs.x + uvs.z, uvs.y + uvs.w };
        //s_Data.QuadTextCoord[3] = { uvs.x        , uvs.y + uvs.w };

        s_Data.QuadTextCoord[0] = { 0.2f, 0.5f };
        s_Data.QuadTextCoord[1] = { 0.3f, 0.5f };
        s_Data.QuadTextCoord[2] = { 0.3f, 1.0f };
        s_Data.QuadTextCoord[3] = { 0.2f, 1.0f };

        for (uint32_t i = 0; i < s_Data.QuadVertexCount; ++i)
        {
            s_Data.LastVertexPtr->Position = Transform * s_Data.QuadOrigin[i];
            s_Data.LastVertexPtr->Color = color;
            s_Data.LastVertexPtr->TextCoord = s_Data.QuadTextCoord[i];
            s_Data.LastVertexPtr->TextID = (float)textureID;
            ++s_Data.LastVertexPtr;
        }
        s_Data.RenderingStats.UpdateQaudDrawnStats();
        s_Data.NumberOfIndicesDrawn += s_Data.QuadIndexCount;
    }

    void Renderer2D::EndScene()
    {
        uint64_t size = (uint8_t*)s_Data.LastVertexPtr - (uint8_t*)s_Data.BasePtr;
        s_Data.VAO->GetVertexBuffer().back()->SetData(s_Data.BasePtr, (uint32_t)size);

        ++s_Data.RenderingStats.NumberOfDrawCall;
    }

    void Renderer2D::Flush()
    {
        s_Data.Shader2D->UploadUnfiromVec();
        for (uint32_t i = 0; i < s_Data.CurrentTextureIndex; ++i)
        {
            s_Data.TextureArray[i]->Bind(i);
        }
        RenderCommand::DrawIndex(s_Data.VAO, s_Data.MaxNumberIndices);
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data.BasePtr;
    }

    void Renderer2D::StartNewBatch()
    {
        EndScene();
        Flush();
        s_Data.Reset();
    }

    void Renderer2D::Submit(const Ref<Mesh>& mesh)
    {

    }

    void Renderer2D::OnMainWindowMinimized(uint32_t width, uint32_t height)
    {
        RenderCommand::SetMainViewPort(width, height);
    }

}