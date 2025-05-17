#include "Game2DLayer.h"
#include "glm/gtc/type_ptr.hpp"
#include <Random>
//#include "assimp/"
//#include "Box2D/Box2D/Collision/b2BroadPhase.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


Game2DLayer::Game2DLayer() 
    : Layer("Game2DLayer"),
    m_Camera(JSEngine::CreateRef<JSEngine::OrthographicCameraController>(g_AppWindow->GetAspectRatio(), glm::vec2(0, 0))), m_ParticalSystem(10000), world({ 0, -0.98f })
{
    m_ParticleProp.Position = { 0.f, 0.f };

    m_ParticleProp.SizeStart = { 0.5f, 0.5f };
    m_ParticleProp.SizeEnd = { 0.f, 0.f };
    m_ParticleProp.SizeVairation = 0.3f;

    m_ParticleProp.ColorBegin = { 1.f, .4f, 0.1f, 1.f };
    m_ParticleProp.ColorEnd =   { 0.f, 0.1f, 1.f, 0.f };

    m_ParticleProp.Velocity = { 0.3f, 0.005f };
    m_ParticleProp.VelocityVariation = 2.f;

    m_ParticleProp.Rotation = 0.f;
    m_ParticleProp.LifeTime = 3.f;

    m_ParticleProp.Acceleration = { 0, -0.005 };

}

Game2DLayer::~Game2DLayer()
{

    // By deleting the world, we delete the bomb, mouse joint, etc.
    //delete m_world;
    //m_world = NULL;

    JSEngine::Renderer2D::Shutdown();
}

void Game2DLayer::OnAttach()
{
    Assimp::Importer importer;

    JSEngine::Random::Init();
    JSEngine::Renderer2D::Init();

    m_AwesomeFace = g_ResourceMgr.Acquire2DTexture("awesomeface");
    m_Bobo        = g_ResourceMgr.Acquire2DTexture("Bobo");
    m_Robot       = g_ResourceMgr.Acquire2DTexture("character_robot_sheetHD");

    m_RobotSub = JSEngine::SubTexture2D::Create(m_Robot, { 9, 5 }, { 1 , 1 , 1, 1 });

    m_Animation = JSEngine::CreateRef<JSEngine::Animation2D>(m_Robot, glm::ivec2(9, 5));
    
    g_Physics.Init({ 0, -0.9f });
    g_Physics.CreateGround({ 0, -5 }, { 40.f, 1.f });

    for (int i = 0; i < 350; ++i)
    {
        float quadSize = JSEngine::Random::Float(0.1f, 1.f);
        g_Physics.AddToBox2DVec(JSEngine::Box2D::Create({ JSEngine::Random::Float(-10.5f, 15.5), JSEngine::Random::Float(10.f, 15.f) }, { quadSize, quadSize }));
    }

}

void Game2DLayer::OnDetach()
{

}


void Game2DLayer::OnUpdate(JSEngine::TimeStep delta)
{
    
    m_Camera->OnUpdate(delta);
    
    static glm::vec2 startPos = { 0, 0 };
    static float step = 0.3f;
    static glm::vec2 size{ step * 0.9f };
    // emit particales based on input
    if (g_Input.IsLeftMouseButtonPressed())
    {
        // Get screen mouse position
        float mouseX = (float)g_Input.GetMousePos().first;
        float mouseY = (float)g_Input.GetMousePos().second;

        // Convert to normalized device coordinates (NDC) [-1, 1]
        float x = (2.0f * mouseX) / g_AppWindow->GetWidth() - 1.0f;
        float y = 1.0f - (2.0f * mouseY) / g_AppWindow->GetHeight(); // Invert Y for screen coord
        glm::vec4 screenPos = glm::vec4(x, y, 0.0f, 1.0f);

        // Invert ViewProjection matrix to convert from NDC to world
        glm::mat4 viewProj = m_Camera->GetCamera().GetViewProjectMatrix();
        glm::mat4 invVP = glm::inverse(viewProj);
        glm::vec4 worldPos = invVP * screenPos;

        glm::vec2 pos = glm::vec2(worldPos.x, worldPos.y);

        m_ParticleProp.Position = pos;
        m_ParticalSystem.Emit(m_ParticleProp);
    }

    JSEngine::RenderCommand::Clear({ 0.1, 0.1, 0.0, 1 });
    m_ParticalSystem.Update(delta);
    m_ParticalSystem.OnRender(m_Camera);

    
    JSEngine::Renderer2D::BeginScene(m_Camera);

    g_Physics.OnUpdate(delta);
    for (const auto& elem : g_Physics.GetBox2DVec())
    {
        glm::vec2 pos = { elem->GetBody()->GetPosition().x , elem->GetBody()->GetPosition().y };
        JSEngine::Renderer2D::DrawRotatedQuad(pos, elem->GetSize(), elem->GetBody()->GetAngle(), glm::vec4(1.f), m_Bobo->GetTextureID());
    }

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
    //ImGui::DragInt("Index: ", (int*)&index, 1, 0, 19);
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

    ImGui::Begin("Particle properties");
    ImGui::Separator();

    ImGui::ColorEdit4("Color Begin: ", value_ptr(m_ParticleProp.ColorBegin));
    ImGui::ColorEdit4("Color End: ", value_ptr(m_ParticleProp.ColorEnd));

    ImGui::DragFloat2("Size Begin: ", value_ptr(m_ParticleProp.SizeStart), 0.1f, 0.f, 2.f);
    ImGui::DragFloat2("Size End: ", value_ptr(m_ParticleProp.SizeEnd), 0.1f, 0.f, 2.f);

    ImGui::DragFloat("Life time: ", &m_ParticleProp.LifeTime, 1.f, 0.f, 10.f);
    

    ImGui::Separator();
    ImGui::End();

}

void Game2DLayer::OnEvent(JSEngine::Event& e)
{
    m_Camera->OnEvent(e);
}
