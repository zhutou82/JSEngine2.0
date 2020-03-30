#pragma once
#include "Core.h"
#include "Layer.h"
#include "SingletonBaseClass.h"
#include <vector>

namespace JSEngine
{
    class JSENGINE_API LayerStack : public Singleton<LayerStack>
    {
    public:
        friend class Singleton <LayerStack>;

        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

        void PushOverlay(Layer* overlay);
        void PopOverLayer(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_StackLayer.begin(); }
        std::vector<Layer*>::iterator end() { return m_StackLayer.end(); }

    private:

        std::vector<Layer*> m_StackLayer;
        std::vector<Layer*>::iterator m_StackLayerInsert;

    };

}

