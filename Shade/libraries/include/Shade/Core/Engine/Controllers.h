#pragma once
#include "Shade/Core/Engine/ScriptableEntity.h"
#include "Shade/Core/Engine/Components.h"
#include "Shade/Core/Engine/Input.h"

namespace se
{
	class SE_API CameraController : public se::ScriptableEntity
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

					_Camera->RotateYaw(-(_DeltaPos.x * deltaTime) * m_RotationSpeed);
					_Camera->RotatePitch(-(_DeltaPos.y * deltaTime) * m_RotationSpeed);

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
		float m_RotationSpeed = 7.0f;
		float m_MovementSpeed = 7.0f;
	};
}

