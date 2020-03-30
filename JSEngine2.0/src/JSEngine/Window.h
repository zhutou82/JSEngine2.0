#pragma once
#include <functional>
#include <string>
#include "Core.h"
#include "Event/Event.h"
#include "SingletonBaseClass.h"
namespace JSEngine
{
    struct WindowsProp
    {
        unsigned int Width;
        unsigned int Height;
        std::string Titile;

        WindowsProp(unsigned int width = 1280, 
                    unsigned int height= 720, 
                    const std::string& title = "JSEngine2.0" )
            : Width(width), Height(height), Titile(title)
        {}

    };

    class JSENGINE_API Window 
    {
      
    public:

        using EventCallBackFn = std::function<void(Event&)>;
        
        virtual ~Window() {}
        
        virtual void OnUpdate() = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void AddCallBackFn(const EventCallBackFn&) = 0;
        virtual bool IsVSync() const = 0;
        virtual void SetVSync(bool b) = 0;

        virtual double GetSystemCurrentTime() const = 0;

        static Window* Create(const WindowsProp& wp = WindowsProp());

    private:
    };
}