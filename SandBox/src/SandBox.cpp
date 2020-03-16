#include <JSEngine.h>

class SandBox : public JSEngine::Application
{
public:
    SandBox()
    {

    }
    ~SandBox()
    {

    }
};

JSEngine::Application*  JSEngine::CreateApplication()
{
    return new SandBox;
}
