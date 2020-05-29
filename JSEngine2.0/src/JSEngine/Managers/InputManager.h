#pragma once
#include "JSEngine/Core/Core.h"
#include "JSEngine/Core/Keycode.h"
#include "JSEngine/Core/MouseCode.h"

#define g_Input JSEngine::InputManager::GetInstance()

namespace JSEngine
{
    //base class
    class JSENGINE_API InputManager
    {
    public:
        InputManager() {}

        static bool IsKeyPressed    (int keycode)    { return s_Instance->IsKeyPressedImp(keycode);       }
        static bool IsKeyReleased   (int keycode)    { return s_Instance->IsKeyReleasedImp(keycode);      }
        static bool IsKeyToggle(int keycode)         { return s_Instance->IsKeyToggledImp(keycode);       }
        static bool IsLeftMouseButtonPressed()       { return s_Instance->IsMouseLeftButtonPressedImp();  }
        static bool IsRightMouseButtonPressed()      { return s_Instance->IsMouseRightButtonPressedImp(); }
        static bool IsLeftMouseButtonToggled()       { return s_Instance->IsMouseLeftButtonToggledImp();  }
        static bool IsRightMouseButtonToggled()      { return s_Instance->IsMouseRightButtonToggledImp(); }
        static bool IsMiddleMouseButtonPressed()     { return s_Instance->IsMouseMiddleButtonPressedImp();}
        static bool IsMiddleMouseButtonToggled()     { return s_Instance->IsMouseMiddleButtonToggledImp();}
        static float GetMouseXpos()                  { return s_Instance->GetMouseXposImp();              }
        static float GetMouseYpos()                  { return s_Instance->GetMouseYposImp();              }
        static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImp();               }
        
        static InputManager& GetInstance() { return *s_Instance;  }
    protected:
        //keyboard
        virtual bool IsKeyPressedImp (int keycode)       = 0;
        virtual bool IsKeyReleasedImp(int keycode)       = 0;
        virtual bool IsKeyToggledImp (int keycode)       = 0; 

        ////mouse 
        virtual bool IsMouseLeftButtonPressedImp()       = 0;
        virtual bool IsMouseRightButtonPressedImp()      = 0;
        virtual bool IsMouseLeftButtonToggledImp()       = 0;
        virtual bool IsMouseRightButtonToggledImp()      = 0;
        virtual bool IsMouseMiddleButtonPressedImp()     = 0;
        virtual bool IsMouseMiddleButtonToggledImp()     = 0;
        virtual float GetMouseXposImp()                  = 0;
        virtual float GetMouseYposImp()                  = 0;
        virtual std::pair<float, float> GetMousePosImp() = 0;

    private:
        static InputManager* s_Instance;
        
    };

    //InputManager* InputManager::s_Instance = NULL;
}
