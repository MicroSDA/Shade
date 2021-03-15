#include "stdafx.h"
#include "ShadeEditor.h"
#include "Serrializer.h"
//#include "Shade/Core/Engine/Collider.h"

ShadeEditor::ShadeEditor()
{
	se::AssetData _Container;
	se::AssetData _ModelsPacket;
	/*se::AssetData _ShaderPacket;
	se::AssetData _SpritePacket;*/
	se::AssetData _Model;
	/*se::AssetData _Shader;
	se::AssetData _Sprite;*/


	_Container.ID = "";

	_ModelsPacket.ID = "Models";
	//_ShaderPacket.ID = "Shaders";

	//_Model.ID = "Cube";
	//_Model.Path = "./resources/models/cube/";
	//Serrializer::Serrialize3DModel("./project/resources/models/cube/cube.obj", &_Model, true);
	//_ModelsPacket.Childs.push_back(_Model);
	//_Container.Childs.push_back(_ModelsPacket);
	/*_Model = se::AssetData{}; // Reset
	_Model.ID = "Floor";
	_Model.Path = "./resources/models/floor/";
	Serrializer::Serrialize3DModel("./project/resources/models/floor/floor.obj", &_Model, true);
	_ModelsPacket.Childs.push_back(_Model);*/


	/*_Model = se::AssetData{}; // Reset
	_Model.ID = "SamuraiHelmet";
	_Model.Path = "./resources/models/samurai-helmet/";
	Serrializer::Serrialize3DModel("./project/resources/models/samurai-helmet/samurai-helmet.obj", &_Model, true);
	_ModelsPacket.Childs.push_back(_Model);*/

	/*_Model = se::AssetData{}; // Reset
	_Model.ID = "Skull";
	_Model.Path = "./resources/models/skull/";
	Serrializer::Serrialize3DModel("./project/resources/models/skull/skull.obj", &_Model, true);
	_ModelsPacket.Childs.push_back(_Model);

/////////////////////////////////////
	_Shader.ID = "BasicModel";
	_Shader.Path = "./resources/shaders/";

	Serrializer::SerrializeShader({
		{"./project/resources/shaders/BasicModelVertex.glsl","#vertex"},
		{"./project/resources/shaders/BasicModelFragment.glsl","#fragment"}, }, &_Shader);
	_ShaderPacket.Childs.push_back(_Shader);

	_Shader = se::AssetData{}; // Reset
	_Shader.ID = "Sprite";
	_Shader.Path = "./resources/shaders/";
	Serrializer::SerrializeShader({
		{"./project/resources/shaders/SpriteVertex.glsl","#vertex"},
		{"./project/resources/shaders/SpriteFragment.glsl","#fragment"}, }, &_Shader);
	_ShaderPacket.Childs.push_back(_Shader);

	_Shader = se::AssetData{}; // Reset
	_Shader.ID = "Grid";
	_Shader.Path = "./resources/shaders/";
	Serrializer::SerrializeShader({
		{"./project/resources/shaders/GridVertex.glsl","#vertex"},
		{"./project/resources/shaders/GridFragment.glsl","#fragment"}, }, &_Shader);
	_ShaderPacket.Childs.push_back(_Shader);

	_Shader = se::AssetData{}; // Reset
	_Shader.ID = "Text";
	_Shader.Path = "./resources/shaders/";
	Serrializer::SerrializeShader({
		{"./project/resources/shaders/TextVertex.glsl","#vertex"},
		{"./project/resources/shaders/TextFragment.glsl","#fragment"}, }, &_Shader);
	_ShaderPacket.Childs.push_back(_Shader);


	
	_SpritePacket.ID = "Sprites";
	_SpritePacket.Path = "./resources/textures/";
	se::AssetData _Texture;

	_Texture.ID = "PoeImage";
	_Texture.Type = se::AssetData::AType::Texture;
	_Texture.Path = "./resources/textures/image.bin"; // if serialize like that need to specify full path and name
	Serrializer::SerrializeTexture("./project/resources/images/image.png", &_Texture);

	_Sprite.ID = "PoeImage";
	_Sprite.Type = se::AssetData::AType::Sprite;
	_Sprite.Childs.push_back(_Texture);
	_SpritePacket.Childs.push_back(_Sprite);

	_Texture.ID = "Font";
	_Texture.Type = se::AssetData::AType::Texture;
	_Texture.Path = "./resources/textures/font.bin"; // if serialize like that need to specify full path and name
	Serrializer::SerrializeTexture("./project/resources/fonts/candara/candara.png", &_Texture);

	se::AssetData _Font;
	_Font.ID = "FontFile";
	_Font.Type = se::AssetData::AType::Font;
	_Font.Path = "./resources/fonts/candara/candara.bin"; // if serialize like that need to specify full path and name
	Serrializer::SerrializeFont("./project/resources/fonts/candara/candara.fnt", &_Font);

	_Container.Childs.push_back(_ShaderPacket);
	_Container.Childs.push_back(_ModelsPacket);
	_Container.Childs.push_back(_SpritePacket);
	_Container.Childs.push_back(_Texture);
	_Container.Childs.push_back(_Font);

	se::AssetManager::WriteAssetDataList("map.bin", _Container);
	exit(0);*/

	//se::AssetManager::WriteAssetDataList("resources/scenes/AssetData.bin", _Container);
}

ShadeEditor::~ShadeEditor()
{

}

void ShadeEditor::OnInit()
{
	se::AssetManager::ReadAssetDataList("resources/scenes/AssetData.bin");
	se::System::InitVideo(se::RenderAPI::OpenGL, 4, 5);
	se::WindowManager::Create(se::Window());

	auto scene = CreateScene<MainScene>("Main");

	auto model = se::AssetManager::Hold<se::Model3D>("Models.Cube");
	se::ShadeShared<se::MeshShape> shape(new se::MeshShape());
	shape->AddVertex(glm::vec3(-1, -1, -1)); // 0 
	shape->AddVertex(glm::vec3(-1, 1, -1)); // 1 
	shape->AddVertex(glm::vec3(1, 1, -1)); // 2 
	shape->AddVertex(glm::vec3(1, -1, -1)); // 3 

	shape->AddVertex(glm::vec3(-1, -1, 1)); // 7
	shape->AddVertex(glm::vec3(1, -1, 1)); // 6
	shape->AddVertex(glm::vec3(1, 1, 1)); // 5
	shape->AddVertex(glm::vec3(-1, 1, 1)); // 4
	{
		auto cube = scene->CreateEntity("Cube1");
		cube.AddComponent<se::Transform3DComponent>().Transform.SetPostition(0,5,0);
		cube.AddComponent<se::Model3DComponent>(model);
		auto& rigidBody = cube.AddComponent<se::RigidBody>();
		rigidBody.AddCollider(shape);
		rigidBody.SetType(se::RigidBody::Type::Static);
	}
	{
		auto cube = scene->CreateEntity("Cube2");
		cube.AddComponent<se::Transform3DComponent>();
		cube.AddComponent<se::Model3DComponent>(model);
		auto& rigidBody = cube.AddComponent<se::RigidBody>();
		rigidBody.AddCollider(shape);
	}

	for (auto const& [name, scene] : GetScenes())
	{
		InitScene(name);
	}

	SetCurentScene("Main");

	auto grid = this->CreateEntity("Grid");
	grid.AddComponent<se::Transform3DComponent>();
	grid.AddComponent<se::DrawableComponent>(se::ShadeShared<se::Drawable>(new se::Grid(500, 500, 250)));

	this->CreateEntity("SceneViewPort").AddComponent<glm::vec2>();
	this->CreateEntity("ModelPreveiwViewPort").AddComponent<glm::vec2>();
	{
		auto camera = this->CreateEntity("EditorCamera");

		auto camera_copm = camera.AddComponent<se::CameraComponent>(new se::Camera(glm::vec3(0.0f, 5.0f, 0.0f), 45.0f, 1.0f, 0.01f, 3000.0f));
		camera.AddComponent<se::NativeScriptComponent>().Bind<se::FreeCameraController>();
		scene->SetActiveCamera(camera_copm.Camera);
	}
	{
		auto camera = this->CreateEntity("ModelCamera");

		auto camera_copm = camera.AddComponent<se::CameraComponent>(new se::Camera(glm::vec3(0.0f, 5.0f, 0.0f), 45.0f, 1.0f, 0.01f, 3000.0f));
		camera.AddComponent<se::NativeScriptComponent>().Bind<se::FreeCameraController>();
		//scene->SetActiveCamera(camera_copm.Camera);
	}

	auto light = this->GetCurrentScene()->CreateEntity("Direct Light");
	auto pLight = new se::GeneralLight();
	//pLight->SetDirection(0, -1, 0);
	auto& component = light.AddComponent<se::EnvironmentComponent>(se::ShadeShared<se::Environment>(pLight));
}

void ShadeEditor::OnUpdate(const se::Timer& deltaTime)
{
	auto entites = GetCurrentScene()->GetEntities().group<se::Transform3DComponent, se::RigidBody>();

	for (auto i = 0; i < entites.size(); i++)
	{
		auto [transform1, body1] = entites.get<se::Transform3DComponent, se::RigidBody>(entites[i]);
	
		for (auto j = i + 1; j < entites.size(); j++)
		{
			auto [transform2, body2] = entites.get<se::Transform3DComponent, se::RigidBody>(entites[j]);
			
			auto result = body1.TestCollision(transform1.Transform.GetModelMatrix(), body2, transform2.Transform.GetModelMatrix());
			if (result.HasCollision)
			{
				if (body1.GetType() == se::RigidBody::Type::Static && body2.GetType() == se::RigidBody::Type::Static)
				{
					continue;
				}
				else if (body1.GetType() == se::RigidBody::Type::Dynamic && body2.GetType() == se::RigidBody::Type::Dynamic)
				{
					transform1.Transform.GetPosition() += result.Direction * result.Depth / 2.0f;
					transform2.Transform.GetPosition() -= result.Direction * result.Depth / 2.0f;
				}
				else if (body1.GetType() == se::RigidBody::Type::Dynamic && body2.GetType() == se::RigidBody::Type::Static)
				{
					transform1.Transform.GetPosition() += result.Direction * result.Depth;
				}
				else if (body1.GetType() == se::RigidBody::Type::Static && body2.GetType() == se::RigidBody::Type::Dynamic)
				{
					transform2.Transform.GetPosition() += result.Direction * result.Depth;
				}
			}
		}
	}
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

