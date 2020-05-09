#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace JSEngine
{
    class Camera 
    {

    public:

        ~Camera() {}
        
        
        const glm::mat4& ConstructViewMat();
        const glm::mat4& ConstructProjectMat();

        const glm::vec3& GetPosition() const { return m_Pos; }
        void SetPosition(glm::vec3 val) { m_Pos = val; }

        float GetAspecRatio() const { return m_AspecRatio; }
        void SetAspecRatio(float val) { m_AspecRatio = val; }

    protected:
        Camera() {};

        //view matrix
        glm::vec3 m_Front;
        glm::vec3 m_Pos;
        glm::vec3 m_Up;
        glm::mat4 m_ViewMat;

        //perspective projection
        float m_FOV;
        float m_NearPlane;
        float m_FarPlane;
        float m_AspecRatio;
        glm::mat4 m_ProjMat;

    };

    class OrthographicCamera
    {
    public:
        OrthographicCamera() {}
        OrthographicCamera(float left, float right, float top, float bottom);

        void SetProjMatrx(float left, float right, float top, float bottom);
        const glm::mat4& GetViewProjectMatrix() const {
            return m_ViewProjMatrix; 
        }

        const glm::vec3& GetPosition() const { return m_Pos; }
        void SetPosition(const glm::vec3& val) { m_Pos = val; ReCalculateViewProjMat();  }

        float GetRotation() const { return m_Rotation; }
        void SetRotation(float val) { m_Rotation = val; ReCalculateViewProjMat(); }

    private:

        void ReCalculateViewProjMat();

    private:
        
        //matrix
        glm::mat4 m_ViewMat;
        glm::mat4 m_ProjMat;
        glm::mat4 m_ViewProjMatrix;

        glm::vec3 m_Pos;
        float m_Rotation;
    };


}