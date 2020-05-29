#include "PCH.h"
#include "OpenGLShader.h"
#include "JSEngine/Managers/ResourceManager.h"
#include "JSEngine/Platform/Opengl/OpenGLContext.h"
#include "glm/gtc/type_ptr.hpp"

namespace JSEngine
{
    std::string OpenGLShader::s_VertexType = "vertex";
    std::string OpenGLShader::s_FragmentType = "fragment";

    uint32_t OpenGLShader::s_ID = 0;

    GLenum OpenGLShader::GetGLShaderTypeByShaderType(const std::string& shaderType)
    {
        if (shaderType == s_VertexType)
            return GL_VERTEX_SHADER;

        else if (shaderType == s_FragmentType)
            return GL_FRAGMENT_SHADER;

        JS_CORE_ASSERT(false, "Unknow shader type");
        return 0;
    }

    int32_t OpenGLShader::GetUniformLocation(const std::string& name) const
    {
        int32_t result = glGetUniformLocation(m_RendererID, name.c_str());
        //if (result == -1)
        //    JS_CORE_WARN("Could not find uniform '{0}' in shader {1} ", name, m_GlslFile.GetFileName());

        return result;
    }

    OpenGLShader::OpenGLShader(const std::string& glslFileName) 
        : m_GlslFile(glslFileName, GLSL, READ)
    {
        m_GlslFile.Init(g_ResourceMgr.GetCoreFolderPaths(CoreFolderPath::SHADER));
        GetShaderSrc();

        //create and link shader file to shader program
        m_RendererID = glCreateProgram();

        for (const auto& shader : m_ShaderTypeShaderSrcMap)
        {
            const char* source = shader.second.c_str();
            unsigned int shaderID = glCreateShader(shader.first);
            glShaderSource(shaderID, 1, &source, NULL);
            glCompileShader(shaderID);
            glAttachShader(m_RendererID, shaderID);
            glDeleteShader(shaderID);
        }
        glLinkProgram(m_RendererID);

        SetShaderID(s_ID++);
    }
    OpenGLShader::OpenGLShader(const std::string& vFile, const std::string & fFile)
    {
        //read shader file
    }
     
    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::UnBind() const
    {
        glUseProgram(0);
    }

    uint32_t OpenGLShader::GetShaderID() const
    {
        return m_ShaderID;
    }

    void OpenGLShader::SetShaderID(uint32_t val)
    {
        m_ShaderID = val;
    }

    void OpenGLShader::SetFloat(const std::string& name, float value)
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value_ptr(value));
    }

    void OpenGLShader::GetShaderSrc()
    {
        FILE* vs = m_GlslFile.GetFile();
        const char* type = "//type";
        const size_t bufsize = 10000;
        char line[bufsize] = { 0 };
        char shaderName[bufsize] = { 0 };
        char shaderSrc[bufsize] = { 0 };

        bool shaderTitleFound = false;
        while (fgets(line, bufsize, vs))
        {
            if (strstr(line, type)) 
            {
                if (shaderTitleFound)
                {
                    //JS_CORE_TRACE("{0}", shaderSrc);
                    m_ShaderTypeShaderSrcMap[GetGLShaderTypeByShaderType(shaderName)] = shaderSrc;
                    memset(shaderSrc, 0, bufsize);
                    memset(shaderName, 0, bufsize);
                }
                int shaderNameStartPos = (int)strlen(type) + 1;
                int i = 0;
                int shaderNameLength = (int)(strchr(line, '\n') - line) - shaderNameStartPos;
                while (i < shaderNameLength)
                {
                    shaderName[i++] = line[shaderNameStartPos++];
                }
                shaderTitleFound = true;
            }
            strcat(shaderSrc, line);
        }
    }
}
