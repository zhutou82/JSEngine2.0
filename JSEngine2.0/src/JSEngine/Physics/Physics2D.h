#pragma once
#include <vector>

#include "box2D/box2d.h"
#include "glm/glm.hpp"

#include "JSEngine/Core/SingletonBaseClass.h"
#include "JSEngine/Core/Core.h"



#define g_Physics JSEngine::Singleton<JSEngine::Physics2D>::GetInstance()

namespace JSEngine
{
    class Box2D;
    class Physics2D : public Singleton<Physics2D>
    {
    public:
        friend class Singleton<Physics2D>;
        friend class Box2D;

        ~Physics2D();

        void Init(const glm::vec2& gravity);
        void CreateGround(const glm::vec2& pos, const glm::vec2& size);
        

        void AddToBox2DVec(const Ref<Box2D>& box2D);
        void OnUpdate(float);

        const std::vector<Ref<Box2D>>& GetBox2DVec() const { return m_BoxesVec; }
        //void OnRender();
        void Shutdown();

        const Ref<b2World>& GetWorld() const { return m_World; }
       

    private:
        Physics2D() {};
        Ref<b2World> m_World;
        glm::vec2 m_Gravity;

        int32 m_VelocityIterations = 3;
        int32 m_PositionIterations = 1;  

        std::vector<Ref<Box2D>> m_BoxesVec;
        

        b2Body* m_groundBody;

        

    };

}

