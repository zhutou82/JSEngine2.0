#pragma once
#include "Event/Event.h"

namespace JSEngine
{
    class JSENGINE_API KeyEvent : public Event
    {

    public:
        int GetKeyCode() const { return m_KeyCode; }
        EVENT_CATEGORY_TYPE(KEYBOARD | INPUT)

    protected: 
        KeyEvent(int keyCode)
            : m_KeyCode(keyCode)
        {}  
        int m_KeyCode;

    };

    class JSENGINE_API KeyPressEvent : public KeyEvent
    {
    public:

        KeyPressEvent(int keycode, int repeatCount) : 
            KeyEvent(keycode), m_RepeatCount(repeatCount) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressEvent: " << m_KeyCode << " ( " << m_RepeatCount << ") ";
            return ss.str();
        }

        int GetRepeatCount() const { return m_RepeatCount; }

        EVENT_CLASS_TYPE(KEY_PRESSED)
    private:
        int m_RepeatCount;
    };

    class JSENGINE_API KeyReleseEvent : public KeyEvent
    {
    public:
        KeyReleseEvent(int keycode) :
            KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleseEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KEY_RELEASE)

    };

}