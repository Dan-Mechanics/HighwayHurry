#pragma once
#include "Vector3.h"

extern const float PI;
extern const float RAD2DEG;

float getDistance(const Vector3& a, const Vector3& b);
float getDot(const Vector3& a, const Vector3& b);
float getNormalizedDot(Vector3 a, Vector3 b);
Vector3 getCross(const Vector3& a, const Vector3& b);

bool checkCircleIntersection(const Vector3& a, const Vector3& b, const float aR, const float bR);

/// <summary>
/// https://stackoverflow.com/questions/40776703/converting-from-radians-to-degrees
/// </summary>
int randomInclusive(const int min, const int max);

int roundToInt(const float f);

/// <summary>
/// https://stackoverflow.com/questions/40776703/converting-from-radians-to-degrees
/// </summary>
float toDegrees(const float rad);

float toRadians(const float deg);