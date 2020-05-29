#pragma once

#include "JSEngine/Scene/Scene.h"

namespace JSEngine
{

    class SceneRenderer
    {
    public:

        static void BeginScene(Scene3D* scene);

        //static void SetupEnvironment();
        static void SubmitEntity(Entity* entity);

        static void EndScene();
        static void Flush();


    };


}