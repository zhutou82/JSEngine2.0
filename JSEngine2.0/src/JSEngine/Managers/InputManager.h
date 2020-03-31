#pragma once
#include "JSEngine/Core.h"

namespace JSEngine
{
    //base class
    class JSENGINE_API InputManager
    {
    public:
        InputManager() {}

        bool IsKeyPressed    (int keycode) { return IsKeyPressedImp(keycode); }
        bool IsKeyReleased   (int keycode) { return IsKeyReleasedImp(keycode);}
        bool IsKeyDown(int keycode) { return IsKeyDownImp(keycode); }
        bool IsLeftMouseButtonPressed() { return IsMouseLeftButtonPressedImp();  }
        bool IsRightMouseButtonPressed() { return IsMouseRightButtonPressedImp();}

    protected:
        //keyboard
        virtual bool IsKeyPressedImp (int keycode) = 0;
        virtual bool IsKeyReleasedImp(int keycode) = 0;
        virtual bool IsKeyDownImp(int keycode) = 0;

        ////mouse 
        virtual bool IsMouseLeftButtonPressedImp() = 0;
        virtual bool IsMouseRightButtonPressedImp() = 0;
        virtual bool IsMouseLeftButtonDownImp() = 0; 
        virtual bool IsMouseRightButtonDownImp() = 0;

    private:
    };

    //InputManager* InputManager::s_Instance = NULL;
}
