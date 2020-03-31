#pragma once
#include "JSEngine/Window.h"
#include "glad/glad.h"
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

        unsigned int GetFrameBufferWidth() const {  return static_cast<unsigned int>(m_Data.FrameBufferWidth); }
        unsigned int GetFrameBufferHeight() const { return static_cast<unsigned int>(m_Data.FrameBufferHeight); }

        float GetSystemCurrentTime() const override { return (float)glfwGetTime(); }

        void AddCallBackFn(const EventCallBackFn& eventCallBkFn) override {
            m_Data.EventCallBackFunction
                = eventCallBkFn;
        }
        bool IsVSync() const override { return m_Data.VSync; }
        void SetVSync(bool b) override;
        
        void* GetNativeWindow() const override { return m_Window; }
        
    private:
        void Init(const WindowsProp& wp);
        void ShutDown();

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

        WindowData m_Data;
       
    };
}
