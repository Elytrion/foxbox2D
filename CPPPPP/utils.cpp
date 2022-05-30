#include "main.h"

bool FloatIsWithinRange(float primary, float minInclusive, float maxInclusive)
{
	return (primary <= maxInclusive && primary >= minInclusive);
}

bool IsPointInRadius(CP_Vector center, float radius, CP_Vector pos)
{
	float distX = pos.x - center.x;
	float distY = pos.y - center.y;
	float distance = (distX * distX) + (distY * distY);
	return distance < (radius* radius);
}