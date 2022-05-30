#pragma once

#define GJK_MAX_ITERATION 64

struct Collider;

struct Simplex
{
private:
	std::array<CP_Vector, 3> s_points;
	unsigned s_size;
public:
	Simplex() : s_points({ 0,0,0 }), s_size(0) {};

	Simplex& operator=(std::initializer_list<CP_Vector> list)
	{
		for (auto point = list.begin(); point != list.end(); point++)
		{
			s_points[std::distance(list.begin(), point)] = *point;
		}
		s_size = list.size();

		return *this;
	}

	void push_front(CP_Vector point)
	{
		s_points = { point, s_points[0], s_points[1] };
		s_size = min(s_size + 1, 3u);
	}

	CP_Vector& operator[](unsigned i) { return s_points[i]; }
	unsigned size() const { return s_size; }

	auto begin() const { return s_points.begin(); }
	auto end() const { return s_points.end() - (3 - s_size); }
};

CP_Vector GetSupportPoint(const Collider* col_primary, const Collider* col_target, CP_Vector direction);

bool GJK_Reduced(const Collider* col_primary, const Collider* col_target, Simplex& termSimplex);

bool GJK_Full(const Collider* col_primary, const Collider* col_target, Simplex& termSimplex);