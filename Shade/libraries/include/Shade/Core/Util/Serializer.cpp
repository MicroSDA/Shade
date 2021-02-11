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

static bool SerializeEntity(YAML::Emitter& out, se::Entity& entity)
{
	out << YAML::BeginMap; // Entity
	out << YAML::Key << "Entity" << YAML::Value << std::string(entity); // TODO: Entity ID goes here
	if (entity.HasComponent<se::TagComponent>())
	{
		out << YAML::Key << "TagComponent";
		out << YAML::BeginMap;

		auto& component = entity.GetComponent<se::TagComponent>().Tag;
		out << YAML::Key << "Tag" << YAML::Value << component;

		out << YAML::EndMap; 
	}
	if (entity.HasComponent<se::Model3DComponent>())
	{
		out << YAML::Key << "Model3DComponent";
		out << YAML::BeginMap; // Model3DComponent

		auto& component = entity.GetComponent<se::Model3DComponent>().Model3D;
		
		out << YAML::Key << "Asset" << YAML::Value << component->GetAssetId();

		out << YAML::EndMap; // Model3DComponent
	}
	if (entity.HasComponent<se::Transform3DComponent>())
	{
		out << YAML::Key << "Transform3DComponent";
		out << YAML::BeginMap; // TransformComponent

		auto& component = entity.GetComponent<se::Transform3DComponent>().Transform;
		out << YAML::Key << "Position" << YAML::Value << component.GetPosition();
		out << YAML::Key << "Rotation" << YAML::Value << component.GetRotation();
		out << YAML::Key << "Scale" << YAML::Value << component.GetScale();

		out << YAML::EndMap; // TransformComponent
	}

	out << YAML::EndMap; // Entity

	return false;
}
bool se::Serializer::SerializeScene(const std::string& filepath, se::Scene& scene)
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "Scene" << YAML::Value << scene.GetName();
	out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
	scene.GetEntities().each([&](auto entityID)
		{
			se::Entity entity { entityID , &scene };
			if (!entity)
				return;

			if(entity.HasComponent<se::Model3DComponent>()) // Only for model 3d for now
				SerializeEntity(out, entity);
		});
	out << YAML::EndSeq;
	out << YAML::EndMap;

	std::ofstream fout(filepath);
	fout << out.c_str();
    return false;
}

bool se::Serializer::DeserializeScene(const std::string& filepath, se::Scene& scene)
{
	YAML::Node data = YAML::LoadFile(filepath);
	if (!data["Scene"])
		return false;

	std::string sceneName = data["Scene"].as<std::string>();

	auto entities = data["Entities"];
	if (entities)
	{
		for (auto entity : entities)
		{
			std::uint32_t id = entity["Entity"].as<std::uint32_t>(); 
			if (entity["TagComponent"])
			{
				auto newEntity = scene.CreateEntity(entity["TagComponent"]["Tag"].as<std::string>());

				if (entity["Transform3DComponent"])
				{
					se::Transform3D transform;
					transform.SetPostition(entity["Transform3DComponent"]["Position"].as<glm::vec3>());
					transform.SetRotation(entity["Transform3DComponent"]["Rotation"].as<glm::vec3>());
					transform.SetScale(entity["Transform3DComponent"]["Scale"].as<glm::vec3>());
					newEntity.AddComponent<se::Transform3DComponent>(transform);
				}
				if (entity["Model3DComponent"])
				{
					se::AssetPointer<se::Model3D> pModel3D(se::AssetManager::Hold<se::Model3D>(entity["Model3DComponent"]["Asset"].as<std::string>()));
					newEntity.AddComponent<se::Model3DComponent>(pModel3D);
				}
			}
		}
	}

	return false;
}
