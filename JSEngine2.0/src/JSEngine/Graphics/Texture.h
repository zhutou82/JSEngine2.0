#pragma once
#include <string>
#include "JSEngine/Core/Core.h"
#include "glm/glm.hpp"

namespace JSEngine
{
    enum TextureType
    {
        DIFFUSE,
        SPECULAR,
        MAX_NUM_TEXTURE_TYPE
    };


    class Texture
    {
    public:

        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual const glm::ivec2& GetDimension() const = 0;
        virtual void SetDimension(const glm::ivec2& dimension) = 0;
        virtual const glm::vec2* GetSubTextureCoord(const glm::ivec2& index ) const = 0;
      
        virtual void Bind(uint32_t slot = 0) const = 0;
        virtual void UnBind() const = 0;

        virtual uint32_t GetTextureID() const = 0;
        virtual bool Equals(const Texture& rhs) = 0;

        virtual TextureType GetTextureType() const = 0;
        virtual void SetTextureType(TextureType typ) = 0;

        virtual const std::string& GetTextureName() const = 0;

        static std::string GetTextureNameByType(TextureType);

    };

    class Texture2D : public Texture
    {

    public:

        static Ref<Texture2D> Create(const std::string& fileName, const glm::ivec2& dim = { 1, 1 });


    };


}
