#pragma once
#include "JSEngine/Core/Window.h"
#include "GLFW/glfw3.h"

namespace JSEngine
{
    class JSENGINE_API WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowsProp& wp);
        ~WindowsWindow() { ShutDown(); }

    public:

        void OnUpdate             ()                                           override;
        uint32_t GetWidth() const                                              override { return m_Data.Width; }
        uint32_t GetHeight() const                                             override { return m_Data.Height; }
        float GetAspectRatio() const                                           override { return m_Data.AspectRatio; }
        float GetSystemCurrentTime() const                                     override { return (float)glfwGetTime(); }
        bool IsVSync              () const                                     override { return m_Data.VSync; }
        void* GetNativeWindow     () const                                     override { return m_Window; }
        void AddCallBackFn        (const EventCallBackFn& eventCallBkFn)       override { m_Data.EventCallBackFunction   = eventCallBkFn;}
        void SetVSync             (bool b)                                     override;

        unsigned int GetFrameBufferWidth()  const { return static_cast<unsigned int>(m_Data.FrameBufferWidth); }
        unsigned int GetFrameBufferHeight() const { return static_cast<unsigned int>(m_Data.FrameBufferHeight); }
    private:
        void Init(const WindowsProp& wp);
        void ShutDown();
        void SetWindowsEventCallBack();

    private:
        struct WindowData
        {
            unsigned int Width;
            unsigned int Height;
            int FrameBufferWidth;
            int FrameBufferHeight;
            bool VSync;
            std::string Title;
            EventCallBackFn EventCallBackFunction;
            float AspectRatio;
        };
        GLFWwindow* m_Window;
        WindowData  m_Data;
    };
}
