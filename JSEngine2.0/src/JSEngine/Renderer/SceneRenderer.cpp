#include "PCH.h"
#include "SceneRenderer.h"
#include "JSEngine/Graphics/Renderer.h"
#include "JSEngine/Graphics/Camera.h"

namespace JSEngine
{
    struct EnvironmentInfo
    {
        Camera ActiveCamera;
        std::vector<Ref<Light>> Lights;
    };

    struct SceneRendererData
    {
        Scene3D* ActiveScene = nullptr;
        EnvironmentInfo Environment;
        struct DrawCommand
        {
            Ref<Mesh> Mesh;
            glm::mat4 Transform;
        };
        std::vector<DrawCommand> DrawList;


    };

    
    static SceneRendererData s_Data;

    void SceneRenderer::BeginScene(Scene3D* scene)
    {
        s_Data.ActiveScene = scene;
        s_Data.Environment.ActiveCamera = scene->m_Camera;
        s_Data.Environment.Lights = scene->m_Lights;

        Renderer::SubmitEnvironment(scene->m_Lights, scene->m_Camera);
    }

    void SceneRenderer::SubmitEntity(Entity* entity)
    {
        // TODO: Culling, sorting, etc.
        auto mesh = entity->GetMesh();
        if (!mesh)
        {
            JS_CORE_WARN("Entity: {0} has no mesh, is it on purpose? ", entity->GetName());
            return;
        }
        s_Data.DrawList.push_back({ mesh, entity->GetTransform() });
    }

    void SceneRenderer::EndScene()
    {
        Flush();
        s_Data.DrawList.clear();
        s_Data.ActiveScene = NULL;
    }

    void SceneRenderer::Flush()
    {
        for (const auto& elem : s_Data.DrawList)
        {
            Renderer::SubmitMesh(elem.Mesh, elem.Transform);
        }
    }

}