#include "MainLayer.h"

MainLayer::MainLayer(const std::string& name, const void* scene)
	:se::Layer(name, scene)
{
}

MainLayer::~MainLayer()
{
}

void MainLayer::OnCreate()
{
	DEBUG_PRINT("OnLayer Create", se::LogLevel::INFO_PRIMARY);

}
void MainLayer::OnInit()
{
	DEBUG_PRINT("OnLayer Init", se::LogLevel::INFO_PRIMARY);

	RegisterEventCallback(se::EventType::SDL_KEYDOWN,
		[](se::Event const& event) {

			if (event.key.keysym.sym == se::KeyCode::SDLK_BACKSPACE)
			{

				DEBUG_PRINT("LayerEvent SDLK_BACKSPACE", se::LogLevel::EVENT);


			}

			return false;
		});
}

void MainLayer::OnRender() 
{
	

	se::Render::SetClearColor({ 0.5444f, 0.62f, 0.69f, 1.0f });
	//se::Render::SetClearColor({ glm::sin(m_Value),  glm::cos(m_Value),  glm::tan(m_Value), 1.0f });
	se::Render::Clear();


	//se::Render::DrawIndexed(new se::Drawable());
}

void MainLayer::OnUpdate() 
{
	//DEBUG_PRINT("OnLayer Update", se::LogLevel::INFO_PRIMARY);
}

void MainLayer::OnDelete()
{
	DEBUG_PRINT("OnLayer Delete", se::LogLevel::INFO_PRIMARY);
}
