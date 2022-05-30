#pragma once

#define EPA_TOLERANCE 0.001f
#define OVERLAP_EPSILON 0.01f;
struct Collider;
struct Simplex;
struct Collision;

struct Edge
{
	Edge() : distance{ 0.0f }, normal{ CP_Vector_Zero() }, index{ 0 } {}
	float distance;
	CP_Vector normal;
	int index;
};

Collision EPA(Simplex& simp, const Collider* col_primary, const Collider* col_target);