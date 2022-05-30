#include "main.h"

#pragma region Support Functions

Edge FindClosestEdge(std::vector<CP_Vector>& poly)
{
	Edge closest;
	closest.distance = FLT_MAX;
	for (int i = 0; i < poly.size(); i++)
	{
		int j = (i + 1) % poly.size();

		CP_Vector edge = poly[i] - poly[j];
		CP_Vector normal;

		normal = { edge.y, -edge.x };
		normal = CP_Vector_QNormalize(normal);

		float distance = normal ^ poly[i];

		//wrong handedness, must flip
		if (distance < 0)
		{
			distance *= -1;
			normal *= -1;
		}

		//if this distance is closer, use this distance
		if (distance < closest.distance)
		{
			closest.distance = distance;
			closest.normal = normal;
			closest.index = j;
		}
	}
	//return closest edge found
	return closest;
}

#pragma endregion

//Can still be improved!
Collision EPA(Simplex& simp, const Collider* col_primary, const Collider* col_target)
{
	std::vector<CP_Vector> polytope(simp.begin(), simp.end());

	for (int i = 0; i < GJK_MAX_ITERATION; i++)
	{
		Edge closestEdge = FindClosestEdge(polytope);

		CP_Vector support = GetSupportPoint(col_primary, col_target, closestEdge.normal);

		float supportDist = support ^ closestEdge.normal;

		if (abs(supportDist - closestEdge.distance) < EPA_TOLERANCE)
		{
			//std::cout << "Found solution (EPA)\n";
			//solution found
			Collision col;
			col.colNormal = closestEdge.normal;
			col.interDist = supportDist;
			return col;
		}
		else
		{
			//std::cout << "Expanding the polytope (EPA)\n";
			polytope.insert(polytope.begin() + closestEdge.index, support);
		}
	}
	return Collision();
}