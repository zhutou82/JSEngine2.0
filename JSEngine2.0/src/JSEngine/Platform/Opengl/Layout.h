#pragma once
#include "JSEngine/Platform/Opengl/OpenGLContext.h"

namespace JSEngine
{
    struct Element
    {
        unsigned int Type;
        unsigned int Count;
        unsigned int Normalized;
        
        static unsigned int GetGLTypeSize(unsigned int type)
        {
            switch (type)
            {
                case GL_FLOAT:        return sizeof(float);
                case GL_UNSIGNED_INT: return sizeof(unsigned int);
                case GL_BYTE:         return sizeof(char);
            }

            JS_CORE_ASSERT(0, "Error Type");
            return 0;
        }
    };

    class Layout
    {
    public:
        Layout() : m_Stride(0) {};
        ~Layout() {};
        const std::vector<Element>& GetElementVec() const { return m_ElementVec; }
        unsigned int GetStride() const { return m_Stride; }

        template <typename T>
        void Push(unsigned int count)
        {
            static_assert(false);
        }

        template <>
        void Push<float>(unsigned int count)
        {
            m_ElementVec.push_back({ GL_FLOAT, count, GL_FALSE });
            m_Stride += count * Element::GetGLTypeSize(m_ElementVec.back().Type);
        }

        template <>
        void Push<unsigned int>(unsigned int count)
        {
            m_ElementVec.push_back({GL_UNSIGNED_INT, count, GL_FALSE });
            m_Stride += count * Element::GetGLTypeSize(m_ElementVec.back().Type);
        }

        template <>
        void Push<char>(unsigned int count)
        {
            m_ElementVec.push_back({ GL_BYTE, count, GL_FALSE });
            m_Stride += count * Element::GetGLTypeSize(m_ElementVec.back().Type);
        }

    private:

        std::vector<Element> m_ElementVec; 
        unsigned int         m_Stride;

    };
}