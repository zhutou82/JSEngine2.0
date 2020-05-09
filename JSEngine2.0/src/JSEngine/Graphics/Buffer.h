#pragma once
#include <memory>
#include "JSEngine/Core/Log.h"
#include "JSEngine/Core/Core.h"

namespace JSEngine
{
    
    enum class ElementType
    {
        FLOAT, VEC2, VEC3, VEC4,

    };

    static uint32_t GetCountByElementType(ElementType type)
    {
        switch (type)
        {
            case JSEngine::ElementType::FLOAT: return 1;
            case JSEngine::ElementType::VEC2:  return 2;
            case JSEngine::ElementType::VEC3:  return 3;
            case JSEngine::ElementType::VEC4:  return 4;

        }
        JS_CORE_ASSERT(false, "Unknow type")
        return 0;
    }

    static uint32_t GetSizeByElementType(ElementType type)
    {
        switch (type)
        {
            case JSEngine::ElementType::FLOAT: return 4;
            case JSEngine::ElementType::VEC2:  return 4 * 2;
            case JSEngine::ElementType::VEC3:  return 4 * 3;
            case JSEngine::ElementType::VEC4:  return 4 * 4;


        }
        JS_CORE_ASSERT(false, "Unknow type")
            return 0;
    }

    struct Element
    {
        Element(ElementType type, uint32_t location, const std::string& name, bool normalized = false) :
            Type(type), Location(location), Name(name), Normalized(normalized), Offset(0), Size(GetSizeByElementType(type))
        {
            Count = GetCountByElementType(type);
        }
        ElementType Type;
        uint32_t Count;
        bool Normalized;
        std::string Name;
        uint32_t Location;
        size_t Offset;
        uint32_t Size;
    };


    class Layout
    {
    public:
        Layout() {}
        Layout(const std::initializer_list<Element>& list) :
            m_ElementVec(list), m_Stride(0)
        {
            CalculateOffsetsAndStride();
        }

        ~Layout() {};

        const std::vector<Element>& GetElementVec() const { return m_ElementVec; }
        uint32_t GetStride()                        const { return m_Stride; }


        std::vector<Element>::iterator begin() { return m_ElementVec.begin(); }
        std::vector<Element>::iterator end() { return m_ElementVec.end(); }
        std::vector<Element>::const_iterator begin() const { return m_ElementVec.begin(); }
        std::vector<Element>::const_iterator end() const { return m_ElementVec.end(); }

    private:
        void CalculateOffsetsAndStride()
        {
            size_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_ElementVec)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }
    private:

        uint32_t m_Stride;
        std::vector<Element> m_ElementVec;

    };

    class VertexBuffer
    {

    public:
        
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void SetData(const void* data, uint32_t size) = 0;
        virtual const Layout& GetLayout() const = 0;
        virtual void SetLayout(const Layout& layout) = 0;

        static Ref<VertexBuffer> Create(const void* data, uint32_t size);
        static Ref<VertexBuffer> Create(uint32_t size);

       
    };

    class IndexBuffer
    {

    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static Ref<IndexBuffer> Create(const uint32_t * data, uint32_t count);
    };


}