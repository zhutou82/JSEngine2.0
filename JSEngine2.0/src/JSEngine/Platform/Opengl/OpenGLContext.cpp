#include "PCH.h"
#include "OpenGLContext.h"
#include "glad/glad.h"
#include "VertexArraryObject.h"
#include "VertexBufferObject.h"
#include "IndexBufferObject.h"
#include "Layout.h"

namespace JSEngine
{
    OpenGLContext::OpenGLContext()
        : m_VertexShader(VERTEX_SHADER_FILE_NAME, VS, READ),
          m_FragmentShader(FRAGMENT_SHADER_FILE_NAME, FS, READ)
    {

    }
    void OpenGLContext::Init(GLFWwindow * windowHandle)
    {
        JS_CORE_ASSERT(windowHandle, "Windows handle is null");
        m_WindowHandle = windowHandle;

        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        JS_CORE_ASSERT(status, "Failed to initialized Glad");
         
        
        //testing render triangle
        float vertexPos[] =
        {
            -0.5f, -0.5f, 0.f, 1.f,  1.f,  0.f, 0.f, 1.f,
             0.5f, -0.5f, 0.f, 1.f,  0.f,  1.f, 0.f, 1.f,
             0.5f,  0.5f, 0.f, 1.f,  0.f,  0.f, 1.f, 1.f,
            -0.5f , 0.5f, 0.f, 1.f,  0.5f , 0.5f, 0.f, 1.f,
        };
        unsigned int indices[] =
        {
            0, 1, 2,
            0, 2, 3
        };
        //create VAO
        VertexArrayObject vao;

        //create VBO 
        VertexBufferObject vbo(sizeof(vertexPos), vertexPos, GL_STATIC_DRAW);
        //create layout
        Layout layout;
        layout.Push<float>(4);
        layout.Push<float>(4);
        //activate layout
        vao.AddToBuffer(vbo, layout);
        //create index buffer
        IndexBufferObject ibo(sizeof(indices), indices, GL_STATIC_DRAW); 
        //create shader
        InitShader();
        //sending unform data to shader
        m_UniformColorID = glGetUniformLocation(m_ShaderID, "u_Color");
    }

    void OpenGLContext::Render()
    {
        static float red = 0.f;
        static float inc = 0.01f;
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.5, 0.5, 0.5, 1);

        glUniform4f(m_UniformColorID, red, 0.2f, 0.5f, 1.f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        
        //if (red <= 0.f)
        //    inc = 0.05f;
        //else if (red >= 1.f)
        //    inc = -0.05f;

        //red += inc;
    }


    void OpenGLContext::InitShader()
    {
        std::string shaderFolderPath = "../Resource/Shader/";
        //read shader file
        m_VertexShader.Init(shaderFolderPath);
        m_FragmentShader.Init(shaderFolderPath);

        unsigned vertexShaderID = CreateAndCompileShader(GL_VERTEX_SHADER, m_VertexShader);
        unsigned fragmentShaderID = CreateAndCompileShader(GL_FRAGMENT_SHADER, m_FragmentShader);

        //create and link shader file to shader program
        m_ShaderID = glCreateProgram();
        glAttachShader(m_ShaderID, vertexShaderID);
        glAttachShader(m_ShaderID, fragmentShaderID);
        glLinkProgram(m_ShaderID);

        int s = 0;
        char errorMsg[512];
        glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &s);
        if (s == GL_FALSE)
        {
            glGetProgramInfoLog(m_ShaderID, sizeof(errorMsg), NULL, errorMsg);
            JS_CORE_ERROR("{0}", errorMsg);
            __debugbreak();
        }
        glUseProgram(m_ShaderID);

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
       
    }

    unsigned int OpenGLContext::CreateAndCompileShader(unsigned int type, const JSFile& shaderFile)
    {
        FILE* vs = shaderFile.GetFile();
        fseek(vs, 0, SEEK_END);
        long fileSize = ftell(vs);
        rewind(vs);
        char * source = (char*)calloc(fileSize + 1, sizeof(char));
        fread(source, sizeof(char), fileSize, vs);

        unsigned int shaderID = glCreateShader(type);
        glShaderSource(shaderID, 1, &source, NULL);
        glCompileShader(shaderID);

        int s = 1;
        char errorMsg[512];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &s);
        if (s == GL_FALSE)
        {
            glGetShaderInfoLog(shaderID, sizeof(errorMsg), NULL, errorMsg);
            JS_CORE_ERROR("At {0}, {1}", type == GL_VERTEX_SHADER ? "Vertex shader" : "Fragment shader", errorMsg);
            __debugbreak();
        }

        free(source);
        return shaderID;
    }

    void OpenGLContext::SwapBuffer()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

}