#pragma once
#include "Shade/Core/Engine/CollisionShape.h"
#include "Shade/Core/Engine/Simplex.h"
#include "Shade/Core/Engine/EPA.h"

namespace se
{
	namespace algo
	{
#define GJK_MAX_ITERATION 32

		bool Line(
			Simplex& points,
			glm::vec3& direction)
		{
			glm::vec3 a = points[0];
			glm::vec3 b = points[1];

			glm::vec3 ab = b - a;
			glm::vec3 ao = -a;

			if (SameDirection(ab, ao))
			{
				direction = glm::cross(glm::cross(ab, ao), ab);
			}
			else 
			{
				points = { a };
				direction = ao;
			}

			return false;
		}
		bool Triangle(
			Simplex& points,
			glm::vec3& direction)
		{
			glm::vec3 a = points[0];
			glm::vec3 b = points[1];
			glm::vec3 c = points[2];

			glm::vec3 ab = b - a;
			glm::vec3 ac = c - a;
			glm::vec3 ao = -a;

			glm::vec3 abc = glm::cross(ab, ac);

			if (SameDirection(glm::cross(abc, ac), ao)) 
			{
				if (SameDirection(ac, ao))
				{
					points = { a, c };
					direction = glm::cross(glm::cross(ac, ao), ac);
				}
				else
				{
					return Line(points = { a, b }, direction);
				}
			}
			else 
			{
				if (SameDirection(glm::cross(ab, abc), ao))
				{
					return Line(points = { a, b }, direction);
				}
				else 
				{
					if (SameDirection(abc, ao))
					{
						direction = abc;
					}
					else 
					{
						points = { a, c, b };
						direction = -abc;
					}
				}
			}

			return false;
		}
		bool Tetrahedron(
			Simplex& points,
			glm::vec3& direction)
		{
			glm::vec3 a = points[0];
			glm::vec3 b = points[1];
			glm::vec3 c = points[2];
			glm::vec3 d = points[3];

			glm::vec3 ab = b - a;
			glm::vec3 ac = c - a;
			glm::vec3 ad = d - a;
			glm::vec3 ao = -a;

			glm::vec3 abc = glm::cross(ab, ac);
			glm::vec3 acd = glm::cross(ac, ad);
			glm::vec3 adb = glm::cross(ad, ab);

			if (SameDirection(abc, ao))
			{
				return Triangle(points = { a, b, c }, direction);
			}

			if (SameDirection(acd, ao))
			{
				return Triangle(points = { a, c, d }, direction);
			}

			if (SameDirection(adb, ao)) 
			{
				return Triangle(points = { a, d, b }, direction);
			}

			return true;
		}
		bool NextSimplex(
			Simplex& points,
			glm::vec3& direction)
		{
			switch (points.size()) {
			case 2: return Line(points, direction);
			case 3: return Triangle(points, direction);
			case 4: return Tetrahedron(points, direction);
			}

			// never should be here
			return false;
		}
		se::CollisionShape::CollisionData GJK(const se::CollisionShape& shapeA, const glm::mat4& transformA, const se::CollisionShape& shapeB , const glm::mat4& transformB)
		{
			// Get initial support point in any direction
			glm::vec3 support = Support(shapeA, transformA, shapeB, transformB, glm::vec3(1.0f, 0.0f, 0.0f));
			// Simplex is an array of points, max count is 4
			se::Simplex points;
			points.push_front(support);

			// New direction is towards the origin
			glm::vec3 direction = -support;
			for (auto i = 0; i < GJK_MAX_ITERATION; i++)
			{
				support = Support(shapeA, transformA, shapeB, transformB, direction);

				if (glm::dot(support, direction) <= 0) // If there <= then no proper colliding when any of 2 axies are aligned
					break;
				
				points.push_front(support);

				if (NextSimplex(points, direction))
				{
					return se::algo::EPA(points, shapeA, transformA, shapeB, transformB);
				}
			}

			return { false };
		}
	}
}
