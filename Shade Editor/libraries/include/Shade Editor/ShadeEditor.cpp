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

	_Shader = se::AssetData{}; // Reset
	_Shader._Name = "Text";
	_Shader._Path = "./resources/shaders/";
	Serrializer::SerrializeShader({
		{"./project/resources/shaders/TextVertex.glsl","#vertex"},
		{"./project/resources/shaders/TextFragment.glsl","#fragment"}, }, &_Shader);
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

	_Texture._Name = "Font";
	_Texture._Type = se::AssetDataType::Texture;
	_Texture._Path = "./resources/textures/font.bin"; // if serialize like that need to specify full path and name
	Serrializer::SerrializeTexture("./project/resources/fonts/candara/candara.png", &_Texture);*/

	se::AssetData _Font;
	_Font._Name = "FontFile";
	_Font._Type = se::AssetDataType::Font;
	_Font._Path = "./resources/fonts/candara/candara.bin"; // if serialize like that need to specify full path and name
	Serrializer::SerrializeFont("./project/resources/fonts/candara/candara.fnt", &_Font);

	/*_Container._Dependency.push_back(_ShaderPacket);
	_Container._Dependency.push_back(_ModelsPacket);
	_Container._Dependency.push_back(_SpritePacket);
	_Container._Dependency.push_back(_Texture);
	_Container._Dependency.push_back(_Font);

	se::AssetManager::WriteRoadMap(_Container);
	exit(0);*/

}

ShadeEditor::~ShadeEditor()
{

}

void ShadeEditor::OnInit()
{
	se::AssetManager::ReadRoadMap();
	se::System::InitVideo(se::RenderAPI::OpenGL, 4, 5);
	se::WindowManager::Create(se::Window());

	auto scene = CreateScene<MainScene>("MainScene");

	for (auto const& [name, scene] : GetScenes())
	{
		InitScene(name);
	}

	SetCurentScene("MainScene");

	auto grid = this->CreateEntity("Grid");
	grid.AddComponent<se::Transform3DComponent>();
	grid.AddComponent<se::DrawableComponent>(se::ShadeShared<se::Drawable>(new se::Grid(500, 500, 500)));

	this->CreateEntity("SceneViewPort").AddComponent<glm::vec2>();
	auto camera = this->CreateEntity("EditorCamera");
	auto camera_copm = camera.AddComponent<se::CameraComponent>(new se::Camera(glm::vec3(0.0f, 5.0f, 0.0f), 45.0f, 1.0f, 0.01f, 3000.0f));
	camera.AddComponent<se::NativeScriptComponent>().Bind<se::FreeCameraController>();
	scene->SetActiveCamera(camera_copm.Camera);
}

void ShadeEditor::OnUpdate(const se::Timer& deltaTime)
{
	return;
}

void ShadeEditor::OnEvent(const se::Event& event)
{

	if (event.GetType() == se::Event::Type::Quit)
		this->Quit();

	if (event.GetType() == se::Event::Type::Window)
	{
		if (event.GetWindow() == se::Event::Window::Resized)
		{
			se::WindowManager::Resize();
		}
	}
}

se::Application* se::CreateApplication()
{
	return new ShadeEditor();
}

