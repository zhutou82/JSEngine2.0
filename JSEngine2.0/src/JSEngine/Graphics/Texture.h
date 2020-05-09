#pragma once
#include <string>
#include "JSEngine/Core/Core.h"

namespace JSEngine
{

    class Texture
    {
    public:

        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
      
        virtual void Bind(uint32_t slot = 0) const = 0;
        virtual void UnBind() const = 0;

        virtual uint32_t GetTextureID() const = 0;
        virtual bool Equals(const Texture& rhs) = 0;
    };

    class Texture2D : public Texture
    {

    public:

        static Ref<Texture2D> Create(const std::string& fileName);


    };


}
