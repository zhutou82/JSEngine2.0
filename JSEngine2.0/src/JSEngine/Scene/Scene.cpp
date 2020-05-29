#include "PCH.h"
#include "Scene.h"
#include "JSEngine/Platform/Opengl/Mesh.h"
#include "JSEngine/Platform/Opengl/Light.h"

#include "JSEngine/Renderer/SceneRenderer.h"

namespace JSEngine
{

    Scene3D::Scene3D(const std::string& sceneName /*= "Scene"*/)
        : m_SceneName(sceneName)
    {

    }

    Scene3D::~Scene3D()
    {
        for (auto& elem : m_Entities)
            delete elem;
    }

    void Scene3D::Init(Camera camera)
    {
        //reserve 1000 entities
        m_Entities.reserve(1000);

        m_Camera = camera;
        //TODO init skybox


        //Init environment light
        Entity* newEntity = CreateEntity("diretionalLight"); 
        Ref<Light> dirLight = Light::Create(LightType::DIRECTIONAL_LIGHT);
        auto& directionalLight = std::static_pointer_cast<Ref<DirectionalLight>::element_type>(dirLight);
        directionalLight->SetLightDirection({ -0.2f, -1.f, -0.3f });

        newEntity->SetLight(dirLight);
        newEntity->SetMesh(CreateRef<Mesh>(MeshType::CUBE, "Light"));

        newEntity->SetPosition({1,1,1});
        newEntity->SetScale(0.25f);

        m_Lights.push_back(dirLight);

    }

    void Scene3D::OnUpdate(TimeStep delta)
    {
        m_Camera.OnUpdate(delta);
        SceneRenderer::BeginScene(this);

        //submit entity
        for (const auto& entity : m_Entities)
        {
            SceneRenderer::SubmitEntity(entity);
        }

        SceneRenderer::EndScene();
    }

    void Scene3D::OnEvent(Event& event)
    {
        m_Camera.OnEvent(event);
    }

    void Scene3D::CreatePointLight(const glm::vec3& pos)
    {
        Entity* newEntity = CreateEntity("ptLight");
        Ref<Light> light = Light::Create(LightType::POINT_LIGHT);

        newEntity->SetLight(light);
        newEntity->SetMesh(CreateRef<Mesh>(MeshType::CUBE, "Light"));
        newEntity->SetPosition(pos);
        newEntity->SetScale(0.25f);
        m_Lights.push_back(light);
    }

    Entity* Scene3D::CreateEntity(const std::string& name)
    {
        Entity* newEntity = new Entity(name);
        AddEntity(newEntity);
        return newEntity;
    }

    void Scene3D::AddEntity(Entity* entity)
    {
        m_Entities.push_back(entity);
    }

    void Scene3D::AddToSceneEntity(Entity* entity)
    {
        m_SceneEntities.push_back(entity);
    }

}