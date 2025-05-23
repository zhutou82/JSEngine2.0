#pragma once
#include "Core.h"
#include "Layer.h"
#include <vector>

namespace JSEngine
{
    //template class JSENGINE_API std::allocator<Layer*>;
    //template class JSENGINE_API std::vector<Layer*, std::allocator<Layer*> >;

    class JSENGINE_API LayerStack 
    {
    public:

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
        uint32_t m_StackLayerInsertIndex;

    };

}

