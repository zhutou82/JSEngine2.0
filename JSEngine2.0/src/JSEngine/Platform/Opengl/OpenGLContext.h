#pragma once
#include "JSEngine/Graphics/GraphicsContext.h"
#include "JSEngine/Platform/WindowsWindow.h"
#include "JSEngine/SingletonBaseClass.h"
#include "JSEngine/FileSystem/FileSystem.h"



namespace JSEngine
{
#define g_GraphicsConext Singleton<OpenGLContext>::GetInstance()

    class OpenGLContext : public GraphicsConext, public Singleton<OpenGLContext>
    {
        const std::string VERTEX_SHADER_FILE_NAME   = "VertexShader";
        const std::string FRAGMENT_SHADER_FILE_NAME = "FragmentShader";


    public:
        friend class Singleton<OpenGLContext>;
        ~OpenGLContext() {};


    public:
        
        void Init(GLFWwindow* m_WindowHandle) override;
        void SwapBuffer()                     override;
        void Render()                         override;
        

    private:
        OpenGLContext();
        void InitShader();
        void ReadShaderSource();
        unsigned int CreateAndCompileShader(unsigned int type, const JSFile& shaderFile);

    private:
        GLFWwindow* m_WindowHandle;
        unsigned int m_VertexArrayID;
        unsigned int m_VertexBufferID;
        unsigned int m_IndicesBufferID;
        unsigned int m_ShaderID;
        unsigned int m_UniformColorID;

        JSFile m_VertexShader;
        JSFile m_FragmentShader;

    };

}