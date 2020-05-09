#pragma once
#include "glm/glm.hpp"
#include "JSEngine/Core/Core.h"


namespace JSEngine
{
    class Meterial
    {
        static uint32_t s_UniqueID;

    public:

        Meterial(const glm::vec3& color    = { 1, 1, 1 }, 
                 const glm::vec3& ambient  = { 0.1f, 0.1f, 0.1f },
                 const glm::vec3& diffuse  = { 0.1f, 0.1f, 0.1f },
                 const glm::vec3& specular = { 0.1f, 0.1f, 0.1f },
                 float shinese = 32);

        const glm::vec3& GetColor() const      { return m_Color;    }
        void SetColor(const glm::vec3& val)    { m_Color = val;     }

        const glm::vec3& GetAmbient() const    { return m_Ambient;  }
        void SetAmbient(const glm::vec3& val)  { m_Ambient = val;   }

        const glm::vec3& GetSpecular() const   { return m_Specular; }
        void SetSpecular(const glm::vec3& val) { m_Specular = val;  }

        const glm::vec3& GetDiffuse() const    { return m_Diffuse;  }
        void SetDiffuse(const glm::vec3& val)  { m_Diffuse = val;   }

        float GetShinese() const               { return m_Shinese;  }
        void SetShinese(float val)             { m_Shinese = val;   }

        uint32_t GetID() const                 { return m_ID;       }

        static Ref<Meterial> Create();

    private:

        glm::vec3 m_Color;
        glm::vec3 m_Ambient;
        glm::vec3 m_Diffuse;
        glm::vec3 m_Specular;

        float m_Shinese;

        uint32_t m_ID;


    };

    
}
