#include "JSEngine/Application.h"
#include "WindowsInput.h"
#include "JSEngine/PCH.h"

namespace JSEngine
{
    WindowsInput::WindowsInput()
    {
        memset(m_Keys, false, NUM_OF_KEYS);
        memset(m_MouseKey, false, NUM_OF_MOUSE_KYES);
    }

    bool WindowsInput::IsKeyReleasedImp(int keycode)
    {
        bool state = glfwGetKey((GLFWwindow*)g_Application->GetWindow()->GetNativeWindow(), keycode) == GLFW_RELEASE;
        if (m_Keys[keycode] && state)
        {
            m_Keys[keycode] = false;
            return true;
        }
        else if (!m_Keys[keycode] && !state)
        {
            m_Keys[keycode] = true;
        }
        return false;
    }

    //mouse and keyboard down functions
    bool WindowsInput::IsKeyDownImp(int keycode)
    {
        return IsButtonDown(keycode, glfwGetKey);
    }
    bool WindowsInput::IsMouseLeftButtonDownImp()
    {
        return IsButtonDown(JS_MOUSE_BUTTON_LEFT, glfwGetMouseButton);
    }
    bool WindowsInput::IsMouseRightButtonDownImp()
    {
        return IsButtonDown(JS_MOUSE_BUTTON_RIGHT, glfwGetMouseButton);
    }

    bool WindowsInput::IsButtonDown(int code, std::function<int(GLFWwindow*, int)> fn)
    {
        return fn((GLFWwindow*)g_Application->GetWindow()->GetNativeWindow(), code);
    }

    //mouse and keyboard press functions
    bool WindowsInput::IsKeyPressedImp(int keycode)
    {
        return IsButtonPressed(m_Keys, keycode, glfwGetKey);
    }
    bool WindowsInput::IsMouseLeftButtonPressedImp()
    {
        return IsButtonPressed(m_MouseKey, JS_MOUSE_BUTTON_LEFT, glfwGetMouseButton);
    }
    bool WindowsInput::IsMouseRightButtonPressedImp()
    {
        return IsButtonPressed(m_MouseKey, JS_MOUSE_BUTTON_RIGHT, glfwGetMouseButton);
    }

    bool WindowsInput::IsButtonPressed(bool* array, int code, std::function<int(GLFWwindow*, int)> fn)
    {
        bool state = fn((GLFWwindow*)g_Application->GetWindow()->GetNativeWindow(), code) == GLFW_PRESS;
        if (state && !array[code])
        {
            array[code] = true;
            return true;
        }
        else if (array[code] && !state)
        {
            array[code] = false;
        }
        return false;
    }
}