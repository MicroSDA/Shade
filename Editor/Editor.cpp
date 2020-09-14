#include <core/engine/Engine.h>

class MainScene :public se::Scene
{
public:
	MainScene(){}
	~MainScene(){}
	void OnCreate() const override 
	{
		
		se::EventManager::OnEvent(se::EventCategory::KEYBOARD,
			[this]{
				if (se::WindowManager::GetWindow().Event.type == SDL_KEYDOWN &&
					se::WindowManager::GetWindow().Event.key.keysym.sym == SDLK_ESCAPE) // Not work
				{
					m_State = se::SceneState::Exit;
				}
				return true;
			});

		
		DEBUG_LOG("OnCreate scene: " + m_Name, se::LOG_LEVEL::INFO_PRIMARY);
	}
	se::SceneState OnUpdate() const override
	{ 
		
		DEBUG_LOG("OnUpdate scene: " + m_Name, se::LOG_LEVEL::INFO_SECONDARY);
		return m_State;
	}
	void OnRender() const override
	{
		DEBUG_LOG("OnREnder scene: " + m_Name, se::LOG_LEVEL::INFO_SECONDARY);
	}
	void OnPause()  const override
	{
		DEBUG_LOG("OnPause scene: " + m_Name, se::LOG_LEVEL::INFO_PRIMARY);
	}
	void OnResume() const override
	{
		DEBUG_LOG("OnResume scene: " + m_Name, se::LOG_LEVEL::INFO_PRIMARY);
	}
	void OnDelete() const override 
	{
		DEBUG_LOG("OnDelete scene: " + m_Name, se::LOG_LEVEL::INFO_PRIMARY);
	}
private:

};

int main()
{
	
	se::Engine::AddScene(new MainScene());
	se::Engine::Start();

	return 0;
}