#include "MathUtils.h"
#include "Vector3.h"
#include <SFML/Graphics.hpp>

const float PI = 3.141592653589793238463f;
const float RAD2DEG = 180 / PI;

int roundToInt(const float f) {
	// ??
	return round(f);
}

float toDegrees(const float rad) {
	return rad * RAD2DEG;
}

float toRadians(const float deg) {
	return deg / RAD2DEG;
}

float distance(const Vector3& a, const Vector3& b) {
	return powf(powf(a.xComponent - b.xComponent, 2) + powf(a.yComponent - b.yComponent, 2) + powf(a.zComponent - b.zComponent, 2), 0.5f);
}

bool checkCircleIntersection(const Vector3& a, const Vector3& b, const float aR, const float bR) {
	return distance(a, b) <= aR + bR;
}

int randomInclusive(const int min, const int max) {
	return rand() % (max - min + 1) + min;
}