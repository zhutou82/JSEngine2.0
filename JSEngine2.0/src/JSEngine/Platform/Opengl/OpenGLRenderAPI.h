#pragma once
#include "JSEngine/Graphics/RendererAPI.h"
#include <map>
#include "OpenGLShader.h"

namespace JSEngine
{

    class OpenGLRendererAPI : public RendererAPI
    {
    public:

        virtual void Clear(const glm::vec4& color) override;
        virtual void DrawIndexd(const Ref<Mesh>& mesh) override;
        
        virtual void AttachShader(const Ref<Shader>& shader) override;
        virtual void DrawIndexd(const Ref<VertexArray>& VAO) override;
        virtual void SetUpCamera() override;
        virtual void SetUpEnviroment(const Ref<SceneData>& sceneData) override;
        virtual void ClearSceneData() override;
        virtual void Submit(const Ref<Mesh>& mesh) override;
    private:
        void UploadUniforms(const Ref<Shader>& shader);
        void UploadAllShaderUniforms();
        

    private:
        
        std::map<uint32_t, Ref<Shader> > m_IDShaderMap;
        Ref<SceneData> m_SceneData;
        

    };

}