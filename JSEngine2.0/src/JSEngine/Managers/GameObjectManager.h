#pragma once
#include "JSEngine/Core/Core.h"
#include "JSEngine/Core/SingletonBaseClass.h"

namespace JSEngine
{

    class GameObjectManager : public Singleton<GameObjectManager>
    {
    public:
        friend class Singleton<GameObjectManager>;
        void Init();

        ~GameObjectManager(){}


    private:
        GameObjectManager() {}



    };


}