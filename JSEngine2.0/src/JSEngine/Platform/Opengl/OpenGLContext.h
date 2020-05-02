#pragma once
#include "JSEngine/Graphics/GraphicsContext.h"
#include "JSEngine/Platform/WindowsWindow.h"
#include "JSEngine/Core/SingletonBaseClass.h"
//#include "glm/"

namespace JSEngine
{
    class Mesh;

#define g_GraphicsConext Singleton<OpenGLContext>::GetInstance()

    class OpenGLContext : public GraphicsConext, public Singleton<OpenGLContext>
    {

    public:

        friend class Singleton<OpenGLContext>;
        ~OpenGLContext();

    public:
        
        void Init(GLFWwindow* m_WindowHandle) override;
        void SwapBuffer()                     override;
        void Render()                         override;
        void Clear();
       
        void EnableDepthTest(bool enable);

    private:
        OpenGLContext();

    private:
        GLFWwindow* m_WindowHandle;
        //std::vector<Mesh*> m_MeshVec;

        //std::vector<Light*> m_LightVec;
        //PointLight* m_PointLight;

        //SceneData* m_SceneData;

        //glm::mat4 m_ProjMat;
        //glm::mat4 m_ViewMat;

        //std::shared_ptr<OpenGLShader> m_Shader;
        //std::shared_ptr<OpenGLShader> m_AnotherShader;
        //
        //float m_NearPlane;
        //float m_FarPlane;

        //glm::vec3 m_CameraPos;
        //glm::vec3 m_CameraFront;
        //glm::vec3 m_CameraUp;

        

    };

}