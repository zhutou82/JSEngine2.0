#pragma once
#include "glm/glm.hpp"
#include <vector>
#include "Texture.h"


namespace JSEngine
{
    class SubTexture2D
    {

    public:

        SubTexture2D(const Ref<Texture>& texture, const std::vector<glm::vec2>& coord);
        const std::vector<glm::vec2>& GetTextureCoord() const { return m_TextureCoord; }
        uint32_t GetTextureID() const { return m_Texture->GetTextureID(); }

        static Ref<SubTexture2D> Create(const Ref<Texture>& texture, const glm::ivec2& dim, const glm::ivec4& indexWithUnit);

    private:

        std::vector<glm::vec2> m_TextureCoord;
        Ref<Texture> m_Texture;

    };



}