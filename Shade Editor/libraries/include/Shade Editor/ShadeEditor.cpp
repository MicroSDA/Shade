#include "stdafx.h"
#include "ShadeEditor.h"
#include "Serializer.h"

ShadeEditor::ShadeEditor()
{
	
	/*Serializer _Serializer;
	_Serializer.SerializeModel("./project/resources/models/cube.obj");
	_Serializer.SerializeShader({
		{"./project/resources/shaders/BasicModelVertex.glsl","#vertex"},
		{"./project/resources/shaders/BasicModelFragment.glsl","#fragment"}}, {});

	se::AssetData _Packet;
	se::AssetData _Asset;

	_Packet._Name = "Assets";
	//_Packet._Type = se::AssetDataType::Packet;

	_Asset._Name = "Shaders";
	//_Asset._Type = se::AssetDataType::Container;
	_Asset._Path = "./resources/shaders/shaders.bin";
	_Asset._Offset = 0;

	_Packet._Dependency.push_back(_Asset);

	_Asset._Name = "BasicModel";
	//_Asset._Type = se::AssetDataType::Shader;
	_Asset._Path = "./resources/shaders/shaders.bin";
	_Asset._Offset = 0;

	_Packet._Dependency[0]._Dependency.push_back(_Asset);

	_Asset._Name = "Models";
	//_Asset._Type = se::AssetDataType::Container;
	_Asset._Path = "./resources/models/";
	_Asset._Offset = 0;

	_Packet._Dependency.push_back(_Asset);

	_Asset._Name = "Cube";
	//_Asset._Type = se::AssetDataType::Model;
	_Asset._Path = "./resources/models/cube.bin";
	_Asset._Offset = 0;

	_Packet._Dependency[1]._Dependency.push_back(_Asset);

	se::AssetManager::WriteRoadMap(_Packet);*/

}

ShadeEditor::~ShadeEditor()
{
}

void ShadeEditor::OnInit()
{
	//Events call back an other stuff 

	se::WindowManager::Create(se::Window{});
	se::EventManager::RegAppEventCallback(se::EventType::SDL_WINDOWEVENT,
		[](se::Event const& event) {

			if (event.window.event == SDL_WINDOWEVENT_MINIMIZED)
			{
				SE_DEBUG_PRINT("WINDOWEVENT_MINIMIZED", se::SLCode::Event);
			}

			if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
			{
				SE_DEBUG_PRINT("WINDOWEVENT_FOCUS_GAINED", se::SLCode::Event);
			}

			return false;
		});
	se::EventManager::RegAppEventCallback(se::EventType::SDL_QUIT,
		[](se::Event const& event) {

			se::WindowManager::DestroyWindow();
			exit(0);
			return true;
		});
	se::EventManager::RegAppEventCallback(se::EventType::SDL_KEYDOWN,
		[](se::Event const& event) {

			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				SE_DEBUG_PRINT("SDLK_ESCAPE", se::SLCode::Event);
				se::WindowManager::DestroyWindow();
				exit(0);
				return true;
			}

			return false;
		
		});

	CreateScene<MainScene>("MainScene");

	//? or more
	
	for (auto const& [name, scene] : GetScenes())
	{
		InitScene(name);
	}

	SetActiveScene("MainScene");
	//DeleteScene("MainScene");
}

void ShadeEditor::OnUpdate()
{
	return;
}

se::Application* se::CreateApplication()
{
	return new ShadeEditor();
}

