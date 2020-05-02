#pragma once
#include "JSEngine/Graphics/Camera.h"
#include "JSEngine/Core/TimeStep.h"
#include "JSEngine/Event/Event.h"
#include "JSEngine/Event/ApplicationEvent.h"
#include "JSEngine/Event/MouseEvent.h"
#include "JSEngine/Core/SingletonBaseClass.h"


#define g_CameraController JSEngine::Singleton<JSEngine::CameraController>::GetInstance()

namespace JSEngine
{

    class CameraController : public Singleton<CameraController>, public Camera
    {
        static constexpr const float s_MaxUpAngle = 89.f;
        static constexpr const float s_MaxDownAngle = -89.f;
        static constexpr const float s_MaxFOV = 45.f;
        static constexpr const float s_MinFOV = 0.f;
        static constexpr const float s_FOV = 45.f;
        static constexpr const float s_NearPlane = 0.1f;
        static constexpr const float s_FarPlane = 100.f;


    public:
        friend class Singleton<CameraController>;

        ~CameraController() {};
        
        void Init(const glm::vec3& camStartPos, float aspecRatio, float fov = 45.f, float nearPlane = 0.1, float farPlane = 100.f);

        void OnUpdate(TimeStep time);
        void OnEvent(Event& e);

        bool CursorScrollCallBack(MouseScrollEvent& event);
        bool CursorPosCallBack(MouseMoveEvent& event);

    private:
        CameraController() {}


        float m_CameraMoveSpeed;
        float m_CameraSensitivity;
        float m_CameraScrollSpeed;

        float m_Yaw;
        float m_Pictch;

        float m_PreXpos;
        float m_PreYpos;
        float m_PreXScroll;
        float m_PreYScroll;




    };



}