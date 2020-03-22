#pragma once
#include "JSEngine/Event/Event.h"
namespace JSEngine
{
    class JSENGINE_API MouseButtonEvent : public Event
    {
    public:
        MouseButtonEvent(int mouseButton) :
            m_MouseButton(mouseButton)
        {}
        int GetMouseButton() const { return m_MouseButton; }
        EVENT_CATEGORY_TYPE( INPUT | MOUSE_BUTTON)

    protected:
        int m_MouseButton;
    };

    class JSENGINE_API MouseButtonPressEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressEvent(int mouseButton) 
            : MouseButtonEvent(mouseButton)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPress: " << m_MouseButton;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED)
    };

    class JSENGINE_API MouseButtonReleaseEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleaseEvent(int mouseButton)
            : MouseButtonEvent(mouseButton)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonRelease: " << m_MouseButton;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED)
    };

    class JSENGINE_API MouseMoveEvent : public Event
    {
    public:
        MouseMoveEvent(float xCoor, float yCoor) : 
            m_Xcoor(xCoor), m_Ycoor(yCoor)
        {}
        int GetMouseXCoordinate() const { return m_Xcoor; }
        int GetMouseYCoordinate() const { return m_Ycoor; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMoved: (" << m_Xcoor << ", " << m_Ycoor << ")";
            return ss.str();
        }

        EVENT_CATEGORY_TYPE(INPUT | MOUSE)
        EVENT_CLASS_TYPE(MOUSE_MOVE)

    private:
        float m_Xcoor;
        float m_Ycoor;
    };

    class JSENGINE_API MouseScrollEvent : public Event
    {
    public:
        MouseScrollEvent(double xOffset, double yOffet) :
            m_Xoffet(xOffset), m_Yoffet(yOffet)
        {}
        int GetMouseXOffSet() const { return m_Xoffet; }
        int GetMouseYOffSet() const { return m_Yoffet; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMoved: (" << m_Xoffet << ", " << m_Yoffet << ")";
            return ss.str();
        }

        EVENT_CATEGORY_TYPE(INPUT | MOUSE)
        EVENT_CLASS_TYPE(MOUSE_SCROLLED)

    private:
        double m_Xoffet;
        double m_Yoffet;
    };
}