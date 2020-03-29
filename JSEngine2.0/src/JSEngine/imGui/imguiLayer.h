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
    public:

        imguiLayer(const std::string& name = "imguiLayer")
            : Layer(name), m_imguiLayerTime(0)
        {}

        void OnUpdate() override;
        void OnAttach() override;
        void OnDetach() override;

        void OnEvent(Event& e) override;
        
        void Init();
        void Shutdonw();
    private:
        
        bool MousePressEventHandler(MouseButtonPressEvent& e);

        float m_imguiLayerTime;


    };


}