#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

#include "JSEngine/Platform/Opengl/Light.h"
#include "JSEngine/Platform/CameraController.h"
#include "JSEngine/Core/TimeStep.h"
#include "JSEngine/Event/Event.h"
#include "JSEngine/Graphics/Camera.h"

#include "Entity.h"

namespace JSEngine
{

    class Scene3D
    {

    public:

        Scene3D(const std::string& sceneName = "Scene");
        ~Scene3D();

        void Init(Camera camera);
        void OnUpdate(TimeStep delta);
        void OnEvent(Event& event);

        void CreatePointLight(const glm::vec3& pos);
        // const Ref<DirectionalLight>& GetEnvironmentLight() const { return m_DirectionLight; }
        // const std::vector<Ref<PointLight>>& GetPointLights() const { return m_PointLights; }
        const std::vector<Ref<Light>>& GetLights() const { return m_Lights; }
        const std::vector<Entity*>& GetEntities() const { return m_Entities; }

        Entity* CreateEntity(const std::string& name = "testObj");
        void AddEntity(Entity* entity);
        void AddToSceneEntity(Entity* entity);

    private:

        friend class SceneRenderer;


    private:
        //name
        std::string m_SceneName;

        //Camera
        Camera m_Camera;

        //Entities
        std::vector<Entity*> m_Entities;
        std::vector<Entity*> m_SceneEntities;
        


        //Light
        std::vector<Ref<Light>>      m_Lights;
        std::vector<Ref<PointLight>> m_PointLights;
        Ref<DirectionalLight>        m_DirectionLight;
       
         
        //Skybox

    };


}


