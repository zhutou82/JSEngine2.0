#include "PCH.h"
#include "Light.h"
#include "OpenGLRenderAPI.h"
#include "JSEngine/Platform/Opengl/Mesh.h"
#include "JSEngine/Graphics/Renderer.h"
#include "JSEngine/Platform/CameraController.h"
#include "JSEngine/Managers/ResourceManager.h"



namespace JSEngine
{
    void OpenGLRendererAPI::SetMainViewPort(uint32_t width, uint32_t height)
    {
        //g_CameraController.SetAspecRatio((float)width / (float)height);
        glViewport(0, 0, width, height);
    }  
    void OpenGLRendererAPI::Clear(const glm::vec4& color)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::DrawIndexd(const Ref<Mesh>& m)
    {

        for (const auto& mesh : m_SceneData->Meshes)
        {
            const auto& shader = m_IDShaderMap[mesh->GetShaderID()];
            shader->AddToUniformVec("u_ModelMat", mesh->ConstructModelMatrix());
            shader->AddToUniformVec("material.shinese", mesh->GetMaterial()->GetShinese());
            shader->AddToUniformVec("u_TextureID", 0);

            shader->UploadUnfiromVec();

            mesh->Bind();
            mesh->GetTexture()->Bind();
            glDrawElements(GL_TRIANGLES, mesh->GetVAO()->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        }
    }

    void OpenGLRendererAPI::UploadUniforms(const Ref<Shader>& shader)
    {
        shader->UploadUnfiromVec();
    }

    void OpenGLRendererAPI::UploadAllShaderUniforms()
    {
        for (const auto& shader : m_IDShaderMap)
        {
            shader.second->UploadUnfiromVec();
        }
    }

    void OpenGLRendererAPI::AttachShader(const Ref<Shader>& shader)
    {
        m_IDShaderMap[shader->GetShaderID()] = shader;
    }



    void OpenGLRendererAPI::SetUpCamera()
    {

    }

    void OpenGLRendererAPI::SetUpEnviroment(const Ref<SceneData>& sceneData)
    {

    }

    void OpenGLRendererAPI::ClearSceneData()
    {
        for (const auto& elem : m_IDShaderMap)
        {
            elem.second->UnloadUniformVec();
        }
        m_SceneData->Meshes.clear();
    }

    void OpenGLRendererAPI::Submit(const Ref<Mesh>& mesh)
    {
        m_SceneData->Meshes.push_back(mesh);
    }



    //////////////////////////////////////2D renderer API/////////////////////////////////////////////

    void OpenGLRendererAPI::DrawIndexd(const Ref<VertexArray>& VAO, uint32_t count)
    {
        VAO->Bind();
        VAO->GetIndexBuffer()->Bind();
        uint32_t vertexCount = count ? count : VAO->GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr);


    }


    


}

