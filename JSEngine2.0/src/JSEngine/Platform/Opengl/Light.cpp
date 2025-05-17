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
        case JSEngine::LightType::DIRECTIONAL_LIGHT: return CreateRef<DirectionalLight>();
        case JSEngine::LightType::POINT_LIGHT:       return CreateRef<PointLight>();
        case JSEngine::LightType::SPOT_LIGHT:        return CreateRef<SpotLight>();
        }

        JS_CORE_ASSERT(false, "Unknow light type");
        return Ref<Light>();
    }


    PointLight::PointLight() :
        Light(), m_Pos({ 0,0,0 }), m_Constant(1.f), m_Linear(0.09f), m_Quadratic(0.032f)
    {
        m_LightType = LightType::POINT_LIGHT;
    }

    const glm::vec3& PointLight::GetPosition() const
    {
        return m_Pos;
    }

    void PointLight::SetPosition(const glm::vec3& val)
    {
        m_Pos = val;
    }

    DirectionalLight::DirectionalLight()
        : Light()
    {
        m_LightType = LightType::DIRECTIONAL_LIGHT;
    }

}
