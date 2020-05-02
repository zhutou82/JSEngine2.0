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
      
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;


    };

    class Texture2D : public Texture
    {

    public:


        static Ref<Texture2D> Create(const std::string& fileName);
    };


}
