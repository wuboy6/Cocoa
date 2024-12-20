#pragma once
#include <sstream>

#include "Event.h"


namespace Cocoa
{
	class COCOA_API KeyEvent :public Event
	{
	public:
		inline int GetKeyCode() const
		{
			return m_KeyCode;
		}
		
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyBoard)

	protected:
		KeyEvent(int keycode)
			:m_KeyCode(keycode){}

		int m_KeyCode;
	};

	class COCOA_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode,int repeatcount)
			:KeyEvent(keycode),m_RepeatCount(repeatcount) { }

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << "repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class COCOA_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	private:
		
	};

	class COCOA_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			:KeyEvent(keycode){}
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent:" << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)

	private:
		
	};
}