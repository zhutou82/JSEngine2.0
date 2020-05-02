#include "PCH.h"
#include "Light.h"
#include "JSEngine/Platform/Opengl/Mesh.h"


namespace JSEngine
{
    Light::Light(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& color, LightType lightType)
        : m_Ambient(ambient),
          m_Diffuse(diffuse),
          m_Specular(specular),
          m_Color(color),
          m_LightType(lightType)
    {

    }

    Ref<Light> Light::Create(LightType type)
    {
        switch (type)
        {
            case JSEngine::LightType::DIRECTIONAL_LIGHT: return std::make_shared<DirectionalLight>();
            case JSEngine::LightType::POINT_LIGHT: return  std::make_shared<PointLight>();
            case JSEngine::LightType::SPOT_LIGHT: return std::make_shared<Light>();
        }

        JS_CORE_ASSERT(false, "Unknow light type");
        return Ref<Light>();
    }


    PointLight::PointLight() :
        Light(), m_Mesh(Mesh::Create(MeshType::CUBE)), m_Pos({0,0,0})
    {
        m_LightType = LightType::POINT_LIGHT;
    }

    const glm::vec3& PointLight::GetPosition() const
    {
        return m_Pos;
        return m_Mesh->GetPosition();
    }

    const glm::mat4& PointLight::ConstructModelMatrix() const
    {
        return m_Mesh->ConstructModelMatrix();
    }

    const Ref<Mesh>& PointLight::GetMesh() const
    {
        return m_Mesh;
    }

    void PointLight::SetPosition(const glm::vec3& val)
    {
        m_Pos = val;
        m_Mesh->SetPosition(val);
    }

    

}
