#pragma once
#include "JSEngine/Window.h"
#include "GLFW/glfw3.h"

namespace JSEngine
{
    class JSENGINE_API WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowsProp& wp);
        ~WindowsWindow() { ShutDown(); }

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; }
        unsigned int GetHeight() const override { return m_Data.Height; }



        void AddCallBackFn(const EventCallBackFn& eventCallBkFn) override {
            m_Data.EventCallBackFunction
                = eventCallBkFn;
        }
        bool IsVSync() const override { return m_Data.VSync; }
        void SetVSync(bool b) override;


    private:

        void Init(const WindowsProp& wp);
        void ShutDown();

        struct WindowData
        {
            unsigned int Width;
            unsigned int Height;
            bool VSync;
            std::string Title;
            EventCallBackFn EventCallBackFunction;
        };

        WindowData m_Data;
        GLFWwindow* m_Window;
    };
}
