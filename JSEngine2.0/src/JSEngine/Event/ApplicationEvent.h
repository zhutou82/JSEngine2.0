#pragma once
#include "JSEngine/Event/Event.h"

namespace JSEngine
{
    class JSENGINE_API WindowReSizeEvent : public Event
    {
    public:
        WindowReSizeEvent(unsigned width, unsigned height)
            : m_Width(width), m_Height(height)
        {}

        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowReSize: (" << m_Width << ", " << m_Height << " )";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WINDOW_RESIZE)
        EVENT_CATEGORY_TYPE(INPUT | APP)

    private:
        unsigned int m_Width;
        unsigned int m_Height;
    };

    class JSENGINE_API WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WINDOW_CLOSE)
        EVENT_CATEGORY_TYPE(APP)

    };
    class JSENGINE_API WindowFocusEvent : public Event
    {
    public:
        WindowFocusEvent(int width, int height)
            : m_Width(width), m_Height(height)
        {}

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowFocusEvent: (" << m_Width << ", " << m_Height << " )";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WINDOW_FOCUS)
        EVENT_CATEGORY_TYPE(APP)

    private:
        int m_Width;
        int m_Height;
    };

    class JSENGINE_API WindowLostFocusEvent : public Event
    {
    public:
        WindowLostFocusEvent(int width, int height)
            : m_Width(width), m_Height(height)
        {}

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowFocusEvent: (" << m_Width << ", " << m_Height << " )";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WINDOW_LOST_FOCUS)
        EVENT_CATEGORY_TYPE(APP)

    private:
        int m_Width;
        int m_Height;
    };

    class JSENGINE_API WindowMoveEvent : public Event
    {
    public:
        WindowMoveEvent(int xCoor, int yCoor)
            : m_Xcoor(xCoor), m_Ycoor(yCoor)
        {}

        int GetWidth() const { return m_Xcoor; }
        int GetHeight() const { return m_Ycoor; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowMoveEvent: (" << m_Xcoor << ", " << m_Ycoor << " )";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WINDOW_MOVED)
        EVENT_CATEGORY_TYPE(APP)

    private:
        int m_Xcoor;
        int m_Ycoor;
    };

    class JSENGINE_API AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(APP_TICK)
        EVENT_CATEGORY_TYPE(APP)
    };

    class JSENGINE_API AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(APP_UPDATE)
        EVENT_CATEGORY_TYPE(APP)
    };
    class JSENGINE_API AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(APP_RENDER)
        EVENT_CATEGORY_TYPE(APP)
    };
}