#include "stdafx.h"
#include "BoxShape.h"

#define GJK_MAX_NUM_ITERATIONS 64

#define EPA_TOLERANCE 0.0001
#define EPA_MAX_NUM_FACES 64
#define EPA_MAX_NUM_LOOSE_EDGES 32
#define EPA_MAX_NUM_ITERATIONS 64

se::BoxShape::BoxShape(const glm::vec3& min, const glm::vec3& max) :
	se::CollisionShape(se::CollisionShape::Shape::Box)
{
	m_MinExt = min;
	m_MaxExt = max;
}

se::CollisionData se::BoxShape::TestCollision(const se::CollisionShape& other) const
{
	switch (other.GetShape())
	{
	case se::CollisionShape::Shape::Box: return BoxCollisionTest(static_cast<const se::BoxShape&>(other));
	default:
		assert(false && "Undefined collision shape!");
		break;
	}
}

glm::vec3 se::BoxShape::Support(const glm::vec3& direction) const
{
	glm::vec3 new_dir = m_RotationScaleMatixInversed * direction;
	glm::vec3 Result(
		(new_dir.x > 0) ? m_MaxExt.x : m_MinExt.x,
		(new_dir.y > 0) ? m_MaxExt.y : m_MinExt.y,
		(new_dir.z > 0) ? m_MaxExt.z : m_MinExt.z);

	return m_RotationScaleMatix * Result + m_Position;
}

void se::BoxShape::Simplex3(
	glm::vec3& A,
	glm::vec3& B,
	glm::vec3& C,
	glm::vec3& D,
	glm::vec3& direction,
	int& simplex_dimension) const
{
	// Triangle normal
	glm::vec3 normal = glm::cross(B - A, C - A);
	// Direction to origin
	glm::vec3 dir_to_origin = -A;

	// Which feature is closet to origin, make that the new simplex
	simplex_dimension = 2;
	// Close to edge AB
	if (glm::dot(glm::cross(B - A, normal), dir_to_origin) > 0.0f)
	{
		C = A;
		direction = glm::cross(glm::cross(B - A, dir_to_origin), B - A);
		return;
	}
	// Close to edge AC
	if (glm::dot(glm::cross(normal, C - A), dir_to_origin) > 0.0f)
	{
		B = A;
		direction = glm::cross(glm::cross(C - A, dir_to_origin), C - A);
		return;
	}

	simplex_dimension = 3;
	// Above triangle
	if (dot(normal, dir_to_origin) > 0.0f)
	{
		D = C;
		C = B;
		B = A;
		direction = normal;
		return;
	}
	else
	{
		D = B;
		B = A;
		direction = -normal;
	}
}

bool se::BoxShape::Simplex4(
	glm::vec3& A,
	glm::vec3& B,
	glm::vec3& C,
	glm::vec3& D,
	glm::vec3& direction,
	int& simplex_dimension) const
{
	glm::vec3 abc = glm::cross(B - A, C - A);
	glm::vec3 acd = glm::cross(C - A, D - A);
	glm::vec3 adb = glm::cross(D - A, B - A);

	glm::vec3 dir_to_origin = -A;
	simplex_dimension = 3;
	if (glm::dot(abc, dir_to_origin) > 0.0f)
	{
		D = C;
		C = B;
		B = A;
		direction = abc;
		return false;
	}
	else if (glm::dot(acd, dir_to_origin) > 0.0f)
	{
		B = A;
		direction = acd;
		return false;
	}
	else if (glm::dot(adb, dir_to_origin) > 0.0f)
	{
		C = D;
		D = B;
		B = A;
		direction = adb;
		return false;
	}

	return true;

}

glm::vec3 se::BoxShape::EPA(glm::vec3& A, glm::vec3& B, glm::vec3& C, glm::vec3& D, const se::BoxShape& other) const
{
	glm::vec3 faces[EPA_MAX_NUM_FACES][4]; //Array of faces, each with 3 verts and a normal

	//Init with final simplex from GJK
	faces[0][0] = A;
	faces[0][1] = B;
	faces[0][2] = C;
	faces[0][3] = glm::normalize(glm::cross(B - A, C - A)); //ABC
	faces[1][0] = A;
	faces[1][1] = C;
	faces[1][2] = D;
	faces[1][3] = glm::normalize(glm::cross(C - A, D - A)); //ACD
	faces[2][0] = A;
	faces[2][1] = D;
	faces[2][2] = B;
	faces[2][3] = glm::normalize(glm::cross(D - A, B - A)); //ADB
	faces[3][0] = B;
	faces[3][1] = D;
	faces[3][2] = C;
	faces[3][3] = glm::normalize(glm::cross(D - B, C - B)); //BDC

	int num_faces = 4;
	int closest_face;

	for (int i = 0; i < EPA_MAX_NUM_ITERATIONS; i++) {
		//Find face that's closest to origin
		float min_dist = dot(faces[0][0], faces[0][3]);
		closest_face = 0;
		for (int i = 1; i < num_faces; i++) {
			float dist = dot(faces[i][0], faces[i][3]);
			if (dist < min_dist) {
				min_dist = dist;
				closest_face = i;
			}
		}

		//search normal to face that's closest to origin
		glm::vec3 search_dir = faces[closest_face][3];
		glm::vec3 p = other.Support(search_dir) - this->Support(-search_dir);

		if (glm::dot(p, search_dir) - min_dist < EPA_TOLERANCE) {
			//Convergence (new point is not significantly further from origin)
			return faces[closest_face][3] * glm::dot(p, search_dir); //dot vertex with normal to resolve collision along normal!
		}

		glm::vec3 loose_edges[EPA_MAX_NUM_LOOSE_EDGES][2]; //keep track of edges we need to fix after removing faces
		int num_loose_edges = 0;

		//Find all triangles that are facing p
		for (int i = 0; i < num_faces; i++)
		{
			if (glm::dot(faces[i][3], p - faces[i][0]) > 0) //triangle i faces p, remove it
			{
				//Add removed triangle's edges to loose edge list.
				//If it's already there, remove it (both triangles it belonged to are gone)
				for (int j = 0; j < 3; j++) //Three edges per face
				{
					glm::vec3 current_edge[2] = { faces[i][j], faces[i][(j + 1) % 3] };
					bool found_edge = false;
					for (int k = 0; k < num_loose_edges; k++) //Check if current edge is already in list
					{
						if (loose_edges[k][1] == current_edge[0] && loose_edges[k][0] == current_edge[1]) {
							//Edge is already in the list, remove it
							//THIS ASSUMES EDGE CAN ONLY BE SHARED BY 2 TRIANGLES (which should be true)
							//THIS ALSO ASSUMES SHARED EDGE WILL BE REVERSED IN THE TRIANGLES (which 
							//should be true provided every triangle is wound CCW)
							loose_edges[k][0] = loose_edges[num_loose_edges - 1][0]; //Overwrite current edge
							loose_edges[k][1] = loose_edges[num_loose_edges - 1][1]; //with last edge in list
							num_loose_edges--;
							found_edge = true;
							k = num_loose_edges; //exit loop because edge can only be shared once
						}
					}//endfor loose_edges

					if (!found_edge) { //add current edge to list
						// assert(num_loose_edges<EPA_MAX_NUM_LOOSE_EDGES);
						if (num_loose_edges >= EPA_MAX_NUM_LOOSE_EDGES) break;
						loose_edges[num_loose_edges][0] = current_edge[0];
						loose_edges[num_loose_edges][1] = current_edge[1];
						num_loose_edges++;
					}
				}

				//Remove triangle i from list
				faces[i][0] = faces[num_faces - 1][0];
				faces[i][1] = faces[num_faces - 1][1];
				faces[i][2] = faces[num_faces - 1][2];
				faces[i][3] = faces[num_faces - 1][3];
				num_faces--;
				i--;
			}//endif p can see triangle i
		}//endfor num_faces

		//Reconstruct polytope with p added
		for (int i = 0; i < num_loose_edges; i++)
		{
			// assert(num_faces<EPA_MAX_NUM_FACES);
			if (num_faces >= EPA_MAX_NUM_FACES) break;
			faces[num_faces][0] = loose_edges[i][0];
			faces[num_faces][1] = loose_edges[i][1];
			faces[num_faces][2] = p;
			faces[num_faces][3] = glm::normalize(glm::cross(loose_edges[i][0] - loose_edges[i][1], loose_edges[i][0] - p));

			//Check for wrong normal to maintain CCW winding
			float bias = 0.000001; //in case dot result is only slightly < 0 (because origin is on face)
			if (glm::dot(faces[num_faces][0], faces[num_faces][3]) + bias < 0) {
				glm::vec3 temp = faces[num_faces][0];
				faces[num_faces][0] = faces[num_faces][1];
				faces[num_faces][1] = temp;
				faces[num_faces][3] = -faces[num_faces][3];
			}
			num_faces++;
		}
	} //End for iterations
	printf("EPA did not converge\n");
	//Return most recent closest point
	return (faces[closest_face][3] * dot(faces[closest_face][0], faces[closest_face][3]));
}

se::CollisionData se::BoxShape::BoxCollisionTest(const se::BoxShape& other) const
{
	glm::vec3 A, B, C, D; // Simplexs

	// Derection between box 1 and box 2
	glm::vec3 direction_betwen = this->m_Position - other.m_Position;

	//Initial point for simplex
	C = other.Support(direction_betwen) - this->Support(-direction_betwen);
	direction_betwen = -C;
	B = other.Support(direction_betwen) - this->Support(-direction_betwen);

	if (glm::dot(B, direction_betwen) < 0.0f)
		return { false, glm::vec3(0.0f, 0.0f, 0.0f) }; // We didn't reach the origin, won't enclose it
	else
	{
		// Search perpendicular to line segment towards origin
		direction_betwen = glm::cross(glm::cross(C - B, -B), C - B);
		if (direction_betwen == glm::vec3(0.0f, 0.0f, 0.0f)) // Origin is on this line segment
		{
			direction_betwen = glm::cross(C - B, glm::vec3(1.0f, 0.0f, 0.0f)); // Normal with x-axis
			if (direction_betwen == glm::vec3(0.0f, 0.0f, 0.0f))
				direction_betwen = glm::cross(C - B, glm::vec3(0.0f, 0.0f, -1.0f)); // Normal with z-axis
		}

		int simplex_dimension = 2;
		for (int i = 0; i < GJK_MAX_NUM_ITERATIONS; i++)
		{
			A = other.Support(direction_betwen) - this->Support(-direction_betwen);
			if (glm::dot(A, direction_betwen) < 0.0f)
				return { false, glm::vec3(0.0f, 0.0f, 0.0f) }; // We didn't reach the origin, won't enclose it

			simplex_dimension++;
			if (simplex_dimension == 3)
			{
				Simplex3(A, B, C, D, direction_betwen, simplex_dimension);
			}
			else if (Simplex4(A, B, C, D, direction_betwen, simplex_dimension)) // update_simplex4
			{
				return { true , EPA(A, B, C, D, other) };
			}
		}

		return { false, glm::vec3(0.0f, 0.0f, 0.0f) }; // We didn't reach the origin, won't enclose it
	}
}

