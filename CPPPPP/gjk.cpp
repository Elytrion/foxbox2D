#include "main.h"

#pragma region Support Functions

CP_Vector GetSupportPoint(const Collider* col_primary, const Collider* col_target, CP_Vector direction)
{
	CP_Vector p1 = col_primary->GetFurthestPointInDirection(direction);
	CP_Vector p2 = col_target->GetFurthestPointInDirection(-direction);
	return (p1 - p2);
}

bool LineCase(Simplex& simp, CP_Vector& dir)
{
	//based on notation, pt A is always the most recently added point
	CP_Vector a = simp[0];
	CP_Vector b = simp[1];

	//calculate required normal
	CP_Vector AB = b - a;
	CP_Vector AO = -a;
	dir = TripleCrossProduct(AB, AO, AB);

	//the line can never contain the origin in a 2D/3D world
	//even if it does, I wont consider it a collision
	return false;
}

bool TriangleCase(Simplex& simp, CP_Vector& dir)
{
	CP_Vector a = simp[0];
	CP_Vector b = simp[1];
	CP_Vector c = simp[2];

	CP_Vector AB = b - a;
	CP_Vector AC = c - a;
	CP_Vector AO = -a;

	CP_Vector AB_Normal = TripleCrossProduct(AC, AB, AB);
	CP_Vector AC_Normal = TripleCrossProduct(AB, AC, AC);

	if ((AB_Normal ^ AO) > 0)
	{
		//origin in is region AB, update simplex
		simp = { a, b, c }; //setting up to remove point C from the simplex
		dir = AB_Normal;
		return false;
	}
	else if ((AC_Normal ^ AO) > 0)
	{
		//origin in is region AC, update simplex
		simp = { a, c, b }; //setting up to remove point B from the simplex
		dir = AC_Normal;
		return false;
	}

	return true;
}

bool UpdateSimplex(Simplex& simp, CP_Vector& dir)
{
	switch (simp.size())
	{
	case 2:
		return LineCase(simp, dir);
		break;
	case 3:
		return TriangleCase(simp, dir);
		break;
	}

	//if it reaches here GJK has imploded
	return false;
}

#pragma endregion

//Determines if the Minkowski Difference of two shapes contain the origin and returns the
//termination simplex (empty simplex if it does not contain the origin
//Utilizes the reduced 1 & 2-simplex vornoi region optimisation that avoids checking all 
//vornoi regions (may result in numerical inaccuracies in the long run)
bool GJK_Reduced(const Collider* col_primary, const Collider* col_target, Simplex& termSimplex)
{
	//getting intial direction
	CP_Vector direction = col_primary->position - col_target->position;

	//getting intital support point
	CP_Vector supportPt = GetSupportPoint(col_primary, col_target, direction);

	//creating a new simplex
	Simplex simp;
	simp.push_front(supportPt);

	//getting second direction (facing origin)
	direction = -supportPt;

	//enter loop
	for (int itr = 0; itr < GJK_MAX_ITERATION; itr++) //while (1)
	{
		supportPt = GetSupportPoint(col_primary, col_target, direction);

		//check if new point is "past the origin" using dot product
		if ((supportPt ^ direction) <= 0)
		{
			return false;
		}

		//add new support point to the simplex
		simp.push_front(supportPt);

		if (UpdateSimplex(simp, direction))
		{
			termSimplex = simp;
			return true;
		}
	}

	termSimplex = Simplex();
	return false;
}

bool GJK_Full(const Collider* col_primary, const Collider* col_target, Simplex& termSimplex)
{
	return false;
}