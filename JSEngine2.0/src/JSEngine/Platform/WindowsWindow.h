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

    public:

        void OnUpdate             ()                                           override;
        unsigned int GetWidth     () const                                     override { return m_Data.Width; }
        unsigned int GetHeight    () const                                     override { return m_Data.Height; }
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
        };
        GLFWwindow* m_Window;
        WindowData  m_Data;
    };
}
