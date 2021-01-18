#include "stdafx.h"
#include "ShadeEditor.h"

#include "Serrializer.h"

ShadeEditor::ShadeEditor()
{
	/*se::AssetData _Container;
	se::AssetData _ModelsPacket;
	se::AssetData _ShaderPacket;
	se::AssetData _SpritePacket;
	se::AssetData _Model;
	se::AssetData _Shader;
	se::AssetData _Sprite;


	_Container._Name = "";

	_ModelsPacket._Name = "Models";
	_ShaderPacket._Name = "Shaders";

	_Model._Name = "Cube";
	_Model._Path = "./resources/models/cube/";
	Serrializer::Serrialize3DModel("./project/resources/models/cube/cube.obj", &_Model, true);
	_ModelsPacket._Dependency.push_back(_Model);

	_Model = se::AssetData{}; // Reset
	_Model._Name = "Floor";
	_Model._Path = "./resources/models/floor/";
	Serrializer::Serrialize3DModel("./project/resources/models/floor/floor.obj", &_Model, true);
	_ModelsPacket._Dependency.push_back(_Model);


	_Model = se::AssetData{}; // Reset
	_Model._Name = "SamuraiHelmet";
	_Model._Path = "./resources/models/samurai-helmet/";
	Serrializer::Serrialize3DModel("./project/resources/models/samurai-helmet/samurai-helmet.obj", &_Model, true);
	_ModelsPacket._Dependency.push_back(_Model);

	_Model = se::AssetData{}; // Reset
	_Model._Name = "Skull";
	_Model._Path = "./resources/models/skull/";
	Serrializer::Serrialize3DModel("./project/resources/models/skull/skull.obj", &_Model, true);
	_ModelsPacket._Dependency.push_back(_Model);

/////////////////////////////////////
	_Shader._Name = "BasicModel";
	_Shader._Path = "./resources/shaders/";

	Serrializer::SerrializeShader({
		{"./project/resources/shaders/BasicModelVertex.glsl","#vertex"},
		{"./project/resources/shaders/BasicModelFragment.glsl","#fragment"}, }, &_Shader);
	_ShaderPacket._Dependency.push_back(_Shader);

	_Shader = se::AssetData{}; // Reset
	_Shader._Name = "Sprite";
	_Shader._Path = "./resources/shaders/";
	Serrializer::SerrializeShader({
		{"./project/resources/shaders/SpriteVertex.glsl","#vertex"},
		{"./project/resources/shaders/SpriteFragment.glsl","#fragment"}, }, &_Shader);
	_ShaderPacket._Dependency.push_back(_Shader);

	_Shader = se::AssetData{}; // Reset
	_Shader._Name = "Grid";
	_Shader._Path = "./resources/shaders/";
	Serrializer::SerrializeShader({
		{"./project/resources/shaders/GridVertex.glsl","#vertex"},
		{"./project/resources/shaders/GridFragment.glsl","#fragment"}, }, &_Shader);
	_ShaderPacket._Dependency.push_back(_Shader);


	
	_SpritePacket._Name = "Sprites";
	_SpritePacket._Path = "./resources/textures/";
	se::AssetData _Texture;

	_Texture._Name = "PoeImage";
	_Texture._Type = se::AssetDataType::Texture;
	_Texture._Path = "./resources/textures/image.bin"; // if serialize like that need to specify full path and name
	Serrializer::SerrializeTexture("./project/resources/images/image.png", &_Texture);

	_Sprite._Name = "PoeImage";
	_Sprite._Type = se::AssetDataType::Sprite;
	_Sprite._Dependency.push_back(_Texture);
	_SpritePacket._Dependency.push_back(_Sprite);

	_Sprite = se::AssetData{};
	_Sprite._Name = "PoeImage2";
	_Sprite._Type = se::AssetDataType::Sprite;
	_Sprite._Dependency.push_back(_Texture);

	_SpritePacket._Dependency.push_back(_Sprite);

	_Container._Dependency.push_back(_ShaderPacket);
	_Container._Dependency.push_back(_ModelsPacket);
	_Container._Dependency.push_back(_SpritePacket);

	se::AssetManager::WriteRoadMap(_Container);
	exit(0);*/

}

ShadeEditor::~ShadeEditor()
{

}

void ShadeEditor::OnInit()
{
	se::AssetManager::ReadRoadMap();

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

	SetCurentScene("MainScene");
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

