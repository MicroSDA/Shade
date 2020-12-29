#include "stdafx.h"
#include "ShadeEditor.h"
#include "Serializer.h"

ShadeEditor::ShadeEditor()
{
	
	Serializer _Serializer;
	//_Serializer.SerializeImage("./project/resources/images/CubeDiffuse.png");
	//_Serializer.SerializeModel("./project/resources/models/cube.obj");
	_Serializer.SerializeShader({
		{"./project/resources/shaders/BasicModelVertex.glsl","#vertex"},
		{"./project/resources/shaders/BasicModelFragment.glsl","#fragment"}}, {});

	/*se::AssetData _Packet;
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

	se::AssetData _Iamge;
	_Iamge._Name = "Image";
	_Iamge._Path = "./resources/textures/CubeDiffuse.bin";

	_Asset._Dependency.push_back(_Iamge);
	_Packet._Dependency[1]._Dependency.push_back(_Asset);

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

