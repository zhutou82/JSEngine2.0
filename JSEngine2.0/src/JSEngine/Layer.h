#pragma once
#include "Core.h"
#include "JSEngine/Event/Event.h"
#include <string>

namespace JSEngine
{
    class JSENGINE_API Layer
    {
    public:
        Layer(const std::string& name = "DebugLayer")
            : m_LayerName(name)
        {}
        virtual ~Layer() {}

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;

        virtual void OnUpdate() = 0;
        virtual void OnEvent(Event& e) = 0;

    private:
        std::string m_LayerName;

    };


}