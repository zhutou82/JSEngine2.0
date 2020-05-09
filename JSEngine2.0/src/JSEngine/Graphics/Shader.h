#pragma once
#include <string>
#include "glm/glm.hpp"

namespace JSEngine
{



    class Shader
    {

    public:

        virtual ~Shader() {};

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        
        //static Ref<Shader> Create(const std::string& vertexShaderFileName = "VertexShader", const std::string& fragmentShaderFileName = "FragmentShader");
        static Ref<Shader> Create(const std::string& glslShaderFileName = "Shader");

        virtual uint32_t GetShaderID()     const = 0;
        virtual void SetShaderID(uint32_t) = 0;

        virtual void UploadUnfiromVec() = 0;
        virtual void UnloadUniformVec() = 0;

        virtual void AddToUniformVec(const std::string& name, int val) = 0;
        virtual void AddToUniformVec(const std::string& name, float val) = 0;
        virtual void AddToUniformVec(const std::string& name, const glm::vec3& val) = 0;
        virtual void AddToUniformVec(const std::string& name, const glm::vec4& val) = 0;
        virtual void AddToUniformVec(const std::string& name, const glm::mat4& val) = 0;

        virtual void SetIntArrary(const std::string& name, uint32_t count, int* val) = 0;
        
        

    };


}