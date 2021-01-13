#pragma once
#include "Shade/Core/Engine/ScriptableEntity.h"
#include "Shade/Core/Engine/Components.h"
#include "Shade/Core/Engine/Input.h"

namespace se
{
	class SE_API Mode3DController : public se::ScriptableEntity
	{
	public:

		void OnCreate()
		{
			/*auto _Models = se::Application::GetApp().GetActiveScene()->GetEntities().view<se::Model3DComponent>();
			auto& Model  = _Models.get<se::Model3DComponent>(_Models[1]); // Suppose to be cube
			auto _Meshes =  Model.Model3D->GetEntities().view<se::MeshComponent, se::MaterialComponent>();

			auto entt = this->m_Entity.GetComponent<se::Model3DComponent>().Model3D->CreateEntity();
			entt.AddComponent<se::MeshComponent>(_Meshes.get<se::MeshComponent>(entt::entity(0)));
			entt.AddComponent<se::MaterialComponent>(_Meshes.get<se::MaterialComponent>(entt::entity(0)));*/
		}
		void OnDestroy()
		{

		}
		void OnUpdate(const se::Timer& deltaTime)
		{
			auto& _Tansform = GetComponent<se::Transform3DComponent>().Transform;
			_Tansform.SetRotation(0, _Tansform.GetRotation().y + (deltaTime * m_RotationSpeed), 0);
		}
	private:
		float m_RotationSpeed = 5.0f;
	};

	class SE_API LightController : public se::ScriptableEntity
	{
	public:
		void OnCreate()
		{
			m_GeneralLight = dynamic_cast<se::GeneralLight*>(this->GetComponent<se::EnvironmentComponent>().Environment);
			m_PointLight   = dynamic_cast<se::PointLight*>(this->GetComponent<se::EnvironmentComponent>().Environment);
			m_SpotLight    = dynamic_cast<se::SpotLight*>(this->GetComponent<se::EnvironmentComponent>().Environment);
		}
		void OnDestroy()
		{

		}
		void OnUpdate(const se::Timer& deltaTime)
		{

			if (m_GeneralLight)
			{
				se::Camera* _Camera = se::Application::GetApp().GetActiveScene()->GetMainCamera();
				if(se::Input::IsKeyboardBPressed(SDL_SCANCODE_LALT))
					m_GeneralLight->SetDirection(_Camera->GetForwardDirrection());
			}
			else if (m_PointLight)
			{
				{
					glm::fvec3 _Position = m_PointLight->GetPosition();
					if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_UP))
						m_PointLight->SetPosition(_Position.x, _Position.y, _Position.z + (m_MovementSpeed * deltaTime));
					if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_DOWN))
						m_PointLight->SetPosition(_Position.x, _Position.y, _Position.z - (m_MovementSpeed * deltaTime));
				}
				{
					glm::fvec3 _Position = m_PointLight->GetPosition();
					if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_LEFT))
						m_PointLight->SetPosition(_Position.x + (m_MovementSpeed * deltaTime), _Position.y, _Position.z);
					if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_RIGHT))
						m_PointLight->SetPosition(_Position.x - (m_MovementSpeed * deltaTime), _Position.y, _Position.z);
				}
				{
					glm::fvec3 _Position = m_PointLight->GetPosition();
					if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_KP_PLUS))
						m_PointLight->SetPosition(_Position.x , _Position.y + (m_MovementSpeed * deltaTime), _Position.z);
					if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_KP_MINUS))
						m_PointLight->SetPosition(_Position.x , _Position.y - (m_MovementSpeed * deltaTime), _Position.z);
				}
			}
			else if(m_SpotLight)
			{
				se::Camera* _Camera = se::Application::GetApp().GetActiveScene()->GetMainCamera();
				m_SpotLight->SetPosition(_Camera->GetPosition());
				m_SpotLight->SetDirection(_Camera->GetForwardDirrection());
			}
		}

	private:
		float             m_MovementSpeed = 7.0f;
		se::GeneralLight* m_GeneralLight  = nullptr;
		se::PointLight*   m_PointLight    = nullptr;
		se::SpotLight*    m_SpotLight     = nullptr;
	};


	class SE_API FreeCameraController : public se::ScriptableEntity
	{
	public:
		void OnCreate()
		{
			se::Input::SetMousePosition(se::WindowManager::GetWindow().Width / 2, se::WindowManager::GetWindow().Height / 2);
		}
		void OnDestroy()
		{
			
		}
		void OnUpdate(const se::Timer& deltaTime)
		{
			auto* _Camera = GetComponent<se::CameraComponent>().Camera;
			{ // Movment
				if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_W))
					_Camera->MoveForward(m_MovementSpeed * deltaTime);
				if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_S))
					_Camera->MoveBack(m_MovementSpeed * deltaTime);

				if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_A))
					_Camera->MoveLeft(m_MovementSpeed * deltaTime);
				if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_D))
					_Camera->MoveRight(m_MovementSpeed * deltaTime);
			}
			{
				if (se::Input::IsKeyboardBPressed(SDL_SCANCODE_LCTRL))
				{
					se::Input::ShowCursor(false);
					glm::ivec2 _DeltaPos = se::Input::GetMousePosition();
					_DeltaPos = _DeltaPos - glm::ivec2(se::WindowManager::GetWindow().Width / 2,
						se::WindowManager::GetWindow().Height / 2);

					_Camera->RotateYaw(  -(_DeltaPos.x * m_RotationSpeed) / 100); // No deltaTime here 
					_Camera->RotatePitch(-(_DeltaPos.y * m_RotationSpeed) / 100);

					se::Input::SetMousePosition(
						se::WindowManager::GetWindow().Width / 2,
						se::WindowManager::GetWindow().Height / 2);
				}
				else
				{
					se::Input::ShowCursor(true);
				}
				
			}
		}

	private:
		float m_RotationSpeed = 5.0f;
		float m_MovementSpeed = 7.0f;
	};
}

