#include "main.h"

CP_Vector operator+(const CP_Vector& lhs, const CP_Vector& rhs)
{
	return CP_Vector_Add(lhs, rhs);
}

CP_Vector operator-(const CP_Vector& lhs, const CP_Vector& rhs)
{
	return CP_Vector_Subtract(lhs, rhs);
}

CP_Vector operator*(const CP_Vector& lhs, const float scalar)
{
	return CP_Vector_Scale(lhs, scalar);
}

CP_Vector operator/(const CP_Vector& vec, const float scalar)
{
	return CP_Vector_Scale(vec, (1.0f/scalar));
}

CP_Vector operator-(const CP_Vector& vec)
{
	return CP_Vector_Negate(vec);
}

float operator^(const CP_Vector& lhs, const CP_Vector& rhs)
{
	return CP_Vector_DotProduct(lhs, rhs);
}

void operator+=(CP_Vector& lhs, const CP_Vector& rhs)
{
	lhs = lhs + rhs;
}

void operator-=(CP_Vector& lhs, const CP_Vector& rhs)
{
	lhs = lhs - rhs;
}

void operator*=(CP_Vector& vec, const float scalar)
{
	vec = vec * scalar;
}

void operator/=(CP_Vector& vec, const float scalar)
{
	vec = vec / scalar;
}

bool operator==(const CP_Vector& lhs, const CP_Vector& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!=(const CP_Vector& lhs, const CP_Vector& rhs)
{
	return !(lhs == rhs);
}

CP_Vector CP_Vector_Rotate(const CP_Vector& vec, const float inDegrees)
{
	CP_Matrix mtx = CP_Matrix_Rotate(inDegrees);
	return CP_Vector_MatrixMultiply(mtx, vec);
}

float QInvSqrt(float number)
{
	float x2 = number * 0.5f;
	float y = number;
	long i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (1.5F - x2 * y * y);
	return y;
}

CP_Vector CP_Vector_QNormalize(const CP_Vector& vec)
{
	float magnitudeSqr = QInvSqrt(vec ^ vec);
	return CP_Vector_Set(vec.x * magnitudeSqr, vec.y * magnitudeSqr);
}

CP_Vector TripleCrossProduct(CP_Vector v1, CP_Vector v2, CP_Vector v3)
{
	//using triple product expansion
	float adotc = v1 ^ v3;
	float bdotc = v2 ^ v3;
	CP_Vector ascale = v1 * bdotc;
	CP_Vector bscale = v2 * adotc;
	return (bscale - ascale);
}