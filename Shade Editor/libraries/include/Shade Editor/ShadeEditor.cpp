#include "stdafx.h"
#include "ShadeEditor.h"

#include "Serrializer.h"

ShadeEditor::ShadeEditor()
{
	se::AssetData _Container;
	se::AssetData _ModelsPacket;
	se::AssetData _ShaderPacket;
	se::AssetData _Model;
	se::AssetData _Shader;

	/*_Container._Name = "Assets";

	_ModelsPacket._Name = "Models";
	_ShaderPacket._Name = "Shaders";

	_Model._Name = "Cube";
	_Model._Path = "./resources/models/cube/";
	TestSerrializer::Serrialize3DModel("./project/resources/models/cube/cube.obj", &_Model, true);
	_ModelsPacket._Dependency.push_back(_Model);

	_Model = se::AssetData{};
	_Model._Name = "Floor";
	_Model._Path = "./resources/models/floor/";
	TestSerrializer::Serrialize3DModel("./project/resources/models/floor/floor.obj", &_Model, true);
	_ModelsPacket._Dependency.push_back(_Model);*/


	/*_Shader._Name = "BasicModel";
	_Shader._Path = "./resources/shaders/";

	Serrializer::SerrializeShader({
		{"./project/resources/shaders/BasicModelVertex.glsl","#vertex"},
		{"./project/resources/shaders/BasicModelFragment.glsl","#fragment"}, }, &_Shader);*/

	/*_ShaderPacket._Dependency.push_back(_Shader);


	_Container._Dependency.push_back(_ShaderPacket);
	_Container._Dependency.push_back(_ModelsPacket);

	se::AssetManager::WriteRoadMap(_Container);*/

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

