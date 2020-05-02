#include <JSEngine.h>

using namespace JSEngine;

class ExampleLayer : public JSEngine::Layer
{


public:
    void OnAttach()
    {
        ProfileStart("Examplelayer::OnAttach");
        g_CameraController.Init({ 0, 1, 3 }, g_AppWindow->GetAspectRatio());
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        m_Shader = Shader::Create("Shader");
        m_LightShader = Shader::Create("Light");

        JSEngine::RenderCommand::AttachShader(m_Shader);
        JSEngine::RenderCommand::AttachShader(m_LightShader);

        m_CubeMeterial = Meterial::Create();
        m_CubeMeterial->SetColor({ 1.0f, 0.5f, 0.31f });

        JSEngine::Ref<Mesh> m = JSEngine::Mesh::Create(JSEngine::MeshType::CUBE);
        m->SetPosition(0, 0, 0);
        m->SetScale(1);
        m->AttachShader(m_Shader->GetShaderID());
        m->AttachMeterial(m_CubeMeterial);

        JSEngine::Ref<Mesh> m2 = JSEngine::Mesh::Create(JSEngine::MeshType::CUBE);
        m2->SetPosition(1, 1, -2);
        m2->SetScale(1);
        m2->AttachShader(m_Shader->GetShaderID());

        JSEngine::Ref<Mesh> m3 = JSEngine::Mesh::Create(JSEngine::MeshType::CUBE);
        m3->SetPosition(-1, -1, -1);
        m3->SetScale(1);
        m3->AttachShader(m_Shader->GetShaderID());

        m_MeshVec.push_back(m);
        m_MeshVec.push_back(m2);
        m_MeshVec.push_back(m3);

        //set up light
        JSEngine::Ref<Light> m_PointLight = JSEngine::Light::Create(JSEngine::LightType::POINT_LIGHT);
        auto& pointLight = std::static_pointer_cast<JSEngine::Ref<JSEngine::PointLight>::element_type>(m_PointLight);
        pointLight->SetPosition(lightPos);
        pointLight->GetMesh()->AttachShader(m_LightShader->GetShaderID());
        pointLight->GetMesh()->SetScale(0.25);
        pointLight->SetAttachedShaderID(m_Shader->GetShaderID());

        m_LightVec.push_back(pointLight);

        m_SceneData = std::make_shared<JSEngine::SceneData>();
        m_SceneData->Lights = m_LightVec;
        ProfilerEnd
    }

    void OnDetach()
    {


    }

    void OnUpdate(TimeStep delta)
    {
        
        ProfileStart("Examplelayer::Onupdate");

        //CLIENT_INFO("{0}", delta.m_DeltaTime);
        g_CameraController.OnUpdate(delta);

        ProfileStart("Examplelayer::Renderer");
            JSEngine::RenderCommand::Clear({ 0.1, 0.1, 0.0, 1 });

            JSEngine::Renderer::BeginScene(m_SceneData);
            for (const auto& mesh : m_MeshVec)
                JSEngine::Renderer::Submit(mesh);

            JSEngine::Renderer::EndScene();
            JSEngine::Renderer::Flush();
        ProfilerEnd


        ProfilerEnd
    }

    void OnRenderUpdate()
    {
        ImGui::Begin("Light properties");

        for (int i = 0; i < m_LightVec.size(); ++i)
        {
            const auto& light = m_LightVec[i];
            ImGui::Text(std::string("Light" + std::to_string(i + 1)).c_str());
            if (light->GetLightType() == JSEngine::LightType::POINT_LIGHT)
            {
                const auto& pointLight = std::static_pointer_cast<JSEngine::Ref<JSEngine::PointLight>::element_type>(light);
                auto color = pointLight->GetColor();
                ImGui::ColorEdit3("lightColor", &color[0]);
                pointLight->SetColor(color);

                auto pos = pointLight->GetPosition();
                ImGui::DragFloat3("lightPos", &pos[0], 0.1f, -5.f, 5.f);
                pointLight->SetPosition(pos);
                ImGui::Separator();
            }

        }
        ImGui::End();
        ImGui::Begin("Mesh properties");
        for (int i = 0; i < m_MeshVec.size(); ++i)
        {
            ImGui::Text(std::string("Mesh ID: " + std::to_string(i + 1)).c_str());
            const auto& mesh = m_MeshVec[i];
            auto pos = mesh->GetPosition();
            ImGui::DragFloat3(std::string("Pos " + std::to_string(i + 1)).c_str(), &pos[0], 0.1f, -5.f, 5.f);
            mesh->SetPosition(pos);
            ImGui::Separator();
        }
        ImGui::End();


        ImGui::Begin("Engine info");
        ImGui::Columns(2, "Proflier info"); // 2-ways, with border
        ImGui::Separator();
        ImGui::Text("Function Name"); ImGui::NextColumn();
        ImGui::Text("Time (ms)"); ImGui::NextColumn();
        ImGui::Separator();

        for (const auto& profiledFunction : g_Profiler.GetProfilerCollectionVec())
        {
            ImGui::Text(std::string(profiledFunction.first).c_str()); ImGui::NextColumn();
            ImGui::Text(std::to_string(profiledFunction.second).c_str()); ImGui::NextColumn();
        }
        ImGui::Separator();
        ImGui::End();
    }


    void OnEvent(JSEngine::Event& e)
    {
        g_CameraController.OnEvent(e);
    }


private:



private:

    std::vector<JSEngine::Ref<Mesh>>       m_MeshVec;
    std::vector<JSEngine::Ref<Light>>      m_LightVec;

    JSEngine::Ref<JSEngine::Shader>        m_Shader;
    JSEngine::Ref<JSEngine::Shader>        m_LightShader;

    JSEngine::Ref<JSEngine::Meterial>      m_CubeMeterial;
    
    JSEngine::Ref<JSEngine::SceneData>     m_SceneData;

};


class SandBox : public JSEngine::Application
{
public:
    SandBox()
    {
        PushLayer(new ExampleLayer());
        PushOverLay(new JSEngine::imguiLayer());


    }
    ~SandBox()
    {

    }
};

JSEngine::Application*  JSEngine::CreateApplication()
{
    return new SandBox;
}
