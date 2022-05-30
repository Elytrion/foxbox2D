#pragma once

struct Collider
{
	CP_Color color;
	CP_Vector position;
	CP_Vector velocity;
	CP_Vector accel;
	float rotation;

	virtual CP_Vector GetFurthestPointInDirection(CP_Vector direction) const = 0;
	virtual void DrawCollider() = 0;
};

struct CircleCollider : public Collider
{
	float radius;

	CP_Vector GetFurthestPointInDirection(CP_Vector direction) const override;
	void DrawCollider() override;

};

struct MeshCollider : public Collider
{
	float scale;
	std::vector<CP_Vector> vertices;

	CP_Vector GetFurthestPointInDirection(CP_Vector direction) const override;
	void DrawCollider() override;

};


std::vector<CP_Vector> CreateConvexPolygonVertices(int vertexCount, float radius, CP_Vector centrePos = CP_Vector_Zero());