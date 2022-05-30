#include "main.h"

#define EPA_TOLERANCE 0.001f
#define OVERLAP_EPSILON 0.01f;

void ResolveCollision_Static(const Collision& colData, Collider* col_primary, Collider* col_target)
{
	CP_Vector interVec = colData.colNormal * (fabs(colData.interDist) / 2.0f);
	col_primary->position -= interVec;
	col_target->position += interVec;
}