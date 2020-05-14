#include "PCH.h"
#include "Box2D.h"


namespace JSEngine
{
    Ref<Box2D> Box2D::Create(const glm::vec2& pos, const glm::vec2& size)
    {
        return CreateRef<Box2D>(pos, size);
    }

    Box2D::Box2D(const glm::vec2& pos, const glm::vec2& size)
    {
        m_Size = size;

        b2Vec2 position(pos.x, pos.y);
        m_BodyDef.type = b2_dynamicBody;
        m_BodyDef.position = position;
        

        m_Body = g_Physics.m_World->CreateBody(&m_BodyDef);


        // Define another box shape for our dynamic body.
        m_PolygonShape.SetAsBox(size.x / 2.f, size.y / 2.f);
        

        m_FixtureDef.shape = &m_PolygonShape;
        // Set the box density to be non-zero, so it will be dynamic.
        m_FixtureDef.density = 2.f;
        // Override the default friction.
        m_FixtureDef.friction = 0.3f;

        m_Body->CreateFixture(&m_FixtureDef);

        //b2PolygonShape dynamicBox;
        //dynamicBox.SetAsBox(size.x/2.f, size.y / 2.f);
        //b2BodyDef box;
        //b2Vec2 position{ pos.x, pos.y };
        //box.type = b2_dynamicBody;
        //box.position = position;
        //b2Body* b1 = g_Physics.GetWorld()->CreateBody(&box);
        //b2FixtureDef fixtureDef;
        //fixtureDef.shape = &dynamicBox;
        //// Set the box density to be non-zero, so it will be dynamic.
        //fixtureDef.density = 1.0f;
        //// Override the default friction.
        //fixtureDef.friction = 0.3f;
        //b1->CreateFixture(&fixtureDef);

        //b1->GetPosition();
    }

    const glm::vec2& Box2D::GetPosition()
    {
        // TODO: insert return statement here
        m_Pos = { m_Body->GetPosition().x, m_Body->GetPosition().y };
        return m_Pos;
    }

    void Box2D::SetPosition(const glm::vec2& pos)
    {
    }

}