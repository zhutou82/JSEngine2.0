#include "PCH.h"
#include "JSEngine/Platform/WindowsWindow.h"
#include "JSEngine/Event/ApplicationEvent.h"
#include "JSEngine/Event/MouseEvent.h"
#include "JSEngine/Event/KeyEvent.h"
#include "JSEngine/Platform/Opengl/OpenGLContext.h"

namespace JSEngine
{
    static bool s_WindowHasInitialized = false;

    Window* Window::Create(const WindowsProp& wp)
    {
        return new WindowsWindow(wp);
    }

    WindowsWindow::WindowsWindow(const WindowsProp& wp)
    {
        Init(wp);
    }
    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
    }

    void WindowsWindow::SetVSync(bool b)
    {
        glfwSwapInterval(b ? 1 : 0); 
        m_Data.VSync = b;
    } 

    void WindowsWindow::Init(const WindowsProp& wp)
    {
        m_Data.Width = wp.Width;
        m_Data.Height = wp.Height;
        m_Data.Title = wp.Titile;
        m_Data.AspectRatio = (float)wp.Width / wp.Height;

        if (s_WindowHasInitialized == false)
        {
            bool success = glfwInit();
            JS_CORE_ASSERT(success, "GLFW init failed");

            s_WindowHasInitialized = true;
        }
        //init window
        m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        JS_CORE_ASSERT(m_Window, "Windows Init failed");
        SetVSync(true);
        JS_CORE_INFO("Window created {0} {1}", m_Data.Width, m_Data.Height);

        //glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //init windows call back event
        SetWindowsEventCallBack();

        //init graphics context
        g_GraphicsConext.Init(m_Window);

    }

    void WindowsWindow::SetWindowsEventCallBack()
    {
        glfwSetWindowUserPointer(m_Window, &m_Data);
        //Set glfw call back functions
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
            {
                WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                data.Height = height;
                data.Width = width;
                glfwGetFramebufferSize(window, &data.FrameBufferWidth, &data.FrameBufferHeight);
                WindowReSizeEvent event(width, height);
                data.EventCallBackFunction(event);
            }
        );

        glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos)
            {
                WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                WindowMoveEvent e(xpos, ypos);
                data.EventCallBackFunction(e);
            });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
            {
                WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                WindowCloseEvent e;
                data.EventCallBackFunction(e);
            });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                switch (action)
                {
                case GLFW_PRESS:
                {
                    KeyPressEvent e(key, 0);
                    data.EventCallBackFunction(e);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleseEvent e(key);
                    data.EventCallBackFunction(e);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressEvent e(key, 1);
                    data.EventCallBackFunction(e);
                    break;
                }
                }
            });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mod)
            {
                WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                switch (action)
                {
                case GLFW_PRESS:
                {
                    MouseButtonPressEvent e(button);
                    data.EventCallBackFunction(e);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleaseEvent e(button);
                    data.EventCallBackFunction(e);
                    break;
                }
                }
            });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffet, double yoffset)
            {
                WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                MouseScrollEvent e((float)xoffet, (float)yoffset);
                data.EventCallBackFunction(e);
            });


        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xcoord, double ycoord)
            {
                WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                MouseMoveEvent e((float)xcoord, (float)ycoord);
                data.EventCallBackFunction(e);
            });


        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
            {
                WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                KeyCharEvent e((int)keycode);
                data.EventCallBackFunction(e);
            });

    }

    void WindowsWindow::ShutDown()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
}