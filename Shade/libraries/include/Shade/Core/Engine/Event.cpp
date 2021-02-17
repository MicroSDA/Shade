#include "stdafx.h"
#include "Event.h"
//#include <SDL2/SDL.h>


void se::Event::operator=(const SDL_Event& event)
{
	m_Type = static_cast<se::Event::Type>(event.type);
	m_Window = static_cast<se::Event::Window>(event.window.event);
	m_Keyboard.ScanCode = static_cast<se::Event::Keyboard::SCode>(event.key.keysym.scancode);
	m_Mouse.Motion.x = event.motion.x;
	m_Mouse.Motion.y = event.motion.y;
	m_Mouse.Button.State = static_cast<se::Event::Mouse::Button::KState>(event.button.state);
	m_Mouse.Button.Code = static_cast<se::Event::Mouse::Button::KCode>(event.button.button);
	std::strncpy(m_Text.Text, event.text.text, sizeof(event.text.text));
}

se::Event::operator SDL_Event()
{
	/*SDL_Event event;
	event.type = static_cast<uint32_t>(this->GetType());
	event.window.event = static_cast<uint8_t>(this->GetWindow());
	event.key.keysym.scancode = static_cast<SDL_Scancode>(this->GetKeyboard().ScanCode);
	event.motion.x      = this->GetMouse().Motion.x;
	event.motion.y      = this->GetMouse().Motion.y;
	event.button.state  = static_cast<uint8_t>(this->GetMouse().Button.State);
	event.button.button = static_cast<uint8_t>(this->GetMouse().Button.Code);
	std::strncpy(event.text.text, m_Text.Text, sizeof(event.text.text));*/

	return this->m_SdlEvent;
}

void se::Event::SetType(const se::Event::Type& type)
{

	m_Type = type;
}

void se::Event::SetWindow(const se::Event::Window& window)
{
	m_Window = window;
}

void se::Event::SetKeyboard(const se::Event::Keyboard& keyboard)
{
	m_Keyboard = keyboard;
}

void se::Event::SetMouse(const se::Event::Mouse& mouse)
{
	m_Mouse = mouse;
}

void se::Event::SetText(const se::Event::Text& text)
{
	m_Text = text;
}

const se::Event::Type& se::Event::GetType() const
{
	return m_Type;
}

const se::Event::Window& se::Event::GetWindow() const
{
	return m_Window;
}

const se::Event::Keyboard& se::Event::GetKeyboard() const
{
	return m_Keyboard;
}

const se::Event::Mouse& se::Event::GetMouse() const
{
	return m_Mouse;
}

const se::Event::Text& se::Event::GetText() const
{
	return m_Text;
}
