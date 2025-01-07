#pragma once
#include "Vector3.h"

extern const float PI;
extern const float RAD2DEG;

bool checkCircleIntersection(const Vector3& a, const Vector3& b, const float aR, const float bR);

/// <summary>
/// https://stackoverflow.com/questions/40776703/converting-from-radians-to-degrees
/// </summary>
int randomInclusive(const int min, const int max);

float distance(const Vector3& a, const Vector3& b);

int roundToInt(const float f);

/// <summary>
/// https://stackoverflow.com/questions/40776703/converting-from-radians-to-degrees
/// </summary>
float toDegrees(const float rad);

float toRadians(const float deg);