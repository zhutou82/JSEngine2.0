#pragma once
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "JSEngine/Core/Core.h"
#include "JSEngine/Platform/Opengl/Light.h"

namespace JSEngine
{

    class Mesh;

    class Entity
    {

    public:

        ~Entity() = default;

        void SetScale(float scale)                                                         { SetScale (glm::vec3{scale}); }
        void SetScale(float x, float y, float z)                                           { SetScale ({ x, y ,z }); }
        void SetScale(const glm::vec3& scaleV)                                             { m_Scale = scaleV;  ConstructModelMatrix(); }

        void SetPosition(float x, float y, float z)                                        { SetPosition({x,y,z}); }
        void SetPosition(const glm::vec3& posV)                                            { m_Position = posV; ConstructModelMatrix(); }

        void SetRotation(float degree, const glm::vec3& rotationAxis = glm::vec3(0, 0, 1)) { m_RotationDegree = degree; m_RotationAxis = rotationAxis; ConstructModelMatrix(); }

        float GetRotation()         const { return m_RotationDegree; }
        glm::vec3 GetScale()        const { return m_Scale; }
        glm::vec3 GetPosition()     const { return m_Position; }
        glm::vec3 GetRotationAxis() const { return m_RotationAxis; }
        float GetRotationDegree()   const { return m_RotationDegree; }

        const glm::mat4& GetTransform() const { return m_Transform;  }

        void SetMesh(const Ref<Mesh>& mesh) { m_Mesh = mesh; }
        Ref<Mesh> GetMesh() { return m_Mesh; }

        void SetLight(const Ref<Light>& light) { m_Light = light; }
        const Ref<Light>& GetLight() const { return m_Light;  }

        const std::string& GetName() const { return m_Name; }

    private:
        friend class Scene3D;

        //entity can only be created through scene
        Entity(const std::string& name);
        void ConstructModelMatrix();

    private:


        std::string m_Name;

        glm::mat4 m_Transform;

        glm::vec3 m_Scale{ 1.f };
        glm::vec3 m_Position{ 0.f };
        glm::vec3 m_RotationAxis{ 0,0,1 };

        float m_RotationDegree{ 0.f };

        Ref<Mesh> m_Mesh;
        Ref<Light> m_Light;

    };


}