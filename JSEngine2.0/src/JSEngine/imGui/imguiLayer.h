#pragma once
#include "JSEngine/Core/Layer.h"
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

        void OnUpdate(TimeStep delta)        override;
        void OnAttach()                      override;
        void OnDetach()                      override;
        void OnRenderUpdate(TimeStep delta)  override;
        void OnEvent(Event& e)               override;
        

        void Begin();
        void End();


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