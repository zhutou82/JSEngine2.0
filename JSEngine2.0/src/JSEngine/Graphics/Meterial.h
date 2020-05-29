#pragma once
#include <vector>

#include "glm/glm.hpp"
#include "JSEngine/Core/Core.h"
#include "JSEngine/Graphics/Texture.h"
#include "JSEngine/Graphics/Shader.h"


namespace JSEngine
{
    class Material
    {
    public:

        Material(const Ref<Shader>& shader);

        float GetShinese() const               { return m_Shinese;  }
        void SetShinese(float val)             { m_Shinese = val;   }

        void AddTexture(const Ref<Texture>& texture) { m_TextureVec.push_back(texture); }
        const Ref<Shader>& GetShader() const { return m_Shader; }

        void Bind() const;

    public:
        static Ref<Material> Create(const Ref<Shader>& shader);

    private:

        float m_Shinese = 32.f;
        uint32_t m_ID;

        std::vector<Ref<Texture>> m_TextureVec;
        Ref<Shader> m_Shader;

    };

    
}
