#include "PCH.h"
#include "CameraController.h"
#include "JSEngine/Managers/InputManager.h"

namespace JSEngine
{

///////////////////////////////////////////////3DCameraController/////////////////////////////////////////////////////////
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

    bool CameraController::OnWindowResizeCallBack(WindowReSizeEvent& event)
    {
        m_AspecRatio = (float)event.GetWidth() / (float)event.GetHeight();
        return true;
    }

///////////////////////////////////////////////2DCameraController/////////////////////////////////////////////////////////

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, const glm::vec2& pos) :
        m_Pos(pos.x, pos.y, 1.f),
        m_EnableRotation(false),
        m_AspecRatio(aspectRatio),
        m_ZoonLevel(1.f),
        m_Camera(-m_AspecRatio * m_ZoonLevel, m_AspecRatio* m_ZoonLevel, -m_ZoonLevel, m_ZoonLevel),
        m_CameraMoveSpeed(1.f),
        m_CameraRotationSpeed(glm::radians(120.f)),
        m_Bound{ -m_AspecRatio * m_ZoonLevel, m_AspecRatio * m_ZoonLevel, -m_ZoonLevel, m_ZoonLevel }
    {
        JS_PROFILE_FUNCTION();
        m_Camera.SetPosition(m_Pos);
    }

    void OrthographicCameraController::OnUpdate(TimeStep delta)
    {
        JS_PROFILE_FUNCTION();
        if (g_Input.IsKeyPressed(JS_KEY_W))
        {
            m_Pos.y += m_CameraMoveSpeed * delta;
        }
        else if (g_Input.IsKeyPressed(JS_KEY_S))
        {
            m_Pos.y -= m_CameraMoveSpeed * delta;
        }

        if (g_Input.IsKeyPressed(JS_KEY_A))
        {
            m_Pos.x -= m_CameraMoveSpeed * delta;

        }
        else if (g_Input.IsKeyPressed(JS_KEY_D))
        {
            m_Pos.x += m_CameraMoveSpeed * delta;
        }

        m_Camera.SetPosition(m_Pos);
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        JS_PROFILE_FUNCTION();
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrollEvent>(JS_BIND_EVENT(OrthographicCameraController::MouseScrollCallBack));
        dispatcher.Dispatch<WindowReSizeEvent>(JS_BIND_EVENT(OrthographicCameraController::OnWindowResizeCallBack));
    }

    bool OrthographicCameraController::MouseScrollCallBack(MouseScrollEvent& e)
    {
        JS_PROFILE_FUNCTION();
        m_ZoonLevel -= e.GetMouseYOffSet() * 0.1f;
        m_Bound = { -m_AspecRatio * m_ZoonLevel, m_AspecRatio * m_ZoonLevel, -m_ZoonLevel, m_ZoonLevel };
        m_Camera.SetProjMatrx(m_Bound.Left, m_Bound.Right, m_Bound.Bottom, m_Bound.Top);
        return true;
    }

    bool OrthographicCameraController::MouseMovementCallBack(MouseMoveEvent& e)
    {
        return true;
    }

    bool OrthographicCameraController::OnWindowResizeCallBack(WindowReSizeEvent& e)
    {
        JS_PROFILE_FUNCTION();
        m_AspecRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Bound = { -m_AspecRatio * m_ZoonLevel, m_AspecRatio * m_ZoonLevel, -m_ZoonLevel, m_ZoonLevel };
        m_Camera.SetProjMatrx(m_Bound.Left, m_Bound.Right, m_Bound.Bottom, m_Bound.Top);
        return true;
    }

}



