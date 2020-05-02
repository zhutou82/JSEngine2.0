#include "PCH.h"
#include "OpenGLContext.h"
#include "glad/glad.h"
#include "Mesh.h"
#include "JSEngine/Application.h"
#include "JSEngine/Platform/WindowsWindow.h"
#include "imgui.h"


namespace JSEngine
{
    void APIENTRY openglCallbackFunction(GLenum source,
                                         GLenum type,
                                         GLuint id,
                                         GLenum severity,
                                         GLsizei length,
                                         const GLchar* message,
                                         const void* userParam) 
    {

        JS_CORE_INFO("---------------------opengl-callback-start------------");
        JS_CORE_INFO("message: {0}", message);
        JS_CORE_INFO("type: ");
        switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            JS_CORE_INFO("ERROR");
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            JS_CORE_INFO("DEPRECATED_BEHAVIOR");
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            JS_CORE_INFO("UNDEFINED_BEHAVIOR");
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            JS_CORE_INFO("PORTABILITY");
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            JS_CORE_INFO("PERFORMANCE");
            break;
        case GL_DEBUG_TYPE_OTHER:
            JS_CORE_INFO("OTHER");
            break;
        }

        JS_CORE_INFO("id: {0}", id);
        JS_CORE_INFO("severity: ");
        switch (severity) {
        case GL_DEBUG_SEVERITY_LOW:
            JS_CORE_INFO("LOW");
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            JS_CORE_INFO("MEDIUM");
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            JS_CORE_INFO("HIGH");
            break;
        }
        JS_CORE_INFO("---------------------opengl-callback-end--------------");
        JS_CORE_ASSERT(false, "Error");
    }


    void OpenGLContext::EnableDepthTest(bool enable)
    {
        if(enable)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
    }
    OpenGLContext::OpenGLContext()
    {

    }
    OpenGLContext::~OpenGLContext()
    {

    }
    void OpenGLContext::Init(GLFWwindow * windowHandle)
    {
        JS_CORE_ASSERT(windowHandle, "Windows handle is null");
        m_WindowHandle = windowHandle;

        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        JS_CORE_ASSERT(status, "Failed to initialized Glad");
        EnableDepthTest(true);

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(openglCallbackFunction, nullptr);

        //GLuint unusedIds = 0;
        //glDebugMessageControl(GL_DONT_CARE,
        //                      GL_DONT_CARE,
        //                      GL_DONT_CARE,
        //                      0,
        //                      &unusedIds,
        //                      true);

        //g_Camera.Init(windowHandle, { 0, 0, 3 });

        //glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        //m_Shader.reset(new OpenGLShader());
        //m_Shader->Init();
        ////m_AnotherShader.reset(new OpenGLShader("AnotherVertexShader", "AnotherFragmentShader"));


        //Mesh * m = new Mesh();
        //m->SetPosition(0, 0, 0);
        //m->SetScale(1);
        //m->AttachShader(m_Shader->GetShaderID());
        //

        //Mesh* lightObj = new Mesh();
        //lightObj->SetPosition(lightPos);
        //lightObj->SetScale(0.5);
        //lightObj->AttachShader(m_Shader->GetShaderID());
        ////m->SetRotation();
        ////m->AttachShader(m_Shader);
        //m_MeshVec.push_back(m);
        //m_MeshVec.push_back(lightObj);

        //m_PointLight = new PointLight();
        //m_PointLight->SetPosition(lightPos);
        //m_PointLight->SetAttachedShaderID(m_Shader->GetShaderID());

        //RenderCommand::AttachShader(m_Shader);
        //m_LightVec.push_back(m_PointLight);

        //m_SceneData = new SceneData;
        //m_SceneData->Lights = m_LightVec;
    }

    void OpenGLContext::Render()
    {
        //RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1 });

        //g_Camera.Update();

        //m_Shader->Bind();
        //m_Shader->SetUnifrom1i("u_TextureID", 0);
        ////ImGui::Begin("Testing");
        ////ImGui::End();
        //m_Shader->SetUnifrom3f("u_ObjectColor", { 1.0f, 0.5f, 0.31f });

        //Renderer::BeginScene(m_SceneData);

        //for (auto mesh : m_MeshVec)
        //{
        //    //mesh->SetRotation(mesh->GetRotation() + 10.f * g_dt);
        //    Renderer::Submit(mesh);
        //}

        //Renderer::EndScene();

    }

    void OpenGLContext::Clear()
    {

    }

    void OpenGLContext::SwapBuffer()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

}