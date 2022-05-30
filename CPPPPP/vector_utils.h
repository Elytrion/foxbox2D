#pragma once

CP_Vector operator+(const CP_Vector& lhs, const CP_Vector& rhs);

CP_Vector operator-(const CP_Vector& lhs, const CP_Vector& rhs);

CP_Vector operator*(const CP_Vector& lhs, const float scalar);

CP_Vector operator/(const CP_Vector& vec, const float scalar);

CP_Vector operator-(const CP_Vector& vec);

float operator^(const CP_Vector& lhs, const CP_Vector& rhs);

void operator+=(CP_Vector& lhs, const CP_Vector& rhs);

void operator-=(CP_Vector& lhs, const CP_Vector& rhs);

void operator*=(CP_Vector& vec, const float scalar);

void operator/=(CP_Vector& vec, const float scalar);

bool operator==(const CP_Vector& lhs, const CP_Vector& rhs);

bool operator!=(const CP_Vector& lhs, const CP_Vector& rhs);

CP_Vector CP_Vector_Rotate(const CP_Vector& vec, const float inDegrees);

CP_Vector CP_Vector_QNormalize(const CP_Vector& vec);

CP_Vector TripleCrossProduct(CP_Vector v1, CP_Vector v2, CP_Vector v3);