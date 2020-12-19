#include <Shade/Shade.h>
#include <Scene/MainScene.h>

#include <string>
void Prepare();
void RoadMap();

int main()
{
	//RoadMap();
	

	se::EngineConfig conf;

	conf.window.Title = "Shade Editor";
	conf.window.WindowFlags = se::WindowFlags(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );
	conf.scene = new MainScene("MainScene");


	se::Engine::SetConfig(conf);

	Prepare();

	se::Engine::Init();
	
	//delete conf.scene;

	return 0;
}
void Prepare()
{
	se::Engine::RegisterEventCallback(se::EventType::SDL_WINDOWEVENT,
		[](se::Event const& event) {

			if (event.window.event == SDL_WINDOWEVENT_MINIMIZED)
			{
				if (se::Engine::GetState() != se::EngineState::PAUSE)
				{
					DEBUG_PRINT("SDL_WINDOWEVENT_MINIMIZED", se::LogLevel::EVENT);
					se::Engine::SetState(se::EngineState::PAUSE);
				}
			}

			if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
			{

				if (se::Engine::GetState() == se::EngineState::PAUSE)
				{
					DEBUG_PRINT("SDL_WINDOWEVENT_FOCUS_GAINED", se::LogLevel::EVENT);
					se::Engine::SetState(se::EngineState::RUNNING);
				}
			}

			return false;
		});

	se::Engine::RegisterEventCallback(se::EventType::SDL_QUIT,
		[](se::Event const& event) {

			DEBUG_PRINT("QUIT", se::LogLevel::EVENT);
			se::Engine::SetState(se::EngineState::STOP);
			return true;
		});
	se::Engine::RegisterEventCallback(se::EventType::SDL_KEYDOWN,
		[](se::Event const& event) {

			if (event.key.keysym.sym == se::KeyCode::SDLK_ESCAPE)
			{
				se::Engine::SetState(se::EngineState::STOP);
				DEBUG_PRINT("QUIT", se::LogLevel::EVENT);
				return true;
			}

			if (event.key.keysym.sym == se::KeyCode::SDLK_PAUSE)
			{
				if (se::Engine::GetState() != se::EngineState::PAUSE)
				{
					se::Engine::SetState(se::EngineState::PAUSE);
				}
				else
				{
					se::Engine::SetState(se::EngineState::RUNNING);
				}
			}

			return false;
		});
}


/*void* operator new(size_t size)
{
	std::cout << size << "\n";
	return malloc(size);

}

void operator delete(void* memory, size_t size)
{
	std::cout << size << "\n";
	free(memory);
}*/

void RoadMap()
{
	se::AssetData _Packet;
	se::AssetData _Asset;

	_Packet._Name = "Assets";
	//_Packet._Type = se::AssetDataType::Packet;
	
	_Asset._Name = "Shaders";
	//_Asset._Type = se::AssetDataType::Container;
	_Asset._Path = "shaders.bin";
	_Asset._Offset = 0;

	_Packet._Dependency.push_back(_Asset);

	_Asset._Name = "BasicModel";
	//_Asset._Type = se::AssetDataType::Shader;
	_Asset._Path = "shaders.bin";
	_Asset._Offset = 0;

	_Packet._Dependency[0]._Dependency.push_back(_Asset);

	_Asset._Name = "Models";
	//_Asset._Type = se::AssetDataType::Container;
	_Asset._Path = "models.bin";
	_Asset._Offset = 0;

	_Packet._Dependency.push_back(_Asset);

	_Asset._Name = "Cube";
	//_Asset._Type = se::AssetDataType::Model;
	_Asset._Path = "models.bin";
	_Asset._Offset = 0;

	_Packet._Dependency[1]._Dependency.push_back(_Asset);

	_Asset._Name = "Triangle";
	//_Asset._Type = se::AssetDataType::Model;
	_Asset._Path = "models.bin";
	_Asset._Offset = 540;

	_Packet._Dependency[1]._Dependency.push_back(_Asset);

	se::AssetManager::WriteRoadMap(_Packet);

}
