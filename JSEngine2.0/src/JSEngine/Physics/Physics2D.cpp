#include "PCH.h"
#include "Physics2D.h"
#include "Box2D.h"


namespace JSEngine
{

    Physics2D::~Physics2D()
    {

    }

    void Physics2D::Init(const glm::vec2& gravity)
    {
        m_Gravity = gravity;
        m_World = CreateRef<b2World>( b2Vec2{ m_Gravity.x, m_Gravity.y });
    }

    void Physics2D::CreateGround(const glm::vec2& pos, const glm::vec2& size)
    {
        //create ground
        b2BodyDef bodyDef;
        bodyDef.position = b2Vec2{ pos.x, pos.y };
        m_groundBody = m_World->CreateBody(&bodyDef);

        // Define the ground box shape.
        b2PolygonShape groundBox;
        // The extents are the half-widths of the box.
        groundBox.SetAsBox(size.x/2.f, size.y/2.f);

        // Add the ground fixture to the ground body.
        m_groundBody->CreateFixture(&groundBox, 0.0f);
    }

    void Physics2D::AddToBox2DVec(const Ref<Box2D>& box2D)
    {
        m_BoxesVec.push_back(box2D);
    }

    void Physics2D::OnUpdate(float delta)
    {
        m_World->Step(delta, m_VelocityIterations, m_PositionIterations);
    }

    void Physics2D::Shutdown()
    {

    }

}