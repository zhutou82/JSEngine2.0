#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "JSEngine/Event/Event.h"
#include "JSEngine/Event/MouseEvent.h"
#include "JSEngine/Core/TimeStep.h"


namespace JSEngine
{
    class Camera 
    {

    public:
        Camera() {}
        Camera(const glm::mat4& projMat);
        ~Camera() {}
        
        
        const glm::mat4& ConstructViewMat();
        const glm::mat4& ConstructProjectMat();

        const glm::vec3& GetPosition() const { return m_Pos; }
        void SetPosition(glm::vec3 val) { m_Pos = val; }

        float GetAspecRatio() const { return m_AspecRatio; }
        void SetAspecRatio(float val) { m_AspecRatio = val; }

        void OnUpdate(TimeStep delta);
        void OnEvent(Event& e);

        const glm::vec3& GetPos() const;

        void SetProjectionMatrix(const glm::mat4& projectionMatrix) { m_ProjMat = projectionMatrix; }
        void SetViewportSize(uint32_t width, uint32_t height) { m_ViewportWidth = width; m_ViewportHeight = height; }

        const glm::mat4& GetProjectionMatrix() const { return m_ProjMat; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMat; }
        const glm::mat4& GetViewProjection() const { return m_ProjMat * m_ViewMat; }

    private:

        glm::vec3 GetForwardDirection();
        glm::vec3 GetRightDirection();
        glm::vec3 GetUpDirection();

        void UpdateViewMatrix();
        glm::quat GetOrientation();

        void MouseRotate(const glm::vec2& delta);
        void MousePan(const glm::vec2& delta);
        void MouseZoom(float delta);

        bool OnMouseScroll(MouseScrollEvent& e);

    protected:
        

        //follow Maya camera
        glm::mat4 m_ProjMat{ 1.f };
        glm::mat4 m_ViewMat{ 1.f };
        
        glm::vec3 m_Position{ 0.f };
        glm::vec3 m_Rotation{ 90.f, 0.f, 0.f };
        glm::vec3 m_Focus{ 0.f };
        float m_Distance;
        float m_Yaw; //X - axis
        float m_Picth; //Y - axis
        float m_RotationSpeed = 0.8f;
        glm::vec2 m_PreMousePos{ 0.f };

        uint32_t m_ViewportWidth = 1280;
        uint32_t m_ViewportHeight = 720;

        //view matrix
        glm::vec3 m_Front{ 0, 0, -1 };
        glm::vec3 m_Pos{0};
        glm::vec3 m_Up{ 0, 1, 0 };
        //glm::mat4 m_ViewMat{1.f};

        //perspective projection
        float m_FOV = 45.f;
        float m_NearPlane = 0.1f;
        float m_FarPlane = 100.f;
        float m_AspecRatio;
        //glm::mat4 m_ProjMat{1.f};

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