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
        JS_CORE_INFO("source: {0}", source);
        JS_CORE_INFO("type: ");
        JS_CORE_INFO("id: {0}", id);

        JS_CORE_INFO("severity: ");
        switch (severity) {
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            JS_CORE_INFO("NOTIFICATION");
            break;
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

        JS_CORE_INFO("message: {0}", message);
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

        JS_CORE_INFO("---------------------opengl-callback-end--------------");

        // dont assert for notifications
        if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
            return;

        JS_CORE_ASSERT(false, "Error");
    }
    void OpenGLContext::EnableDepthTest(bool enable)
    {
        if(enable)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
    }
    void OpenGLContext::EnableBlending(bool enable)
    {
        if (enable)
            glEnable(GL_BLEND);
        else
            glDisable(GL_BLEND);
    }
    void OpenGLContext::SetBlendFunc(GLenum source, GLenum dest)
    {
        glBlendFunc(source, dest);
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

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(openglCallbackFunction, nullptr);

        // Comment below to retrieve ALL OpenGL debug messages, including trivial notifications. Warning: it's fucking spammy.
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, false);
    }

    void OpenGLContext::Render()
    {

    }

    void OpenGLContext::Clear()
    {

    }

    void OpenGLContext::SwapBuffer()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

}