#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/glm/glm.hpp"

namespace se
{
	class SE_API Simplex
	{
	public:
		Simplex();
		~Simplex() = default;
		Simplex& operator=(std::initializer_list<glm::vec3> list) {
			for (auto v = list.begin(); v != list.end(); v++) {
				m_Points[std::distance(list.begin(), v)] = *v;
			}
			m_Count = list.size();
			return *this;
		};
		glm::vec3& operator[](unsigned i) { return m_Points[i]; }
		unsigned size() const { return m_Count; }
		void push_front(const glm::vec3& point);
		auto begin() const;
		auto end()   const;
	private:
		std::array<glm::vec3, 4> m_Points;
		uint32_t				 m_Count;
	};
}

