#include "Game3DLayer.h"

Game3DLayer::Game3DLayer()
    : Layer("Game3Dlayer")
{

}

void Game3DLayer::OnAttach()
{
    JS_PROFILE_FUNCTION();
    //init camera
    g_CameraController.Init({ 0, 1, 3 }, g_AppWindow->GetAspectRatio());

    m_Shader = g_ResourceMgr.AcquireShader("Shader");
    m_LightShader = g_ResourceMgr.AcquireShader("Light");

    JSEngine::RenderCommand::AttachShader(m_Shader);
    JSEngine::RenderCommand::AttachShader(m_LightShader);

    m_CubeMeterial = JSEngine::Meterial::Create();
    m_CubeMeterial->SetColor({ 1.0f, 0.5f, 0.31f });

    JSEngine::Ref<JSEngine::Mesh> m = JSEngine::Mesh::Create(JSEngine::MeshType::CUBE);
    m->SetPosition(0, 0, 0);
    m->SetScale(1);
    m->AttachShader(m_Shader->GetShaderID());
    m->AttachMeterial(m_CubeMeterial);

    JSEngine::Ref<JSEngine::Mesh> m3 = JSEngine::Mesh::Create(JSEngine::MeshType::CUBE);
    m3->SetPosition(0, -1, -2);
    m3->SetScale(1);
    m3->AttachShader(m_Shader->GetShaderID());

    JSEngine::Ref<JSEngine::Mesh> m2 = JSEngine::Mesh::Create(JSEngine::MeshType::CUBE);
    m2->SetPosition(-2, -2, -2);
    m2->SetScale(1);
    m2->AttachShader(m_Shader->GetShaderID());


    JSEngine::Ref<JSEngine::Mesh> m4 = JSEngine::Mesh::Create(JSEngine::MeshType::CUBE);
    m4->SetPosition(0, 1, -2);
    m4->SetScale(1);
    m4->AttachShader(m_Shader->GetShaderID());

    m_MeshVec.push_back(m);
    m_MeshVec.push_back(m2);
    m_MeshVec.push_back(m3);
    m_MeshVec.push_back(m4);

    //set up light
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    JSEngine::Ref<JSEngine::Light> m_PointLight = JSEngine::Light::Create(JSEngine::LightType::POINT_LIGHT);
    auto& pointLight = std::static_pointer_cast<JSEngine::Ref<JSEngine::PointLight>::element_type>(m_PointLight);
    pointLight->SetPosition(lightPos);
    pointLight->GetMesh()->AttachShader(m_LightShader->GetShaderID());
    pointLight->GetMesh()->SetScale(0.25);
    pointLight->SetAttachedShaderID(m_Shader->GetShaderID());
    m_LightVec.push_back(pointLight);

    glm::vec3 lightDirection(-0.2f, -1.f, -0.3f);
    JSEngine::Ref<JSEngine::Light> dirLight = JSEngine::Light::Create(JSEngine::LightType::DIRECTIONAL_LIGHT);
    auto& directionalLight = std::static_pointer_cast<JSEngine::Ref<JSEngine::DirectionalLight>::element_type>(dirLight);
    directionalLight->SetLightDirection(lightDirection);
    directionalLight->SetAttachedShaderID(m_Shader->GetShaderID());

    m_LightVec.push_back(directionalLight);

    m_SceneData = std::make_shared<JSEngine::SceneData>();
    m_SceneData->Lights = m_LightVec;
}

void Game3DLayer::OnDetach()
{

}

void Game3DLayer::OnUpdate(JSEngine::TimeStep delta)
{
    //CLIENT_INFO("{0}", delta.m_DeltaTime);
    g_CameraController.OnUpdate(delta);

    //ProfileStart("Examplelayer::Renderer");
    JSEngine::RenderCommand::Clear({ 0.1, 0.1, 0.0, 1 });

    //m_SceneData->OrthoGraphicsCam = m_Camera;
    JSEngine::Renderer::BeginScene(m_SceneData);
    for (const auto& mesh : m_MeshVec)
        JSEngine::Renderer::Submit(mesh);

    JSEngine::Renderer::EndScene();
    JSEngine::Renderer::Flush();
    //ProfilerEnd
}

void Game3DLayer::OnRenderUpdate(JSEngine::TimeStep delta)
{
    ImGui::Begin("Light properties");

    for (int i = 0; i < m_LightVec.size(); ++i)
    {
        const auto& light = m_LightVec[i];
        std::string uniqueID = std::to_string(i);
        if (light->GetLightType() == JSEngine::LightType::DIRECTIONAL_LIGHT)
        {
            ImGui::Text(std::string("DirectionalLight " + uniqueID).c_str());
            ImGui::Separator();
            const auto& pointLight = JSEngine::CastLightTo<JSEngine::DirectionalLight>(light);
            auto color = pointLight->GetColor();
            ImGui::ColorEdit3("Color1", &color[0]);
            pointLight->SetColor(color);

            auto pos = pointLight->GetLightDirection();
            ImGui::DragFloat3("Pos1", &pos[0], 0.1f, -5.f, 5.f);
            pointLight->SetLightDirection(pos);
            ImGui::Separator();
        }
        else if (light->GetLightType() == JSEngine::LightType::POINT_LIGHT)
        {
            ImGui::Text(std::string("PointLight " + uniqueID).c_str());
            ImGui::Separator();
            const auto& pointLight = JSEngine::CastLightTo<JSEngine::PointLight>(light);
            auto color = pointLight->GetColor();
            ImGui::ColorEdit3("Color", &color[0]);
            pointLight->SetColor(color);

            auto pos = pointLight->GetPosition();
            ImGui::DragFloat3("Pos", &pos[0], 0.1f, -5.f, 5.f);
            pointLight->SetPosition(pos);
            ImGui::Separator();
        }
    }
    ImGui::End();



    ImGui::Begin("Mesh properties");
    for (int i = 0; i < m_MeshVec.size(); ++i)
    {
        std::string uniqueID = std::to_string(i);
        ImGui::Text(std::string("Mesh ID: " + uniqueID).c_str());
        const auto& mesh = m_MeshVec[i];
        auto pos = mesh->GetPosition();
        ImGui::DragFloat3(std::string("Pos " + uniqueID).c_str(), &pos[0], 0.1f, -5.f, 5.f);
        mesh->SetPosition(pos);
        ImGui::Separator();
    }
    ImGui::End();


    ImGui::Begin("Engine info");
    ImGui::Text(std::string("Frame rate: " + std::to_string(delta * 1000.f) + " ms").c_str());
    ImGui::Columns(2, "Proflier info"); // 2-ways, with border
    ImGui::Separator();
    ImGui::Text("Function Name"); ImGui::NextColumn();
    ImGui::Text("Time (ms)"); ImGui::NextColumn();
    ImGui::Separator();

    //for (const auto& profiledFunction : g_Profiler.GetProfilerCollectionVec())
    //{
    //    ImGui::Text(std::string(profiledFunction.first).c_str()); ImGui::NextColumn();
    //    ImGui::Text(std::to_string(profiledFunction.second).c_str()); ImGui::NextColumn();
    //}
    ImGui::Separator();
    ImGui::End();
}

void Game3DLayer::OnEvent(JSEngine::Event& e)
{
    g_CameraController.OnEvent(e);
}



