#include "main.h"

#pragma region Circle Collider

CP_Vector CircleCollider::GetFurthestPointInDirection(CP_Vector direction) const
{
	//direction MUST be normalized here
	//as distance to be calculated has to be accurate
	CP_Vector normDir = CP_Vector_QNormalize(direction);
	CP_Vector resizedDir = CP_Vector_Scale(normDir, radius);
	return CP_Vector_Add(position, resizedDir);
}

void CircleCollider::DrawCollider() 
{
	CP_Settings_Fill(color);
	CP_Graphics_DrawCircle(position.x, position.y, radius * 2);
	CP_Settings_Fill(CP_Color_Create(127, 127, 127, 255));
}

#pragma endregion

#pragma region Mesh Collider

CP_Vector MeshCollider::GetFurthestPointInDirection(CP_Vector direction) const
{
	CP_Vector maxPoint = CP_Vector_Zero();
	float maxDistance = -FLT_MAX;

	//direction DOES not have to be normalized here
	//As all checks are subjective to the first
	CP_Vector normDir = direction;

	for (CP_Vector vertex : vertices)
	{
		vertex = CP_Vector_Add(vertex, position);
		float currDistance = CP_Vector_DotProduct(vertex, normDir);
		if (currDistance > maxDistance)
		{
			maxDistance = currDistance;
			maxPoint = vertex;
		}
	}

	return maxPoint;
}

void MeshCollider::DrawCollider()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		CP_Settings_Fill(color);
		CP_Vector updatedVertex = CP_Vector_Add(position, vertices[i]);
		CP_Vector updatedNxtVertex = CP_Vector_Add(position, vertices[(i + 1) % vertices.size()]);
		CP_Graphics_DrawCircle(position.x, position.y, 10);
		CP_Graphics_DrawCircle(updatedVertex.x, updatedVertex.y, 5);
		CP_Graphics_DrawLine(updatedVertex.x, updatedVertex.y, updatedNxtVertex.x, updatedNxtVertex.y);
		CP_Settings_Fill(CP_Color_Create(127, 127, 127, 255));
	}
}

#pragma endregion

std::vector<CP_Vector> CreateConvexPolygonVertices(int vertexCount, float radius, CP_Vector centrePos)
{
	bool test;
	std::vector<CP_Vector> vertexes;
	std::vector<float> angles;
	while (angles.size() < vertexCount)
	{
		test = false;
		float newAngle = CP_Random_RangeFloat(0.0f, 2.0f * M_PI);
		for (int i = 0; i < angles.size(); i++)
		{
			if (FloatIsWithinRange(newAngle, angles[i] - 0.5f, angles[i] + 0.5f))
			{
				test = true;
			}
		}
		if (!test)
			angles.push_back(newAngle);
	}

	std::sort(angles.begin(), angles.end());

	for (int i = 0; i < vertexCount; i++)
	{
		float xcoord = centrePos.x + radius * cos(angles[i]);
		float ycoord = centrePos.y + radius * sin(angles[i]);
		vertexes.push_back({ xcoord, ycoord });
	}

	return vertexes;
}
