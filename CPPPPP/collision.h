#pragma once

struct Collider;
struct Simplex;

struct Collision
{
	Collision() : colNormal(CP_Vector_Zero()), interDist(0.0f) {}
	CP_Vector colNormal;
	float interDist;

	//contact points
	//the two colliders which collided
};

void ResolveCollision_Static(const Collision& colData, Collider* col_primary, Collider* col_target);
