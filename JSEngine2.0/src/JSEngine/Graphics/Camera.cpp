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




}