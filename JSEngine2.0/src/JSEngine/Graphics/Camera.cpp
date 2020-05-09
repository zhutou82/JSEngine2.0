#include "PCH.h"
#include "Camera.h"

namespace JSEngine
{

    const glm::mat4& Camera::ConstructViewMat()
    {
        m_ViewMat = glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
        return m_ViewMat;
    }

    const glm::mat4& Camera::ConstructProjectMat()
    {
        m_ProjMat = glm::perspective(glm::radians(m_FOV), m_AspecRatio, m_NearPlane, m_FarPlane);
        return m_ProjMat;
    }


    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_ViewMat(1.f), 
          m_ProjMat(glm::ortho(left, right, bottom, top, 1.f, -1.f)),
          m_ViewProjMatrix(1.f),
          m_Pos(1.f),
          m_Rotation(0.f)
    {

    }
    void OrthographicCamera::SetProjMatrx(float left, float right, float bottom, float top)
    {
        m_ProjMat = glm::ortho(left, right, bottom, top, 1.f, -1.f);
        ReCalculateViewProjMat();
    }

    void OrthographicCamera::ReCalculateViewProjMat()
    {
        m_ViewMat = glm::translate(glm::mat4(1.f), m_Pos) * glm::rotate(glm::mat4(1.f), m_Rotation, glm::vec3(0, 0, 1));
        m_ViewMat = glm::inverse(m_ViewMat);

        m_ViewProjMatrix = m_ProjMat * m_ViewMat;
    }

}