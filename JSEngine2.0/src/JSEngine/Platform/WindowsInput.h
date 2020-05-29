#pragma once
#include "JSEngine/Core/SingletonBaseClass.h"
#include "JSEngine/Managers/InputManager.h"


namespace JSEngine
{
    /* Printable keys */
#define JS_RELEASE                 0
#define JS_PRESS                   1
#define JS_REPEAT                  2

    class WindowsInput : public InputManager
    {
        static constexpr int NUM_OF_KEYS = 512;
        static constexpr int NUM_OF_MOUSE_KYES = 8;

    public:
        
        WindowsInput();

    protected:

        bool IsKeyPressedImp  (int keycode)      override;
        bool IsKeyReleasedImp (int keycode)      override;
        bool IsKeyToggledImp(int keycode)        override;
        bool IsMouseLeftButtonPressedImp()       override;
        bool IsMouseRightButtonPressedImp()      override;
        bool IsMouseLeftButtonToggledImp()       override;
        bool IsMouseRightButtonToggledImp()      override;
        bool IsMouseMiddleButtonPressedImp()     override;
        bool IsMouseMiddleButtonToggledImp()     override;
        float GetMouseXposImp()                  override;
        float GetMouseYposImp()                  override;
        std::pair<float, float> GetMousePosImp() override;

        

    private:
        bool IsButtonToggled(bool* array, int code,const std::function<int(GLFWwindow*, int)>& fn);
        bool IsButtonDown(int code,const std::function<int(GLFWwindow*, int)>& fn);
    
    private:
        
        bool m_Keys[NUM_OF_KEYS];
        bool m_MouseKey[NUM_OF_MOUSE_KYES];


    };


}