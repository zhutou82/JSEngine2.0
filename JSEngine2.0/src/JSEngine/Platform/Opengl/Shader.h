#pragma once
#include "JSEngine/Platform/Opengl/OpenGLContext.h"
#include "JSEngine/FileSystem/FileSystem.h"
#include <unordered_map>
namespace JSEngine
{
    class Shader
    {

    public:
        Shader(const std::string vFile, const std::string& fFile);
        ~Shader();

        void Bind() const;
        void UnBind() const;

        void SetUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3);
       


    private:
        void Init();
        unsigned int CreateAndCompile(unsigned int type, const JSFile& shaderFile);
        int GetUnifromLocation(const std::string& name);

    private:

        JSFile m_VertexShader;
        JSFile m_FragmentShader;

        unsigned int m_RendererID;

        std::unordered_map<std::string, int> m_UnfiromNameIDMap;
    };


}