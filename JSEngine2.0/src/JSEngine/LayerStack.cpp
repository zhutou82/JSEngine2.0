#include "PCH.h"
#include "LayerStack.h"

namespace JSEngine
{
    LayerStack::LayerStack()
        : m_StackLayerInsertIndex(0)
    {
    }

    LayerStack::~LayerStack()
    {
        for (auto& elem : m_StackLayer)
            delete elem;
    }

    void LayerStack::PushLayer(Layer* layer)
    {
       m_StackLayer.emplace(m_StackLayer.begin() + m_StackLayerInsertIndex, layer);
       ++m_StackLayerInsertIndex;
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(m_StackLayer.begin(), m_StackLayer.end(), layer);
        if (it != m_StackLayer.end())
        {
            m_StackLayer.erase(it);
            --m_StackLayerInsertIndex;
        }
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        m_StackLayer.emplace_back(overlay);
    }

    void LayerStack::PopOverLayer(Layer* overlay)
    {
        auto it = std::find(m_StackLayer.begin(), m_StackLayer.end(), overlay);
        if (it != m_StackLayer.end())
            m_StackLayer.erase(it);
    }


}

