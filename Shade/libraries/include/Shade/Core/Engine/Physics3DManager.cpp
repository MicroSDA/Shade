#include "stdafx.h"
#include "Physics3DManager.h"
//#include "ReactPhysics3D/include/reactphysics3d.h"

se::Physics3DManager::Physics3DManager() :
	m_pWorld(nullptr)
{
	
}

se::Physics3DManager& se::Physics3DManager::Get()
{
	static Physics3DManager _Instatnce;
	return _Instatnce;
}

void se::Physics3DManager::Init()
{
	Get().m_pWorld = Get().m_Common.createPhysicsWorld();
}

void se::Physics3DManager::Update(const se::Timer& deltaTime)
{
	Get().m_pWorld->update(deltaTime);
}

void se::Physics3DManager::Attach(se::RigidBody3D* body, const se::Transform3D& transform)
{
	reactphysics3d::Transform tr;
	reactphysics3d::Quaternion qat;
	glm::quat gqat(transform.GetRotation());

	tr.setPosition(reactphysics3d::Vector3(transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z));
	qat.setAllValues(gqat.x, gqat.y, gqat.z, gqat.w);

	tr.setOrientation(qat);
	
	body->m_RigidBody       = Get().m_pWorld->createRigidBody(tr);

	switch (body->m_Type)
	{
	case se::RigidBody3D::Type::Static:
		body->m_RigidBody->setType(reactphysics3d::BodyType::STATIC);
		break;
	case se::RigidBody3D::Type::Dynamic:
		body->m_RigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
		break;
	default:
		break;
	}

	body->m_RigidBody->addCollider(body->m_pCollisionShape, reactphysics3d::Transform::identity());
}

reactphysics3d::PhysicsCommon* se::Physics3DManager::GetCommon()
{
	return &Get().m_Common;
}
