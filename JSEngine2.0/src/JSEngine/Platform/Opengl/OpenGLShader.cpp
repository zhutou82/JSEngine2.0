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
                    JS_CORE_TRACE("{0}", shaderSrc);
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


    void OpenGLShader::UploadUnfiromVec()
    {
        for (const auto& val : m_Uniforms.IntVec)   SetUnifrom1i(val.first, val.second);
        for (const auto& val : m_Uniforms.FloatVec) SetUnifrom1f(val.first, val.second);
        for (const auto& val : m_Uniforms.Vec3Vec)  SetUnifrom3f(val.first, val.second);
        for (const auto& val : m_Uniforms.Vec4Vec)  SetUnifrom4f(val.first, val.second);
        for (const auto& val : m_Uniforms.Mat4Vec)  SetUnifromMat4f(val.first, val.second);
    }

    void OpenGLShader::UnloadUniformVec()
    {
        m_Uniforms.FloatVec.clear();
        m_Uniforms.Vec3Vec.clear();
        m_Uniforms.Vec4Vec.clear();
        m_Uniforms.Mat4Vec.clear();
        m_Uniforms.IntVec.clear();
    }

    void OpenGLShader::SetUnifromMat4f(const std::string& name, const glm::mat4& mat)
    {
        glUniformMatrix4fv(GetUnifromLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void OpenGLShader::SetUnifrom4f(const std::string & name, float v0, float v1, float v2, float v3)
    {
        glUniform4f(GetUnifromLocation(name), v0, v1, v2, v3);
    }

    void OpenGLShader::SetUnifrom4f(const std::string& name, const glm::vec4& vec4)
    {
        SetUnifrom4f(name, vec4.x, vec4.y, vec4.z, vec4.w);
    }

    void OpenGLShader::SetUnifrom3f(const std::string& name, float v0, float v1, float v2)
    {
        glUniform3f(GetUnifromLocation(name), v0, v1, v2);
    }

    void OpenGLShader::SetUnifrom3f(const std::string& name, const glm::vec3& vec3)
    {
        SetUnifrom3f(name, vec3.x, vec3.y, vec3.z);
    }

    void OpenGLShader::SetUnifrom1i(const std::string& name, int value)
    {
        glUniform1i(GetUnifromLocation(name), value);
    }

    void OpenGLShader::SetUnifrom1f(const std::string& name, float value)
    {
        glUniform1f(GetUnifromLocation(name), value);
    }

    void OpenGLShader::SetIntArrary(const std::string& name, uint32_t count, int* val)
    {
        glUniform1iv(GetUnifromLocation(name), count, val);
    }

    int OpenGLShader::GetUnifromLocation(const std::string & name)
    {
        if (m_UnfiromNameIDMap.find(name) == m_UnfiromNameIDMap.end())
        {
            m_UnfiromNameIDMap[name] = glGetUniformLocation(m_RendererID, name.c_str());
            if (m_UnfiromNameIDMap[name] == -1)
                JS_CORE_INFO("Uniform name not exist {0}, {1}", name, m_GlslFile.GetFileName());
        }

        return m_UnfiromNameIDMap[name];
    }


}
