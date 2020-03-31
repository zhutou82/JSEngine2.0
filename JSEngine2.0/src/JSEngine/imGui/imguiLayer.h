#pragma once
#include "JSEngine/PCH.h"
#include "JSEngine/Layer.h"
#include "imconfig.h"
#include "imgui.h"
#include "JSEngine/Event/MouseEvent.h"
#include "JSEngine/Event/Event.h"
#include "JSEngine/Event/ApplicationEvent.h"
#include "JSEngine/Event/KeyEvent.h"


namespace JSEngine
{
    class JSENGINE_API imguiLayer : public Layer
    {
        static constexpr const char* JS_GL_VERSION = "#version 410";

    public:

        imguiLayer(const std::string& name = "imguiLayer")
            : Layer(name), m_imguiLayerTime(0)
        {}

        void OnUpdate() override;
        void OnAttach() override;
        void OnDetach() override;

        void OnEvent(Event& e) override;
        

    private:
        bool MousePressedEvent(MouseButtonPressEvent& e);
        bool MouseReleasedEvent(MouseButtonReleaseEvent& e);
        bool MouseScrolledEvent(MouseScrollEvent& e);
        bool MouseMovedEvent(MouseMoveEvent& e);
        bool KeyPressedEvent(KeyPressEvent& e);
        bool KeyReleasedEvent(KeyReleseEvent& e);
        bool KeyTypedEvent(KeyCharEvent& e);
        bool WindowReziedEvent(WindowReSizeEvent& e);


    private:
        
        float m_imguiLayerTime;

    };


}