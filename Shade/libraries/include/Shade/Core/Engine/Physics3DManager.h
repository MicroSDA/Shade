#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Timer.h"
#include "Shade/Core/Engine/RigidBody3D.h"
#include "ReactPhysics3D/include/reactphysics3d.h"

/*namespace reactphysics3d
{
	class PhysicsCommon;
	class PhysicsWorld;
	class RigidBody;
}*/

namespace se
{
	class SE_API Physics3DManager
	{
	public:
		static void Init();
		static void Update(const se::Timer& deltaTime);
		static void Attach(se::RigidBody3D*   body, const se::Transform3D& transform);
		static reactphysics3d::PhysicsCommon* GetCommon();
	private:
		//Singleton implementation
		Physics3DManager();
		~Physics3DManager() = default; // for now
		Physics3DManager(const Physics3DManager&) = delete;
		Physics3DManager& operator= (const Physics3DManager&) = delete;
		Physics3DManager(const Physics3DManager&&) = delete;
		Physics3DManager& operator= (const Physics3DManager&&) = delete;
		static Physics3DManager& Get();

		reactphysics3d::PhysicsWorld*   m_pWorld;
		reactphysics3d::PhysicsCommon   m_Common;
	};
}