#include "JSEngine/Platform/WindowsWindow.h"
#include "JSEngine/Log.h"
#include "JSEngine/Event/ApplicationEvent.h"
#include "JSEngine/Event/MouseEvent.h"
#include "JSEngine/Event/KeyEvent.h"


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
        glfwSwapBuffers(m_Window);
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

        if (s_WindowHasInitialized == false)
        {
            bool success = glfwInit();
            JS_CORE_ASSERT(success, "GLFW init failed");

            s_WindowHasInitialized = true;
        }
        JS_CORE_INFO("Window created {0} {1} {2}", m_Data.Title, m_Data.Width, m_Data.Height);
        m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        //Set glfw call back functions
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
            {
                WindowData data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                data.Height = height;
                data.Width = width;
                WindowReSizeEvent event(height, width);
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
                MouseScrollEvent e(xoffet, yoffset);
                data.EventCallBackFunction(e);
            });
    }

    void WindowsWindow::ShutDown()
    {
        glfwDestroyWindow(m_Window);
    }

}