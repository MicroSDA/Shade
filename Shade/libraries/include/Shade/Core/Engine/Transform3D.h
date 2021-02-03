#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/glm/glm.hpp"
#include "Vendors/glm/gtx/transform.hpp"

namespace se {

	class SE_API Transform3D
	{
	public:
		Transform3D();
		~Transform3D();
		inline void SetPostition(const float& x, const float& y, const float& z) { m_Possition.x = x; m_Possition.y = y; m_Possition.z = z;};
		inline void SetPostition(const glm::fvec3& position)                     { m_Possition = position; };
		inline void SetRotation(const float& x, const float& y, const float& z)  { m_Rotation.x = x; m_Rotation.y = y; m_Rotation.z = z; };
		inline void SetRotation(const glm::fvec3& rotation)                      { m_Rotation = rotation; };
		inline void SetScale(const float& x, const float& y, const float& z)     { m_Scale.x = x; m_Scale.y = y; m_Scale.z = z; };
		inline void SetScale(const glm::fvec3& scale)                            { m_Scale = scale; };

		inline const glm::fvec3& GetPosition() const { return m_Possition; };
		inline const glm::fvec3& GetRotation() const { return m_Rotation; };
		inline const glm::fvec3& GetScale()    const { return m_Scale; };

		inline glm::fvec3& GetPositionRef() { return m_Possition; };
		inline glm::fvec3& GetRotationRef() { return m_Rotation; };
		inline glm::fvec3& GetScaleRef()    { return m_Scale; };

		glm::mat4 GetModelMatrix() const;
	private:
		glm::fvec3 m_Possition;
		glm::fvec3 m_Rotation;
		glm::fvec3 m_Scale;
	};
}

