#pragma once
#include <functional>
#include <string>
#include "Core.h"
#include "JSEngine/Event/Event.h"
#include "SingletonBaseClass.h"
namespace JSEngine
{
    struct WindowsProp
    {
        unsigned int Width;
        unsigned int Height;
        std::string Titile;

        WindowsProp(uint32_t width = 1280, 
                    uint32_t height= 720, 
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
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual float GetAspectRatio() const = 0;

        virtual void AddCallBackFn(const EventCallBackFn&) = 0;
        virtual bool IsVSync() const = 0;
        virtual void SetVSync(bool b) = 0;

        virtual float GetSystemCurrentTime() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Window* Create(const WindowsProp& wp = WindowsProp());

    private:
    };
}