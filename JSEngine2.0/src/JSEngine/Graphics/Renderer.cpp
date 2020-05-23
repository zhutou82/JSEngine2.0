#include "PCH.h"
#include "Renderer.h"
#include "JSEngine/Managers/ResourceManager.h"
#include "JSEngine/Platform/CameraController.h"
#include "JSEngine/Platform/Opengl/Mesh.h"
#include "JSEngine/Platform/Opengl/Light.h"

namespace JSEngine
{
    Ref<SceneData> Renderer::s_Data;

    void Renderer::OnMainWindowMinimized(uint32_t width, uint32_t height)
    {
        RenderCommand::SetMainViewPort(width, height);
    }
    void Renderer::BeginScene(const Ref<SceneData>& sceneData)
    {
        s_Data = sceneData;
        //RenderCommand::SetUpEnviroment(sceneData);
        //RenderCommand::SetUpCamera();

        const auto& lightVec = sceneData->Lights;
        for (auto light : lightVec)
        {
            const auto& shader = s_Data->Shaders[light->GetAttachedShaderID()];
            LightType lightType = light->GetLightType();
            if (lightType == LightType::POINT_LIGHT)
            {
                auto& ptLight = CastLightTo<PointLight>(light);
                shader->AddToUniformVec("ptLight.pos", ptLight->GetPosition());
                shader->AddToUniformVec("ptLight.ambient", ptLight->GetAmbient());
                shader->AddToUniformVec("ptLight.color", ptLight->GetColor());
                shader->AddToUniformVec("ptLight.diffuse", ptLight->GetDiffuse());
                shader->AddToUniformVec("ptLight.specular", ptLight->GetSpecular());

                shader->AddToUniformVec("ptLight.constant", ptLight->GetConstant());
                shader->AddToUniformVec("ptLight.linear", ptLight->GetLinear());
                shader->AddToUniformVec("ptLight.quadratic", ptLight->GetQuadratic());

                s_Data->Meshes.push_back(ptLight->GetMesh());
            }
            else if (lightType == LightType::DIRECTIONAL_LIGHT)
            {
                auto& dirLight = CastLightTo<DirectionalLight>(light);
                dirLight->GetLightDirection();
                shader->AddToUniformVec("directionalLight.direction", dirLight->GetLightDirection());
                shader->AddToUniformVec("directionalLight.ambient", dirLight->GetAmbient());
                shader->AddToUniformVec("directionalLight.diffuse", dirLight->GetDiffuse());
                shader->AddToUniformVec("directionalLight.color", dirLight->GetColor());
                shader->AddToUniformVec("directionalLight.specular", dirLight->GetSpecular());
            }
            else if (lightType == LightType::SPOT_LIGHT)
            {



            }
        }

        for (const auto& elem : s_Data->Shaders)
        {
            //elem.second->AddToUniformVec("u_ViewProjMat", m_SceneData->OrthoGraphicsCam->GetCamera().GetViewProjectMatrix());
            elem.second->AddToUniformVec("u_ViewMat", g_CameraController.ConstructViewMat());
            elem.second->AddToUniformVec("u_ProjMat", g_CameraController.ConstructProjectMat());
            elem.second->AddToUniformVec("u_CameraPos", g_CameraController.GetPosition());
        }

    }
    void Renderer::EndScene()
    {
        //RenderCommand::DrawIndex(Ref<Mesh>());
        Flush();
    }
    
    void Renderer::Submit(const Ref<Mesh>& mesh)
    {
        s_Data->Meshes.push_back(mesh);
        //RenderCommand::Submit(mesh); 
    }

    void Renderer::SubmitMesh(const Ref<Mesh>& mesh, const glm::mat4& transform)
    {
        s_Data->Meshes.push_back(mesh);
    }

    void Renderer::DrawMesh()
    {
        for (const auto& mesh : s_Data->Meshes)
        {
            const auto& shader = s_Data->Shaders[mesh->GetShaderID()];
            shader->AddToUniformVec("u_ModelMat", mesh->ConstructModelMatrix());
            //shader->AddToUniformVec("material.shininess", mesh->GetMeterial()->GetShinese());
            //shader->AddToUniformVec("material.diffuse", mesh->GetMeterial()->GetDiffuse());
            //shader->AddToUniformVec("material.specular", mesh->GetMeterial()->GetSpecular());
            shader->Bind();
            int textureSlots[32] = { 0 };
            for (const auto& texture : mesh->GetTextures())
            {
                //shader->AddToUniformVec(texture->GetTextureName(), (int32_t)texture->GetTextureID());
                //texture->Bind(texture->GetTextureID());
                textureSlots[texture->GetTextureID()] = texture->GetTextureID();
            }
            shader->SetIntArrary("u_Textures", 32, textureSlots);
            mesh->Bind();
            for (const auto& subMesh : mesh->GetSubMeshes())
            {
                shader->AddToUniformVec("u_AlbedoMapIndex", (int)subMesh.AlbedoMapIndex);
                g_ResourceMgr.Acquire2DTexture(subMesh.AlbedoMapIndex)->Bind(subMesh.AlbedoMapIndex);
                glDrawElementsBaseVertex(GL_TRIANGLES, subMesh.IndexCount, GL_UNSIGNED_INT, (void*)(sizeof(uint32_t) * subMesh.BaseIndex), subMesh.BaseVertex);
            }
            shader->UploadUnfiromVec();
        }
    }

    void Renderer::Flush()
    {
        DrawMesh();
        for (const auto& elem : s_Data->Shaders)
        {
            elem.second->UnloadUniformVec();
        }
        s_Data->Meshes.clear();

        //RenderCommand::ClearScene();
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
         

        s_Data.QuadOrigin[0] = { -0.5f, -0.5f, 0.f, 1.f };
        s_Data.QuadOrigin[1] = {  0.5f, -0.5f, 0.f, 1.f };
        s_Data.QuadOrigin[2] = {  0.5f,  0.5f, 0.f, 1.f };
        s_Data.QuadOrigin[3] = { -0.5f,  0.5f, 0.f, 1.f };

        s_Data.QuadTextCoord[0] = { 0.f, 0.f };
        s_Data.QuadTextCoord[1] = { 1.f, 0.f };
        s_Data.QuadTextCoord[2] = { 1.f, 1.f };
        s_Data.QuadTextCoord[3] = { 0.f, 1.f };

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

        if (s_Data.TextureIDArray.find(textureID) == s_Data.TextureIDArray.end())
        {
            s_Data.TextureIDArray.insert(textureID);
        }

    }

    void Renderer2D::DrawSubTextureQuad(const glm::vec3& pos, const glm::vec2& size, float rotationAngle, const glm::vec4& color, const Ref<SubTexture2D>& subTexture)
    {
        if (s_Data.NumberOfIndicesDrawn >= s_Data.NumberOfQuadsPerDrawCall * s_Data.QuadIndexCount)
        {
            StartNewBatch();
        }
        glm::mat4 Transform = glm::translate(glm::mat4(1.f), glm::vec3(pos.x, pos.y, pos.z)) *
                              glm::rotate(glm::mat4(1.f), rotationAngle, glm::vec3(0, 0, 1.f)) *
                              glm::scale(glm::mat4(1.f), glm::vec3(size.x, size.y, 1.f));

        int textureID = subTexture->GetTextureID();
        for (uint32_t i = 0; i < s_Data.QuadVertexCount; ++i)
        {
            s_Data.LastVertexPtr->Position = Transform * s_Data.QuadOrigin[i];
            s_Data.LastVertexPtr->Color = color;
            s_Data.LastVertexPtr->TextCoord = subTexture->GetTextureCoord()[i];
            s_Data.LastVertexPtr->TextID = (float)textureID;
            ++s_Data.LastVertexPtr;
        }
        s_Data.RenderingStats.UpdateQaudDrawnStats();
        s_Data.NumberOfIndicesDrawn += s_Data.QuadIndexCount;

        if (s_Data.TextureIDArray.find(textureID) == s_Data.TextureIDArray.end())
        {
            s_Data.TextureIDArray.insert(textureID);
        }

    }

    void Renderer2D::DrawAnimatedQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture>& texture, const Ref<Animation2D>& animation)
    {

        if (s_Data.NumberOfIndicesDrawn >= s_Data.NumberOfQuadsPerDrawCall * s_Data.QuadIndexCount)
        {
            StartNewBatch();
        }
        glm::mat4 Transform = glm::translate(glm::mat4(1.f), glm::vec3(pos.x, pos.y, pos.z)) *
                              glm::rotate(glm::mat4(1.f), 0.f, glm::vec3(0, 0, 1.f)) *
                              glm::scale(glm::mat4(1.f), glm::vec3(size.x, size.y, 1.f));


        int textureID = texture->GetTextureID();
        for (uint32_t i = 0; i < s_Data.QuadVertexCount; ++i)
        {
            s_Data.LastVertexPtr->Position = Transform * s_Data.QuadOrigin[i];
            s_Data.LastVertexPtr->Color = {1,1,1,1};
            s_Data.LastVertexPtr->TextCoord = animation->GetTextureCoord()[i];
            s_Data.LastVertexPtr->TextID = (float)textureID;
            ++s_Data.LastVertexPtr;
        }
        s_Data.RenderingStats.UpdateQaudDrawnStats();
        s_Data.NumberOfIndicesDrawn += s_Data.QuadIndexCount;


        if (s_Data.TextureIDArray.find(textureID) == s_Data.TextureIDArray.end())
        {
            s_Data.TextureIDArray.insert(textureID);
        }


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
        int textureSlots[s_Data.MaxTextureSlots] = { 0 };
        for (const auto& textureID : s_Data.TextureIDArray)
        {
            textureSlots[textureID] = textureID;
        }
        s_Data.Shader2D->SetIntArrary("u_Textures", s_Data.MaxTextureSlots, textureSlots);

        for (const auto& textureID : s_Data.TextureIDArray)
        {
            g_ResourceMgr.Acquire2DTexture(textureID)->Bind(textureID);
        }
        RenderCommand::DrawIndex(s_Data.VAO, s_Data.NumberOfIndicesDrawn);
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