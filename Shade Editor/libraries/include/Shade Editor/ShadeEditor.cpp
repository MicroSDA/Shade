#include "stdafx.h"
#include "ShadeEditor.h"
#include "Serializer.h"

ShadeEditor::ShadeEditor()
{
	
	Serializer _Serializer;
	//_Serializer.SerializeImage("./project/resources/images/CubeDiffuse.png");
	//_Serializer.SerializeModel("./project/resources/models/nanosuit.obj");
	_Serializer.SerializeShader({
		{"./project/resources/shaders/BasicModelVertex.glsl","#vertex"},
		{"./project/resources/shaders/BasicModelFragment.glsl","#fragment"}}, {});

	/*se::AssetData _Packet;
	se::AssetData _Shaders;
	se::AssetData _Models;
	se::AssetData _Asset;

	_Packet._Name = "Assets";

	_Shaders._Name = "Shaders";
	_Shaders._Path = "./resources/shaders/shaders.bin";
	_Shaders._Offset = 0;

	_Asset._Name = "BasicModel";
	_Asset._Path = "./resources/shaders/shaders.bin";
	_Asset._Offset = 0;
	_Shaders._Dependency.push_back(_Asset);

	//_Packet._Dependency.push_back(_Shaders);
///////////////////////////////////////////////////
	_Models._Name = "Models";
	_Models._Path = "./resources/models/";
	_Models._Offset = 0;

	_Asset._Name = "Cube";
	_Asset._Path = "./resources/models/cube.bin";
	_Asset._Offset = 0;
		se::AssetData _Image;
		_Image._Name = "Image";
		_Image._Path = "./resources/textures/CubeDiffuse.bin";
	_Asset._Dependency.push_back(_Image);
	_Models._Dependency.push_back(_Asset);

	_Asset._Name = "Nanosuit";
	_Asset._Path = "./resources/models/nanosuit.bin";
	_Asset._Offset = 0;
	_Models._Dependency.push_back(_Asset);
	///////////////
	_Packet._Dependency.push_back(_Shaders);
	_Packet._Dependency.push_back(_Models);

	se::AssetManager::WriteRoadMap(_Packet);*/

}

ShadeEditor::~ShadeEditor()
{
}

void ShadeEditor::OnInit()
{
	//Events call back an other stuff 
	se::EventManager::RegAppEventCallback(se::EventType::SDL_QUIT,
		[&](se::Event const& event) {
			this->Quit();
			return true;
		});
	se::EventManager::RegAppEventCallback(se::EventType::SDL_KEYDOWN,
		[&](se::Event const& event) {
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				this->Quit();
				return true;
			}
			return false;
		});

	se::WindowManager::Create(se::Window{});
	CreateScene<MainScene>("MainScene");

	//? or more
	
	for (auto const& [name, scene] : GetScenes())
	{
		InitScene(name);
	}

	SetActiveScene("MainScene");
	//DeleteScene("MainScene");
}

void ShadeEditor::OnUpdate(const se::Timer& deltaTime)
{
	return;
}

se::Application* se::CreateApplication()
{
	return new ShadeEditor();
}

