#include "stdafx.h"
#include "ShadeEditor.h"
#include "Serializer.h"

ShadeEditor::ShadeEditor()
{
	
	
	Serializer _Serializer;
	_Serializer.SerializeShader({
		{"./project/resources/shaders/BasicModelVertex.glsl","#vertex"},
		{"./project/resources/shaders/BasicModelFragment.glsl","#fragment"} }, *new se::AssetData());

	/*se::AssetData _Packet;
	se::AssetData _Shaders;
	se::AssetData _Models;
	se::AssetData _Model;
	se::AssetData _Asset;

	_Packet._Name = "Assets";

	_Shaders._Name = "Shaders";
	_Shaders._Path = "./resources/shaders/shaders.bin";
	_Shaders._Offset = 0;

	_Asset._Name = "BasicModel";
	_Asset._Path = "./resources/shaders/shaders.bin";
	_Asset._Offset = 0;
	_Shaders._Dependency.push_back(_Asset);

	_Models._Name = "Models";
	_Models._Path = "./resources/models/";
	_Models._Offset = 0;

	_Model._Name = "Cube";
	_Model._Path = "./resources/models/";
	_Serializer.SerializeModel("./project/resources/models/cube.obj", _Model);
	_Models._Dependency.push_back(_Model);

	_Packet._Dependency.push_back(_Shaders);
	_Packet._Dependency.push_back(_Models);

	se::AssetManager::WriteRoadMap(_Packet); */

	//_Serializer.SerializeImage("./project/resources/images/CubeDiffuse.png");
	//_Serializer.SerializeModel("./project/resources/models/nanosuit.obj");
	/*_Serializer.SerializeShader({
		{"./project/resources/shaders/BasicModelVertex.glsl","#vertex"},
		{"./project/resources/shaders/BasicModelFragment.glsl","#fragment"}}, {});

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

