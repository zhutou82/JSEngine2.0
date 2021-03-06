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

    g_Physics.Init({ 0, -9.8f });
    g_Physics.CreateGround({ 0, -5 }, { 40.f, 1.f });

    for (int i = 0; i < 50; ++i)
    {
        float quadSize = JSEngine::Random::Float(0.5f, 2.f);
        g_Physics.AddToBox2DVec(JSEngine::Box2D::Create({ JSEngine::Random::Float(-10.5f, 15.5), JSEngine::Random::Float(10.f, 15.f) }, { quadSize, quadSize }));
    }
        // Define the gravity vector.
    // Define the ground body.
    //b2BodyDef groundBodyDef;
    //groundBodyDef.position.Set(0.0f, 0.0f);

    //// Call the body factory which allocates memory for the ground body
    //// from a pool and creates the ground box shape (also from a pool).
    //// The body is also added to the world.
    //groundBody = world.CreateBody(&groundBodyDef);

    //// Define the ground box shape.
    //b2PolygonShape groundBox;

    //groundWH = { 10.f, 1.f };
    //boxWH = {.1f, .1f };

    //// The extents are the half-widths of the box.
    //groundBox.SetAsBox(groundWH.x/2, groundWH.y/2);

    //// Add the ground fixture to the ground body.
    //groundBody->CreateFixture(&groundBox, 0.0f);

    //// Define the dynamic body. We set its position and call the body factory.
    //b2BodyDef bodyDef;
    //bodyDef.type = b2_dynamicBody;
    //bodyDef.position.Set(0.0f, 4.0f);
    //body = world.CreateBody(&bodyDef);

    //// Define another box shape for our dynamic body.
    //b2PolygonShape dynamicBox;
    //dynamicBox.SetAsBox(boxWH.x/2, boxWH.y/2);

    //// Define the dynamic body fixture.
    //b2FixtureDef fixtureDef;
    //fixtureDef.shape = &dynamicBox;

    //// Set the box density to be non-zero, so it will be dynamic.
    //fixtureDef.density = 1.0f;

    //// Override the default friction.
    //fixtureDef.friction = 0.3f;

    //// Add the shape to the body.
    //body->CreateFixture(&fixtureDef);


}

void Game2DLayer::OnDetach()
{

}

float index = 0;

void Game2DLayer::OnUpdate(JSEngine::TimeStep delta)
{
    
    m_Camera->OnUpdate(delta);
    
    static glm::vec2 startPos = { 0, 0 };
    static float step = 0.3f;
    static glm::vec2 size{ step * 0.9f };

    if (g_Input.IsLeftMouseButtonPressed())
    {
        //auto& mousePos = m_Camera->GetCamera().GetViewProjectMatrix() * glm::vec4(g_Input.GetMousePos().first, g_Input.GetMousePos().second, 0, 0);
        auto& mousePos = glm::vec4(g_Input.GetMousePos().first, g_Input.GetMousePos().second, 0, 0);

        glm::vec2 pos(1.f); //{ mousePos.x, mousePos.y };
        pos.x =   (float)mousePos.x / (float)g_AppWindow->GetWidth()  * m_Camera->GetBound().GetWidth() - 0.5f * m_Camera->GetBound().GetWidth();
        pos.y = -((float)mousePos.y / (float)g_AppWindow->GetHeight() * m_Camera->GetBound().GetHeigh() - 0.5f * m_Camera->GetBound().GetHeigh());

        auto& cameraPos = m_Camera->GetCamera().GetPosition();

        m_ParticleProp.Position = { cameraPos.x + pos.x, cameraPos.y + pos.y };
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
        //glm::vec2 size = 
        JSEngine::Renderer2D::DrawRotatedQuad(pos, elem->GetSize(), elem->GetBody()->GetAngle(), glm::vec4(1.f), m_Bobo->GetTextureID());
    }

    //world.Step(delta, 3, 1);
    
    //JSEngine::Renderer2D::DrawQuad({ groundBody->GetPosition().x, groundBody->GetPosition().y }, groundWH, glm::vec4(1.f), m_AwesomeFace->GetTextureID());
    //JSEngine::Renderer2D::DrawQuad({ body->GetPosition().x, body->GetPosition().y }, boxWH , glm::vec4(1.f), m_AwesomeFace->GetTextureID());

    //auto pos = { body->GetPosition().x, body->GetPosition().y };
    //JS_CORE_INFO("{0}, {1}", groundBody->GetPosition().y + groundWH.y/2 , body->GetPosition().y - boxWH.y/2);

    //m_groundBody->
    //JSEngine::Renderer2D::DrawQuad({ 0, 0 }, { 0.2f, 0.2f }, glm::vec4(1.f), m_Bobo->GetTextureID());
    //JSEngine::Renderer2D::DrawQuad({ 0.2, 0 }, { 0.2f, 0.2f }, glm::vec4(1.f), m_Bobo->GetTextureID());
    
    //JSEngine::Renderer2D::DrawSubTextureQuad({ 0.2,0.2,0 }, { 0.2f, 0.2f }, 0.f, glm::vec4(1.f), m_RobotSub);


    //m_Animation->OnUpdate(delta);
    //m_Animation->Play(0, 7, 0.1f);
    //JSEngine::Renderer2D::DrawAnimatedQuad({ -0.2, -0.2, 0 }, { 0.2f, 0.2f }, m_Robot, m_Animation);   



    //
    //index += delta;
    ////CLIENT_INFO("{0}", index);
    ////JSEngine::Renderer2D::DrawAnimatedQuad(glm::vec3(0.f), { 0.2f, 0.2f }, 0, glm::vec4(1.f), 2, (int)index);
    ////JSEngine::Renderer2D::DrawQuad({ 1.f, 1.f }, 1, color, 1);

    ////for (float i = -5.f; i < 5.f; i += step)
    ////{
    ////    for (float j = -5.f; j < 5.f; j += step)
    ////    {
    ////        glm::vec4 color = { (i + 5.f) / 10.f, 0.3f, (j + 5.f) / 10.f, 1.f };
    ////        JSEngine::Renderer2D::DrawQuad({ startPos.x + j, startPos.y + i }, size, color, 1);
    ////    }
    ////}

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
