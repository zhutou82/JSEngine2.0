#include <JSEngine.h>


class SandBox : public JSEngine::Application
{
public:
    SandBox()
    {
        PushOverLay(new JSEngine::imguiLayer());
    }
    ~SandBox()
    {

    }
};

JSEngine::Application*  JSEngine::CreateApplication()
{
    return new SandBox;
}
