#include "PCH.h"
#include "CameraController.h"
#include "JSEngine/Managers/InputManager.h"

namespace JSEngine
{

    void CameraController::Init(const glm::vec3& camStartPos, float aspecRatio, float fov, float nearPlane, float farPlane)
    {
        m_Pos = camStartPos;
        m_Up = { 0, 1, 0 };
        m_Front = { 0, 0, -1 };

        m_CameraSensitivity = 0.05f;
        m_CameraScrollSpeed = 5.f;
        m_CameraMoveSpeed = 5.f;

        m_Yaw = -90.f;
        m_Pictch = 0.f;

        m_NearPlane = s_NearPlane;
        m_FarPlane = s_FarPlane;
        m_FOV = s_FOV;
        m_AspecRatio = aspecRatio;

    }

    void CameraController::OnUpdate(TimeStep delta)
    {
        if (g_Input.IsKeyPressed(JS_KEY_W))
        {
            m_Pos += glm::normalize(m_Front) * (m_CameraMoveSpeed * delta);

        }
        else if (g_Input.IsKeyPressed(JS_KEY_S))
        {
            m_Pos -= glm::normalize(m_Front) * (m_CameraMoveSpeed * delta);
        }

        if (g_Input.IsKeyPressed(JS_KEY_A))
        {
            m_Pos -= glm::normalize(glm::cross(m_Front, m_Up)) * (m_CameraMoveSpeed * delta);
        }
        else if (g_Input.IsKeyPressed(JS_KEY_D))
        {
            m_Pos += glm::normalize(glm::cross(m_Front, m_Up)) * (m_CameraMoveSpeed * delta);
        }

        if (g_Input.IsKeyPressed(JS_KEY_Q))
        {
            m_Pos += glm::normalize(m_Up) * (m_CameraMoveSpeed * delta);
        }
        else if (g_Input.IsKeyPressed(JS_KEY_E))
        {
            m_Pos -= glm::normalize(m_Up) * (m_CameraMoveSpeed * delta);
        }
    }

    void CameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrollEvent>(JS_BIND_EVENT(CameraController::CursorScrollCallBack));
        dispatcher.Dispatch<MouseMoveEvent>(JS_BIND_EVENT(CameraController::CursorPosCallBack));
    }

    bool CameraController::CursorScrollCallBack(MouseScrollEvent& event)
    {
        float yOffset = event.GetMouseYOffSet();
        yOffset *= m_CameraScrollSpeed;
        m_FOV -= yOffset;

        if (m_FOV > s_MaxFOV) m_FOV = s_MaxFOV;
        if (m_FOV < s_MinFOV) m_FOV = s_MinFOV;

        return true;
    }

    bool CameraController::CursorPosCallBack(MouseMoveEvent& event)
    {
        static bool firstMouse = true;
        float xPos = event.GetMouseXCoordinate();
        float yPos = event.GetMouseYCoordinate();
        if (firstMouse)
        {
            m_PreXpos = xPos;
            m_PreYpos = yPos;
            firstMouse = false;
        }

        float xOffset = xPos - m_PreXpos;
        float yOffset = -(yPos - m_PreYpos);

        m_PreXpos = xPos;
        m_PreYpos = yPos;

        xOffset *= m_CameraSensitivity;
        yOffset *= m_CameraSensitivity;

        m_Yaw += xOffset;
        m_Pictch += yOffset;

        if (m_Pictch > s_MaxUpAngle) m_Pictch = s_MaxUpAngle;
        if (m_Pictch < s_MaxDownAngle) m_Pictch = s_MaxDownAngle;

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pictch));
        direction.y = sin(glm::radians(m_Pictch));
        direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pictch));

        m_Front = glm::normalize(direction);

        return true;
    }

}



