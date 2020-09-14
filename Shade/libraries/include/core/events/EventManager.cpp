#include "EventManager.h"
se::EventManager::EventManager()
{
}

se::EventManager::~EventManager()
{
}

se::EventManager& se::EventManager::GetInstance()
{
	static EventManager _Instatnce;
	return _Instatnce;
}

inline void se::EventManager::OnEvent(const EventCategory& catagory, const std::function<bool()>& callBack)
{
	GetInstance()._OnEvent(catagory, callBack);
}

void se::EventManager::Update()
{
	GetInstance()._Update();
}

void se::EventManager::_OnEvent(const EventCategory& catagory, const std::function<bool()>& callBack)
{
	m_EventCallBacks[catagory].push_back(callBack);
}

void se::EventManager::_Update()
{
	
	while (SDL_PollEvent(&WindowManager::GetWindow().Event))
	{
		switch (WindowManager::GetWindow().Event.type)
		{
		case SDL_WINDOWEVENT:
			for (auto i = 0; i < m_EventCallBacks[EventCategory::WINDOW].size(); i++)
			{
				if (!m_EventCallBacks[EventCategory::WINDOW][i]())
				{
					m_EventCallBacks[EventCategory::WINDOW].erase(
						m_EventCallBacks[EventCategory::WINDOW].begin() + i);
				}
			}
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			for (auto i = 0; i < m_EventCallBacks[EventCategory::KEYBOARD].size(); i++)
			{
				if (!m_EventCallBacks[EventCategory::KEYBOARD][i]())
				{
					m_EventCallBacks[EventCategory::KEYBOARD].erase(
						m_EventCallBacks[EventCategory::KEYBOARD].begin() + i);
				}
			}
			break;
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			for (auto i = 0; i < m_EventCallBacks[EventCategory::MOUSE].size(); i++)
			{
				if (!m_EventCallBacks[EventCategory::MOUSE][i]())
				{
					m_EventCallBacks[EventCategory::MOUSE].erase(
						m_EventCallBacks[EventCategory::MOUSE].begin() + i);
				}
			}
			break;
		default:
			break;
		}

	}

	

}