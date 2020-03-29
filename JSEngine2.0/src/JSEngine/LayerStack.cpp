#include "LayerStack.h"
#include <algorithm>

namespace JSEngine
{
    LayerStack::LayerStack()
    {
        m_StackLayerInsert = m_StackLayer.begin();
    }

    LayerStack::~LayerStack()
    {
        for (auto& elem : m_StackLayer)
            delete elem;
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_StackLayerInsert = m_StackLayer.emplace(m_StackLayerInsert, layer);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(m_StackLayer.begin(), m_StackLayer.end(), layer);
        if (it != m_StackLayer.end())
        {
            m_StackLayer.erase(it);
            --m_StackLayerInsert;
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

