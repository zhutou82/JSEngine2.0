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
        static std::string s_VertexType;
        static std::string s_FragmentType;

        static uint32_t s_ID;

    public:
        OpenGLShader(const std::string& glslFileName);
        OpenGLShader(const std::string& vFile, const std::string& fFile);
        ~OpenGLShader();

        virtual void Bind()   const override;
        virtual void UnBind() const override;

        uint32_t GetProgramID() const { return m_RendererID; }

        virtual uint32_t GetShaderID() const override;
        virtual void SetShaderID(uint32_t val) override;

        // TODO: These are all bullshit. Remove them.
        virtual void UploadUnfiromVec() override {}
        virtual void UnloadUniformVec() override {}
        virtual void AddToUniformVec(const std::string& name, int val) override {}
        virtual void AddToUniformVec(const std::string& name, float val) override {}
        virtual void AddToUniformVec(const std::string& name, const glm::vec3& val) override {}
        virtual void AddToUniformVec(const std::string& name, const glm::vec4& val) override {}
        virtual void AddToUniformVec(const std::string& name, const glm::mat4& val) override {}

        virtual void SetIntArrary(const std::string& name, uint32_t count, int* val) override {}

        void SetFloat(const std::string& name, float value);
        void SetFloat3(const std::string& name, const glm::vec3& value);
        void SetInt(const std::string& name, int value);
        void SetMat4(const std::string& name, const glm::mat4& value);
        //void SetMat4FromRenderThread(const std::string& name, const glm::mat4& value, bool bind = true);

    private:
        void GetShaderSrc();
        GLenum GetGLShaderTypeByShaderType(const std::string& shaderType);
        int32_t GetUniformLocation(const std::string& name) const;

    private:
        JSFile m_GlslFile;

        uint32_t m_RendererID;
        uint32_t m_ShaderID;
        
        std::unordered_map<GLenum, std::string> m_ShaderTypeShaderSrcMap;
    };


}