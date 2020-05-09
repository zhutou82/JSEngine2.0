#include "Game2DLayer.h"

Game2DLayer::Game2DLayer() 
    : Layer("Game2DLayer"),
      m_Camera(JSEngine::CreateRef<JSEngine::OrthographicCameraController>(g_AppWindow->GetAspectRatio(), glm::vec2(0, 0)))
{

}

Game2DLayer::~Game2DLayer()
{
    JSEngine::Renderer2D::Shutdown();
}

void Game2DLayer::OnAttach()
{
    JSEngine::Renderer2D::Init();
}

void Game2DLayer::OnDetach()
{

}

int index = 2;

void Game2DLayer::OnUpdate(JSEngine::TimeStep delta)
{
    m_Camera->OnUpdate(delta);
    static glm::vec2 startPos = { 0, 0 };
    static float step = 0.3f;
    static glm::vec2 size{ step * 0.9f };

    JSEngine::RenderCommand::Clear({ 0.1, 0.1, 0.0, 1 });
    JSEngine::Renderer2D::BeginScene(m_Camera);

    //JSEngine::Renderer2D::DrawQuad(startPos, { 0.2f, 0.2f }, glm::vec4(1.f), 2);
    
    //index += delta;
    //CLIENT_INFO("{0}", index);
    JSEngine::Renderer2D::DrawAnimatedQuad(glm::vec3(0.f), { 0.2f, 0.2f }, 0, glm::vec4(1.f), 2, (int)index);
    //JSEngine::Renderer2D::DrawQuad({ 1.f, 1.f }, 1, color, 1);

    //for (float i = -5.f; i < 5.f; i += step)
    //{
    //    for (float j = -5.f; j < 5.f; j += step)
    //    {
    //        glm::vec4 color = { (i + 5.f) / 10.f, 0.3f, (j + 5.f) / 10.f, 1.f };
    //        JSEngine::Renderer2D::DrawQuad({ startPos.x + j, startPos.y + i }, size, color, 1);
    //    }
    //}

    JSEngine::Renderer2D::EndScene();
    JSEngine::Renderer2D::Flush();

}

void Game2DLayer::OnRenderUpdate(JSEngine::TimeStep delta)
{



    ImGui::Begin("Renderer2D info");
    const auto& stats =  JSEngine::Renderer2D::GetSceneStats();
    const auto& data = JSEngine::Renderer2D::GetSceneData();
    ImGui::Text("Frame rate: %f", 1.f/delta);
    ImGui::Separator();
    ImGui::DragInt("Number of Quads per draw call: ", (int*)&data.NumberOfQuadsPerDrawCall);
    ImGui::DragInt("Index: ", &index, 1, 0, 19);
    ImGui::Columns(2, "Renderer stats"); // 2-ways, with border
    ImGui::Text("Drawn "); ImGui::NextColumn();
    ImGui::Text("Number "); ImGui::NextColumn();
    ImGui::Separator();

    ImGui::Text("Draw call: "); ImGui::NextColumn();
    ImGui::Text("%i", stats.NumberOfDrawCall); ImGui::NextColumn();

    ImGui::Text("Quads "); ImGui::NextColumn();
    ImGui::Text("%i", stats.NumberOfQuadDrawn); ImGui::NextColumn();

    ImGui::Text("Vertices "); ImGui::NextColumn();
    ImGui::Text("%i", stats.NumberOfVerticesDrawn); ImGui::NextColumn();

    ImGui::Text("Indices "); ImGui::NextColumn();
    ImGui::Text("%i", stats.NumberOfIndicesDrawn); ImGui::NextColumn();



    ImGui::Separator();
    ImGui::End();
}

void Game2DLayer::OnEvent(JSEngine::Event& e)
{
    m_Camera->OnEvent(e);
}
