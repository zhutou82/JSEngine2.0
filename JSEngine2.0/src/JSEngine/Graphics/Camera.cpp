#include "PCH.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/ext/quaternion_transform.hpp>

#include "Camera.h"
#include "JSEngine/Managers/InputManager.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace JSEngine
{
#define PI glm::pi<float>()

    Camera::Camera(const glm::mat4& projMat)
        : m_ProjMat(projMat)
    {
        m_Yaw = 0.f;
        m_Picth = PI / 4.f; //45 degree
        m_Focus = { 0.f, 0.f, 0.f };
        m_Distance = glm::length(glm::vec3(10, 10, 10));
        UpdateViewMatrix();

    }
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


    void Camera::OnUpdate(TimeStep delta)
    {
        if (g_Input.IsKeyPressed(JS_KEY_LEFT_ALT))
        {
            glm::vec2 currentMousePos = { g_Input.GetMousePos().first, g_Input.GetMousePos().second };
            glm::vec2 mouseDelta = currentMousePos - m_PreMousePos;
            m_PreMousePos = currentMousePos;

            mouseDelta *= delta;

            if(g_Input.IsLeftMouseButtonPressed())
            {
                MouseRotate(mouseDelta);
            }
            if (g_Input.IsRightMouseButtonPressed())
            {
                MouseZoom(mouseDelta.y);
            }
            if (g_Input.IsMiddleMouseButtonPressed())
            {
                MousePan(mouseDelta);
            }
        }
        UpdateViewMatrix();
    }

    void Camera::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseScrollEvent>(JS_BIND_EVENT(Camera::OnMouseScroll));

    }

    glm::vec3 Camera::GetForwardDirection()
    {
        return glm::rotate(GetOrientation(), glm::vec3( 0.f, 0.f, -1.f ));
    }

    glm::vec3 Camera::GetRightDirection()
    {
        return glm::rotate(GetOrientation(), glm::vec3(1.f, 0.f, 0.f));
    }

    glm::vec3 Camera::GetUpDirection()
    {
        return glm::rotate(GetOrientation(), glm::vec3(0.f, 1.f, 0.f));
    }

    const glm::vec3& Camera::GetPos() const
    {
        return m_Position;
    }

    void Camera::UpdateViewMatrix()
    {
        m_Position = m_Focus - GetForwardDirection() * m_Distance;

        //m_Rotation = 
        m_ViewMat = glm::translate(glm::mat4(1.f), m_Position) * glm::toMat4(GetOrientation());
        m_ViewMat = glm::inverse(m_ViewMat);
    }

    glm::quat Camera::GetOrientation()
    {
        return glm::quat(glm::vec3(-m_Picth, -m_Yaw, 0.f));
    }

    void Camera::MouseRotate(const glm::vec2& delta)
    {
        //float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
        m_Yaw += delta.x * m_RotationSpeed;
        m_Picth += delta.y * m_RotationSpeed;
    }

    void Camera::MousePan(const glm::vec2& delta)
    {
        m_Focus -= GetRightDirection() * delta.x;
        m_Focus  += GetUpDirection() * delta.y;
    }

    void Camera::MouseZoom(float delta)
    {
        float distance = m_Distance * 0.2f;
        float speed = distance * distance;
        speed = std::min(speed, 100.0f); // max speed = 100

        m_Distance -= delta * speed;
        if (m_Distance < 1.f)
        {
            //m_Focus += GetForwardDirection();
            m_Distance = 1.f;

        }
    }

    bool Camera::OnMouseScroll(MouseScrollEvent& e)
    {
        MouseZoom(e.GetMouseYOffSet() * 0.1f);
        return true;
    }

    ///////////////////////////////////////////////////2D Camera/////////////////////////////////////////////////////////

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