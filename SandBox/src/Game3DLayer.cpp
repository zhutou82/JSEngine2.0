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
    m_SceneData = JSEngine::CreateRef<JSEngine::SceneData>();
                          

    //body scene
    {
        m_Scene = JSEngine::CreateRef<JSEngine::Scene3D>("body scene"); 
        m_Scene->Init(JSEngine::Camera(glm::perspectiveFov(glm::radians(45.0f), 1280.0f, 720.0f, 0.1f, 10000.0f)));

        JSEngine::Entity* bodyEntity = m_Scene->CreateEntity("Body");
        bodyEntity->SetMesh(JSEngine::Mesh::Create("Body/nanosuit"));

        JSEngine::Entity* cubeEntity = m_Scene->CreateEntity("Cube");
        cubeEntity->SetMesh(JSEngine::Mesh::Create(JSEngine::MeshType::CUBE));
        cubeEntity->SetScale({ 50.f, 0.1f, 50.f });

        m_Scene->CreatePointLight({ 1.2f, 1.0f, 2.0f });

    }
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

    m_Scene->OnUpdate(delta);

    ////m_SceneData->OrthoGraphicsCam = m_Camera;
    //JSEngine::Renderer::BeginScene(m_SceneData);

    //for (const auto& mesh : m_MeshVec)
    //    JSEngine::Renderer::SubmitMesh(mesh, glm::mat4(1.f));

    //JSEngine::Renderer::EndScene();
    ////ProfilerEnd
}

void Game3DLayer::OnRenderUpdate(JSEngine::TimeStep delta)
{
    //ImGui::Begin("Light properties");

    //for (int i = 0; i < m_SceneData->Lights.size(); ++i)
    //{
    //    const auto& light = m_SceneData->Lights[i];
    //    std::string uniqueID = std::to_string(i);
    //    if (light->GetLightType() == JSEngine::LightType::DIRECTIONAL_LIGHT)
    //    {
    //        ImGui::Text(std::string("DirectionalLight " + uniqueID).c_str());
    //        ImGui::Separator();
    //        const auto& pointLight = JSEngine::CastLightTo<JSEngine::DirectionalLight>(light);
    //        auto color = pointLight->GetColor();
    //        ImGui::ColorEdit3("Color1", &color[0]);
    //        pointLight->SetColor(color);

    //        auto pos = pointLight->GetLightDirection();
    //        ImGui::DragFloat3("Pos1", &pos[0], 0.1f, -5.f, 5.f);
    //        pointLight->SetLightDirection(pos);
    //        ImGui::Separator();
    //    }
    //    else if (light->GetLightType() == JSEngine::LightType::POINT_LIGHT)
    //    {
    //        ImGui::Text(std::string("PointLight " + uniqueID).c_str());
    //        ImGui::Separator();
    //        const auto& pointLight = JSEngine::CastLightTo<JSEngine::PointLight>(light);
    //        auto color = pointLight->GetColor();
    //        ImGui::ColorEdit3("Color", &color[0]);
    //        pointLight->SetColor(color);

    //        auto pos = pointLight->GetPosition();
    //        ImGui::DragFloat3("Pos", &pos[0], 0.1f, -5.f, 5.f);
    //        pointLight->SetPosition(pos);
    //        ImGui::Separator();
    //    }
    //}
    //ImGui::End();



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
    m_Scene->OnEvent(e);
}



