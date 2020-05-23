#pragma once
#include "glm/glm.hpp"


#define CAST_LIGHT_TO(type, x) std::static_pointer_cast<JSEngine::Ref<type>::element_type>(x)

namespace JSEngine
{
    
    class Mesh;
    enum class LightType
    {
        DIRECTIONAL_LIGHT,
        POINT_LIGHT,
        SPOT_LIGHT
    };

     //CastLightTo<DirectionalLight>(light)

    class Light
    {

    public:

        Light(const glm::vec3& ambient = { 0.1f, 0.1f, 0.1f }, const glm::vec3& diffuse = { 0.5f, 0.5f, 0.5f }, const glm::vec3& specular = { 0.5f, 0.5f, 0.5f },
              const glm::vec3& color = glm::vec3(1, 1, 1), LightType lightType = LightType::POINT_LIGHT);


        const glm::vec3& GetAmbient() const { return m_Ambient; }
        void SetAmbient(const glm::vec3& val) { m_Ambient = val; }

        const glm::vec3& GetDiffuse() const { return m_Diffuse; }
        void SetDiffuse(const glm::vec3& val) { m_Diffuse = val; }

        const glm::vec3& GetSpecular() const { return m_Specular; }
        void SetSpecular(const glm::vec3& val) { m_Specular = val; }

        glm::vec3 GetColor() const { return m_Color; }
        void SetColor(glm::vec3 val) { m_Color = val; }

        LightType GetLightType() const { return m_LightType; }
        void SetLightType(LightType val) { m_LightType = val; }

        uint32_t GetAttachedShaderID() const { return m_AttachedShaderID; }
        void SetAttachedShaderID(uint32_t val) { m_AttachedShaderID = val; }

        uint32_t GetID() const { return m_ID; }
        void SetID(uint32_t val) { m_ID = val; }

        

        static Ref<Light> Create(LightType type);

    protected:

        glm::vec3 m_Color;
        glm::vec3 m_Ambient;
        glm::vec3 m_Diffuse;
        glm::vec3 m_Specular;
        LightType m_LightType;
        uint32_t m_AttachedShaderID;
        uint32_t m_ID;

    };


    class DirectionalLight : public Light
    {

    public:
        DirectionalLight();

        const glm::vec3& GetLightDirection() const { return m_Direction; }
        void SetLightDirection(const glm::vec3& val) { m_Direction = val; }


    private:
        glm::vec3 m_Direction;
    };


    class PointLight : public Light
    {

    public:
        PointLight();

        const glm::vec3& GetPosition() const;
        void SetPosition(const glm::vec3& val);

        const glm::mat4& ConstructModelMatrix() const;
        const Ref<Mesh>& GetMesh() const;

        float GetConstant() const { return m_Constant; }
        void SetConstant(float val) { m_Constant = val; }

        float GetLinear() const { return m_Linear; }
        void SetLinear(float val) { m_Linear = val; }

        float GetQuadratic() const { return m_Quadratic; }
        void SetQuadratic(float val) { m_Quadratic = val; }
    private:
        glm::vec3 m_Pos;
        Ref<Mesh> m_Mesh;

        float m_Constant;
        float m_Linear;
        float m_Quadratic; 
    };

    class SpotLight : public Light
    {

    public:


    private:

        glm::vec3 m_Pos;
        glm::vec3 m_Direction;

    };

    template <typename T>
    Ref<T> CastLightTo(const Ref<Light>& light)
    {
        return std::static_pointer_cast<Ref<T>::element_type>(light);
    }

}