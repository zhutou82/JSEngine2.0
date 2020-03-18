#pragma once
#include "JSEngine/Core.h"

#include <string>
#include <functional>
#include <sstream>
namespace JSEngine
{
    // Currently a blocking Event
    // Meaning that event will be dealt with immediately

    enum class EventType
    {
        //windows 
        NONE = 0,
        WINDOW_CLOSE,
        WINDOW_RESIZE,
        WINDOW_FOCUS,
        WINDOW_LOST_FOCUS,
        WINDOW_MOVED,
        //app
        APP_TICK,
        APP_UPDATE,
        APP_RENDER,
        //key board
        KEY_PRESSED,
        KEY_RELEASE,
        //mouse
        MOUSE_BUTTON_PRESSED,
        MOUSE_BUTTON_RELEASED,
        MOUSE_MOVE,
        MOUSE_SCROLLED
    };
    //used bit fill to cater certain event that fall into multiple categories
    enum EventCategory
    {
        NONE = 0,
        APP             = BIT(0),
        INPUT           = BIT(1),  
        KEYBOARD        = BIT(2),
        MOUSE           = BIT(3),
        MOUSE_BUTTON    = BIT(4) 
    };


#define EVENT_CLASS_TYPE(type)                                            \
virtual const char* GetName() const override { return #type ; }           \
static EventType GetStaticEventType () {return EventType::##type; } \
virtual EventType GetEventType() const override {return GetStaticEventType(); }


#define EVENT_CATEGORY_TYPE(cat)                                          \
virtual int GetCategoryFlag() const override { return cat; } 

    class JSENGINE_API Event
    {
        friend class EventDispatcher;
    public:
        virtual EventType GetEventType() const = 0;
        virtual int GetCategoryFlag() const = 0;
        virtual const char* GetName() const = 0;
        virtual std::string ToString() const { return GetName(); }
        bool IsInCategory(EventCategory cat) { return GetCategoryFlag() & cat; }

    protected:
        bool m_Handled = false;

    };

    class EventDispatcher
    {
        template <typename T>
        using EventFn = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& e) :
            m_Event(e)
        {}
        template <typename T>
        bool Dispatch(EventFn<T>& fn)
        {
            if (m_Event.GetEventType() == T::GetStaticEventType())
            {
                m_Event.m_Handled = fn(*dynamic_cast<T*>(&m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;

    };

}
