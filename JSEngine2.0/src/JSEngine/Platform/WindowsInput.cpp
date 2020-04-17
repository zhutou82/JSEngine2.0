#include "PCH.h"
#include "JSEngine/Application.h"
#include "WindowsInput.h"


namespace JSEngine 
{
    InputManager* InputManager::s_Instance = new WindowsInput();

    WindowsInput::WindowsInput()
    {
        memset(m_Keys, false, NUM_OF_KEYS);
        memset(m_MouseKey, false, NUM_OF_MOUSE_KYES);
    }

    bool WindowsInput::IsKeyReleasedImp(int keycode)
    {
        bool state = glfwGetKey(g_AppWindowHandle, keycode) == GLFW_RELEASE;
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

    //mouse and keyboard press functions
    bool WindowsInput::IsKeyPressedImp(int keycode)
    {
        return IsButtonDown(keycode, glfwGetKey);
    }
    bool WindowsInput::IsMouseLeftButtonPressedImp()
    {
        return IsButtonDown(JS_MOUSE_BUTTON_LEFT, glfwGetMouseButton);
    }
    bool WindowsInput::IsMouseRightButtonPressedImp()
    {
        return IsButtonDown(JS_MOUSE_BUTTON_RIGHT, glfwGetMouseButton);
    }

    bool WindowsInput::IsButtonDown(int code, const std::function<int(GLFWwindow*, int)>& fn)
    {
        return fn(g_AppWindowHandle, code);
    }

    //mouse and keyboard toggled functions
    bool WindowsInput::IsKeyToggledImp(int keycode)
    {
        return IsButtonToggled(m_Keys, keycode, glfwGetKey);
    }
    bool WindowsInput::IsMouseLeftButtonToggledImp()
    {
        return IsButtonToggled(m_MouseKey, JS_MOUSE_BUTTON_LEFT, glfwGetMouseButton);
    }
    bool WindowsInput::IsMouseRightButtonToggledImp()
    {
        return IsButtonToggled(m_MouseKey, JS_MOUSE_BUTTON_RIGHT, glfwGetMouseButton);
    }
    bool WindowsInput::IsButtonToggled(bool* array, int code,const std::function<int    (GLFWwindow*, int)>& fn)
    {
        bool state = fn(g_AppWindowHandle, code) == GLFW_PRESS;
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
    float WindowsInput::GetMouseXposImp()
    {
        auto[x, y] = GetMousePosImp();
        return x;
    }
    float WindowsInput::GetMouseYposImp()
    {
        auto[x, y] = GetMousePosImp();
        return y;
    }
    std::pair<float, float> WindowsInput::GetMousePosImp()
    {
        double x, y;
        glfwGetCursorPos(g_AppWindowHandle, &x, &y);
        return std::make_pair((float)x, (float)y);
    }
}