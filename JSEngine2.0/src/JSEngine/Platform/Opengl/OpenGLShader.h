#pragma once
#include "JSEngine/FileSystem/FileSystem.h"
#include <unordered_map>
#include "glm/glm.hpp"
#include "JSEngine/Graphics/Shader.h"
#include "Glad/glad.h"

namespace JSEngine
{
    class OpenGLShader : public Shader
    {

        struct Unifroms
        {
            std::vector<std::pair<std::string, int>> IntVec;
            std::vector<std::pair<std::string, float>> FloatVec;
            std::vector<std::pair<std::string, glm::vec3>> Vec3Vec;
            std::vector<std::pair<std::string, glm::vec4>> Vec4Vec;
            std::vector<std::pair<std::string, glm::mat4>> Mat4Vec;
        };

        static std::string s_FolderPath;
        static std::string s_VertexType;
        static std::string s_FragmentType;

        static uint32_t s_ID;

    public:

        

        static void SetShaderFolderPath(const std::string& folderPath);

        OpenGLShader(const std::string& glslFileName);
        OpenGLShader(const std::string& vFile, const std::string& fFile);
        ~OpenGLShader();

        virtual void Bind()   const override;
        virtual void UnBind() const override;

        virtual uint32_t GetShaderID() const override;
        virtual void SetShaderID(uint32_t val) override;

        virtual void UploadUnfiromVec() override;
        virtual void UnloadUniformVec() override;

        void SetUnifromMat4f(const std::string& name, const glm::mat4& mat);
        void SetUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUnifrom4f(const std::string& name, const glm::vec4& vec4);
        void SetUnifrom3f(const std::string& name, float v0, float v1, float v2);
        void SetUnifrom3f(const std::string& name, const glm::vec3& vec3);
        void SetUnifrom1i(const std::string& name, int value);
        void SetUnifrom1f(const std::string& name, float value);

        

        void AddToUniformVec(const std::string& name, float f)
        {
            m_Uniforms.FloatVec.push_back({ name,f });
        }
        void AddToUniformVec(const std::string& name, const glm::vec3& vec3)
        {
            m_Uniforms.Vec3Vec.push_back({ name,vec3 });
        }
        void AddToUniformVec(const std::string& name, const glm::vec4& vec4)
        {
            m_Uniforms.Vec4Vec.push_back({ name,vec4 });
        }
        void AddToUniformVec(const std::string& name, const glm::mat4& mat4) 
        {
            m_Uniforms.Mat4Vec.push_back({ name,mat4 });
        }
        void AddToUniformVec(const std::string& name, int val)
        {
            m_Uniforms.IntVec.push_back({ name, val });
        }

    private:
        
        int GetUnifromLocation(const std::string& name);
        void GetShaderSrc();
        GLenum GetGLShaderTypeByShaderType(const std::string& shaderType);
    private:

        JSFile m_GlslFile;

        unsigned int m_RendererID;
        Unifroms m_Uniforms;
        uint32_t m_ShaderID;
        
        std::unordered_map<std::string, int> m_UnfiromNameIDMap;
        std::unordered_map<GLenum, std::string> m_ShaderTypeShaderSrcMap;
            
    };


}