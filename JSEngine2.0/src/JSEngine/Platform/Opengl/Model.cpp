#include "PCH.h"
#include "Model.h"

namespace JSEngine
{
    Model::Model() :
        m_Vertex 
        {
            -0.5f, -0.5f, 0.f, 1.f,  1.f,  0.f, 0.f, 1.f,
             0.5f, -0.5f, 0.f, 1.f,  0.f,  1.f, 0.f, 1.f,
             0.5f,  0.5f, 0.f, 1.f,  0.f,  0.f, 1.f, 1.f,
            -0.5f , 0.5f, 0.f, 1.f,  0.5f , 0.5f, 0.f, 1.f,
        }
    {
        
    }


}