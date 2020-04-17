#include "PCH.h"
#include "Shader.h"

namespace JSEngine
{
    Shader::Shader(const std::string vFile, const std::string & fFile) 
        : m_VertexShader(vFile, VS, READ),
          m_FragmentShader(fFile, FS, READ)
    {
        Init();
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void Shader::UnBind() const
    {
        glUseProgram(0);
    }



    void Shader::Init()
    {
        std::string shaderFolderPath = "../Resource/Shader/";
        //read shader file
        m_VertexShader.Init(shaderFolderPath);
        m_FragmentShader.Init(shaderFolderPath);

        unsigned int vertexShaderID = CreateAndCompile(GL_VERTEX_SHADER, m_VertexShader);
        unsigned int fragmentShaderID = CreateAndCompile(GL_FRAGMENT_SHADER, m_FragmentShader);

        //create and link shader file to shader program
        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertexShaderID);
        glAttachShader(m_RendererID, fragmentShaderID);
        glLinkProgram(m_RendererID);

        int s = 0;
        char errorMsg[512];
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &s);
        if (s == GL_FALSE)
        {
            glGetProgramInfoLog(m_RendererID, sizeof(errorMsg), NULL, errorMsg);
            JS_CORE_ERROR("{0}", errorMsg);
            __debugbreak();
        }
        
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    unsigned int Shader::CreateAndCompile(unsigned int type, const JSFile& shaderFile)
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

    void Shader::SetUnifrom4f(const std::string & name, float v0, float v1, float v2, float v3)
    {
        glUniform4f(GetUnifromLocation(name), v0, v1, v2, v3);
    }

    int Shader::GetUnifromLocation(const std::string & name)
    {
        if (m_UnfiromNameIDMap.find(name) == m_UnfiromNameIDMap.end())
        {
            m_UnfiromNameIDMap[name] = glGetUniformLocation(m_RendererID, name.c_str());
            if (m_UnfiromNameIDMap[name] == -1)
                JS_CORE_INFO("Uniform name not exist {0}", name);
        }

        return m_UnfiromNameIDMap[name];
    }

}
