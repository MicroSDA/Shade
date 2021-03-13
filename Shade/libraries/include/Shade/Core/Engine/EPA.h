#pragma once
#include "stdafx.h"
#include "Vendors/glm/glm.hpp"
#include "Shade/Core/Engine/Simplex.h"
#include "Shade/Core/Engine/CollisionShape.h"

namespace se
{
	namespace algo
	{
#define EPA_MAX_ITER 32

		bool SameDirection(
			const glm::vec3& direction,
			const glm::vec3& ao)
		{
			return glm::dot(direction, ao) > 0;
		}
		void AddIfUniqueEdge(
			std::vector<std::pair<size_t, size_t>>& edges,
			const std::vector<size_t>& faces,
			size_t a,
			size_t b)
		{
			auto reverse = std::find(               //      0--<--3
				edges.begin(),                     //     / \ B /   A: 2-0
				edges.end(),                       //    / A \ /    B: 0-2
				std::make_pair(faces[b], faces[a]) //   1-->--2
			);

			if (reverse != edges.end()) 
			{
				edges.erase(reverse);
			}
			else
			{
				edges.emplace_back(faces[a], faces[b]);
			}
		}

		std::pair<std::vector<glm::vec4>, size_t> GetFaceNormals(
			const std::vector<glm::vec3>& polytope,
			const std::vector<size_t>& faces)
		{
			std::vector<glm::vec4> normals;
			size_t minTriangle = 0;
			float  minDistance = FLT_MAX;

			for (size_t i = 0; i < faces.size(); i += 3) 
			{
				glm::vec3 a = polytope[faces[i    ]];
				glm::vec3 b = polytope[faces[i + 1]];
				glm::vec3 c = polytope[faces[i + 2]];

				glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
				float distance = glm::dot(normal, a);

				if (distance < 0) 
				{
					normal *= -1;
					distance *= -1;
				}

				normals.emplace_back(normal, distance);

				if (distance < minDistance) 
				{
					minTriangle = i / 3;
					minDistance = distance;
				}
			}

			return { normals, minTriangle };
		}

		glm::vec3 Support(
			const se::CollisionShape& shapeA, const glm::mat4& transformA,
			const se::CollisionShape& shapeB, const glm::mat4& transformB,
			const glm::vec3& direction)
		{
			return shapeA.FindFurthestPoint(transformA, direction) - shapeB.FindFurthestPoint(transformB, -direction);
		};

		se::CollisionShape::CollisionData EPA(
			const se::Simplex& simplex,
			const se::CollisionShape& shapeA, const glm::mat4& transformA,
			const se::CollisionShape& shapeB, const glm::mat4& transformB)
		{
			std::vector<glm::vec3> polytope(simplex.begin(), simplex.end());
			std::vector<size_t>    faces = {
				0, 1, 2,
				0, 3, 1,
				0, 2, 3,
				1, 3, 2
			};

			// list: vector4(normal, distance), index: min distance
			auto [normals, minFace] = GetFaceNormals(polytope, faces);

			glm::vec3 minNormal;
			float   minDistance = FLT_MAX;

			size_t iterations = 0;
			while (minDistance == FLT_MAX)
			{
				minNormal = glm::vec3(normals[minFace].x, normals[minFace].y, normals[minFace].z);
				minDistance = normals[minFace].w;

				if (iterations++ > EPA_MAX_ITER)
					break;

				glm::vec3 support = Support(shapeA, transformA, shapeB, transformB, minNormal);
				float sDistance = glm::dot(minNormal, support);

				if (glm::abs(sDistance - minDistance) > 0.001f) 
				{
					minDistance = FLT_MAX;

					std::vector<std::pair<size_t, size_t>> uniqueEdges;

					for (size_t i = 0; i < normals.size(); i++) 
					{
						if (SameDirection(normals[i], support)) 
						{
							size_t f = i * 3;

							AddIfUniqueEdge(uniqueEdges, faces, f, f + 1);
							AddIfUniqueEdge(uniqueEdges, faces, f + 1, f + 2);
							AddIfUniqueEdge(uniqueEdges, faces, f + 2, f);

							faces[f + 2] = faces.back(); faces.pop_back();
							faces[f + 1] = faces.back(); faces.pop_back();
							faces[f] = faces.back(); faces.pop_back();

							normals[i] = normals.back(); normals.pop_back();

							i--;
						}
					}

					std::vector<size_t> newFaces;
					for (auto [edgeIndex1, edgeIndex2] : uniqueEdges) 
					{
						newFaces.push_back(edgeIndex1);
						newFaces.push_back(edgeIndex2);
						newFaces.push_back(polytope.size());
					}

					polytope.push_back(support);

					auto [newNormals, newMinFace] = GetFaceNormals(polytope, newFaces);
					float oldMinDistance = FLT_MAX;
					for (size_t i = 0; i < normals.size(); i++)
					{
						if (normals[i].w < oldMinDistance)
						{
							oldMinDistance = normals[i].w;
							minFace = i;
						}
					}

					if (newNormals[newMinFace].w < oldMinDistance) 
					{
						minFace = newMinFace + normals.size();
					}

					faces.insert(faces.end(), newFaces.begin(), newFaces.end());
					normals.insert(normals.end(), newNormals.begin(), newNormals.end());
				}
			}

			if (minDistance == FLT_MAX) 
			{
				return { false };
			}

			return { true , minDistance + 0.001f, -minNormal };
		}
	}
}
