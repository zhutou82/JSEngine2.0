#pragma once
#include "Physics2D.h"


namespace JSEngine
{
    class Box2D
    {
    public:

        Box2D(const glm::vec2& pos, const glm::vec2& size);
        ~Box2D() = default;

        const glm::vec2& GetPosition();
        void SetPosition(const glm::vec2& pos);

        const glm::vec2& GetSize() const { return m_Size; }
        void SetSize(const glm::vec2& size) { m_Size = size; }

        const b2Body* GetBody() const { return m_Body; }
        void SetBody(b2Body* body) { m_Body = body; }

        const b2BodyDef GetBodyDef() const { return m_BodyDef; }
        const b2FixtureDef& GetFixture() { return m_FixtureDef; }

        static Ref<Box2D> Create(const glm::vec2& pos, const glm::vec2& size);

    private:
        

        glm::vec2 m_Pos;
        glm::vec2 m_Size;

        b2Body* m_Body;
        b2BodyDef m_BodyDef;
        b2FixtureDef m_FixtureDef;

        b2Shape* m_Shape;
        float m_Friction;
        float m_Density;

        b2PolygonShape m_PolygonShape;
        

    };


}

