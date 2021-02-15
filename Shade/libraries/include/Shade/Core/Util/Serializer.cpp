#include "stdafx.h"
#include "Serializer.h"
#include <Shade/Core/Engine/Scene.h>
#include <Shade/Core/Engine/Entity.h>
#include <Shade/Core/Engine/Components.h>
#include <yaml-cpp/yaml.h>


namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

}
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
	return out;
}

static bool SerrializeTagComponent(se::Entity& entity, YAML::Emitter& emitter)
{
	if (entity.HasComponent<se::TagComponent>())
	{
		auto& component = entity.GetComponent<se::TagComponent>().Tag;
		emitter << YAML::Key << "TagComponent" << YAML::BeginMap;
		emitter << YAML::Key << "Tag" << YAML::Value << component;
		emitter << YAML::EndMap;
		return true;
	}
	else
		return false;
}

static bool SerrializeTransform3DComponent(se::Entity& entity, YAML::Emitter& emitter)
{
	if (entity.HasComponent<se::Transform3DComponent>())
	{
		auto& component = entity.GetComponent<se::Transform3DComponent>().Transform;
		emitter << YAML::Key << "Transform3DComponent" << YAML::BeginMap;
		emitter << YAML::Key << "Position" << YAML::Value << component.GetPosition();
		emitter << YAML::Key << "Rotation" << YAML::Value << component.GetRotation();
		emitter << YAML::Key << "Scale" << YAML::Value << component.GetScale();
		emitter << YAML::EndMap;
		return true;
	}
	else
		return false;
}

static bool SerrializeModel3DComponent(se::Entity& entity, YAML::Emitter& emitter)
{
	if (entity.HasComponent<se::Model3DComponent>())
	{
		auto& component = entity.GetComponent<se::Model3DComponent>().Model3D;
		emitter << YAML::Key << "Model3DComponent" << YAML::BeginMap;
		emitter << YAML::Key << "Asset" << YAML::Value << component->GetAssetId();
		emitter << YAML::EndMap;
		return true;
	}
	else
		return false;
}

static bool SerrializeCameraComponent(se::Entity& entity, YAML::Emitter& emitter)
{
	if (entity.HasComponent<se::CameraComponent>())
	{
		auto& component = entity.GetComponent<se::CameraComponent>();
		emitter << YAML::Key << "CameraComponent" << YAML::BeginMap;
		emitter << YAML::Key << "IsPrimary" << YAML::Value << component.IsPrimary;
		emitter << YAML::Key << "Position" << YAML::Value << component.Camera->GetPosition();
		emitter << YAML::Key << "Direction" << YAML::Value << component.Camera->GetForwardDirrection();
		emitter << YAML::Key << "Fov" << YAML::Value << component.Camera->GetFov();
		emitter << YAML::Key << "Aspect" << YAML::Value << component.Camera->GetAspect();
		emitter << YAML::Key << "Near" << YAML::Value << component.Camera->GetNear();
		emitter << YAML::Key << "Far" << YAML::Value << component.Camera->GetFar();
		emitter << YAML::EndMap; // CameraComponent
		return true;
	}
	else
		return false;
}

static bool SerrializeEnvironmentComponent(se::Entity& entity, YAML::Emitter& emitter)
{
	if (entity.HasComponent<se::EnvironmentComponent>())
	{
		auto& environment = entity.GetComponent<se::EnvironmentComponent>().Environment;
		emitter << YAML::Key << "EnvironmentComponent" << YAML::BeginMap;
		switch (environment->GetType())
		{
		case se::Environment::Type::GeneralLight:
		{
			auto pLight = static_cast<se::GeneralLight*>(environment.get());
			emitter << YAML::Key << "Type" << YAML::Value << static_cast<uint32_t>(pLight->GetType());
			emitter << YAML::Key << "Direction" << YAML::Value << pLight->GetDirection();
			emitter << YAML::Key << "Ambient" << YAML::Value << pLight->GetAmbientColor();
			emitter << YAML::Key << "Diffuse" << YAML::Value << pLight->GetDiffuseColor();
			emitter << YAML::Key << "Specular" << YAML::Value << pLight->GetSpecularColor();
			break;
		}
		case se::Environment::Type::PointLight:
		{
			auto pLight = static_cast<se::PointLight*>(environment.get());
			emitter << YAML::Key << "Type" << YAML::Value << static_cast<uint32_t>(pLight->GetType());
			emitter << YAML::Key << "Position" << YAML::Value << pLight->GetPosition();
			emitter << YAML::Key << "Ambient" << YAML::Value << pLight->GetAmbientColor();
			emitter << YAML::Key << "Diffuse" << YAML::Value << pLight->GetDiffuseColor();
			emitter << YAML::Key << "Specular" << YAML::Value << pLight->GetSpecularColor();
			emitter << YAML::Key << "Constant" << YAML::Value << pLight->GetConstant();
			emitter << YAML::Key << "Linear" << YAML::Value << pLight->GetLinear();
			emitter << YAML::Key << "Qaudratic" << YAML::Value << pLight->GetQaudratic();
			break;
		}
		case se::Environment::Type::SpotLight:
		{
			auto pLight = static_cast<se::SpotLight*>(environment.get());
			emitter << YAML::Key << "Type" << YAML::Value << static_cast<uint32_t>(pLight->GetType());
			emitter << YAML::Key << "Position" << YAML::Value << pLight->GetPosition();
			emitter << YAML::Key << "Direction" << YAML::Value << pLight->GetDirection();
			emitter << YAML::Key << "Ambient" << YAML::Value << pLight->GetAmbientColor();
			emitter << YAML::Key << "Diffuse" << YAML::Value << pLight->GetDiffuseColor();
			emitter << YAML::Key << "Specular" << YAML::Value << pLight->GetSpecularColor();
			emitter << YAML::Key << "Constant" << YAML::Value << pLight->GetConstant();
			emitter << YAML::Key << "Linear" << YAML::Value << pLight->GetLinear();
			emitter << YAML::Key << "Qaudratic" << YAML::Value << pLight->GetQaudratic();
			emitter << YAML::Key << "MinAngle" << YAML::Value << pLight->GetMinAngle();
			emitter << YAML::Key << "MaxAngle" << YAML::Value << pLight->GetMaxAngle();
			break;
		}
		}
		emitter << YAML::EndMap;
		return true;
	}
	else
		return false;
}

static bool SerializeEntity(se::Entity& entity, YAML::Emitter& emitter)
{
	emitter << YAML::BeginMap << YAML::Key << "Entity" << YAML::Value << static_cast<uint32_t>(entity);
	SerrializeTagComponent(entity, emitter);
	SerrializeTransform3DComponent(entity, emitter);
	SerrializeModel3DComponent(entity, emitter);
	SerrializeCameraComponent(entity, emitter);
	SerrializeEnvironmentComponent(entity, emitter);
	emitter << YAML::EndMap;
	return true; // TODO hm it's looks useless
}

bool se::Serializer::SerializeScene(const std::string& filepath, se::Scene& scene)
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "Scene" << YAML::Value << scene.GetName();
	out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
	scene.GetEntities().each([&](auto entityID)
		{
			se::Entity entity{ entityID , &scene };
			if (!entity)
				return;
			SerializeEntity(entity, out);
		});
	out << YAML::EndSeq;
	out << YAML::EndMap;

	std::ofstream fout(filepath);
	fout << out.c_str();
	return false;
}

static bool DeserializeTagComponent(se::Entity& entity, YAML::detail::iterator_value& iter_value)
{
	if (iter_value["TagComponent"])
	{
		entity.GetComponent<se::TagComponent>().Tag = iter_value["TagComponent"]["Tag"].as<std::string>();
		return true;
	}
	else
		return false;
}

static bool DeserializeTransform3DComponent(se::Entity& entity, YAML::detail::iterator_value& iter_value)
{
	if (iter_value["Transform3DComponent"])
	{
		auto ser_component = iter_value["Transform3DComponent"];
		se::Transform3DComponent transform_component;
		transform_component.Transform.SetPostition(ser_component["Position"].as<glm::vec3>());
		transform_component.Transform.SetRotation(ser_component["Rotation"].as<glm::vec3>());
		transform_component.Transform.SetScale(ser_component["Scale"].as<glm::vec3>());
		entity.AddComponent<se::Transform3DComponent>(transform_component);
		return true;
	}
	else
		return false;
}

static bool DeserializeModel3DComponent(se::Entity& entity, YAML::detail::iterator_value& iter_value)
{
	if (iter_value["Model3DComponent"])
	{
		auto ser_component = iter_value["Model3DComponent"];
		const std::string asset = ser_component["Asset"].as<std::string>();
		auto pModel = se::AssetManager::Hold<se::Model3D>(asset);
		entity.AddComponent<se::Model3DComponent>(pModel);
		return true;
	}
	else
		return false;
}

static bool DeserializeCameraComponent(se::Entity& entity, YAML::detail::iterator_value& iter_value)
{
	if (iter_value["CameraComponent"])
	{
		se::Camera* pCamera = new se::Camera();
		auto ser_component = iter_value["CameraComponent"];
		pCamera->SetPosition(ser_component["Position"].as<glm::vec3>());
		pCamera->SeDirection(ser_component["Direction"].as<glm::vec3>());
		pCamera->SetAspect(ser_component["Aspect"].as<float>());
		pCamera->SetFov(ser_component["Fov"].as<float>());
		pCamera->SetNear(ser_component["Near"].as<float>());
		pCamera->SetFar(ser_component["Far"].as<float>());
		pCamera->Resize();
		entity.AddComponent<se::CameraComponent>(pCamera).IsPrimary = ser_component["IsPrimary"].as<bool>();
		return true;
	}
	else
		return false;
}

static bool DeserializeEnvironmentComponent(se::Entity& entity, YAML::detail::iterator_value& iter_value)
{
	if (iter_value["EnvironmentComponent"])
	{
		auto ser_component = iter_value["EnvironmentComponent"];
		switch (ser_component["Type"].as<uint32_t>())
		{
		case (uint32_t)se::Environment::Type::GeneralLight: // TODO how to convert it to uint32_t without cast
		{
			auto pLight = new se::GeneralLight();
			pLight->SetDirection(ser_component["Direction"].as<glm::vec3>());
			pLight->SetAmbientColor(ser_component["Ambient"].as<glm::vec3>());
			pLight->SetDiffuseColor(ser_component["Diffuse"].as<glm::vec3>());
			pLight->SetSpecularColor(ser_component["Specular"].as<glm::vec3>());
			entity.AddComponent<se::EnvironmentComponent>(se::ShadeShared<se::Environment>(pLight));
			return true;
		}
		case (uint32_t)se::Environment::Type::PointLight: // TODO how to convert it to uint32_t without cast
		{
			auto pLight = new se::PointLight();
			pLight->SetPosition(ser_component["Position"].as<glm::vec3>());
			pLight->SetAmbientColor(ser_component["Ambient"].as<glm::vec3>());
			pLight->SetDiffuseColor(ser_component["Diffuse"].as<glm::vec3>());
			pLight->SetSpecularColor(ser_component["Specular"].as<glm::vec3>());
			pLight->SetConstant(ser_component["Constant"].as<float>());
			pLight->SetLinear(ser_component["Linear"].as<float>());
			pLight->SetQaudratic(ser_component["Qaudratic"].as<float>());
			entity.AddComponent<se::EnvironmentComponent>(se::ShadeShared<se::Environment>(pLight));
			return true;
		}
		case (uint32_t)se::Environment::Type::SpotLight: // TODO how to convert it to uint32_t without cast
		{
			auto pLight = new se::SpotLight();
			pLight->SetPosition(ser_component["Position"].as<glm::vec3>());
			pLight->SetDirection(ser_component["Direction"].as<glm::vec3>());
			pLight->SetAmbientColor(ser_component["Ambient"].as<glm::vec3>());
			pLight->SetDiffuseColor(ser_component["Diffuse"].as<glm::vec3>());
			pLight->SetSpecularColor(ser_component["Specular"].as<glm::vec3>());
			pLight->SetConstant(ser_component["Constant"].as<float>());
			pLight->SetLinear(ser_component["Linear"].as<float>());
			pLight->SetQaudratic(ser_component["Qaudratic"].as<float>());
			pLight->SetMinAngle(ser_component["MinAngle"].as<float>());
			pLight->SetMaxAngle(ser_component["MaxAngle"].as<float>());
			entity.AddComponent<se::EnvironmentComponent>(se::ShadeShared<se::Environment>(pLight));
			return true;
		}
		default:
			return false; // keep in mind
		}
	}
	else
		return false;
}

static bool DeserializeEntity(se::Entity& entity, YAML::detail::iterator_value& iter_value)
{

	DeserializeTagComponent(entity, iter_value);
	DeserializeTransform3DComponent(entity, iter_value);
	DeserializeModel3DComponent(entity, iter_value);
	DeserializeCameraComponent(entity, iter_value);
	DeserializeEnvironmentComponent(entity, iter_value);

	return true; // usless
}

bool se::Serializer::DeserializeScene(const std::string& filepath, se::Scene& scene)
{
	YAML::Node serialized_scene = YAML::LoadFile(filepath);
	if (!serialized_scene["Scene"])
		return false;

	std::string sceneName    = serialized_scene["Scene"].as<std::string>();
	auto serialized_entities = serialized_scene["Entities"];
	if (serialized_entities)
	{
		for (auto entity : serialized_entities)
		{
			std::uint32_t id = entity["Entity"].as<std::uint32_t>(); 
			auto entt = scene.CreateEntity(entity["TagComponent"]["Tag"].as<std::string>());
			DeserializeEntity(entt, entity);
		}

		return true;
	}
}