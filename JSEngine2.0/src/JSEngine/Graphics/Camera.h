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

        //

    };


}