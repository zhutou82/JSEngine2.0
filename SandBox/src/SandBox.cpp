#include <JSEngine.h>
//--------------Entry point---------------------
#include <JSEngine/Core/EntryPoint.h>
//---------------------------------------------- 
#include "Game2DLayer.h"
#include "Game3DLayer.h"

class SandBox : public JSEngine::Application
{
public:
    SandBox()
    {
        PushLayer(new Game2DLayer());
        //PushLayer(new Game3DLayer());
        PushOverLay(new JSEngine::imguiLayer());

    }
    ~SandBox()
    {

    }

private:


};

JSEngine::Application* JSEngine::CreateApplication()
{
    return new SandBox;
}
