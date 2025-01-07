#include "MathUtils.h"
#include "Vector3.h"
#include <SFML/Graphics.hpp>

const float PI = 3.141592653589793238463f;
const float RAD2DEG = 180 / PI;

float getDistance(const Vector3& a, const Vector3& b) {
	return powf(powf(a.xComponent - b.xComponent, 2) + powf(a.yComponent - b.yComponent, 2) + powf(a.zComponent - b.zComponent, 2), 0.5f);
}

float getDot(const Vector3& a, const Vector3& b) {
	return
		a.xComponent * b.xComponent +
		a.yComponent * b.yComponent +
		a.zComponent * b.zComponent;
}

float getNormalizedDot(Vector3 a, Vector3 b) {
	a.normalize();
	b.normalize();

	return getDot(a, b);
}

Vector3 getCross(const Vector3& a, const Vector3& b) {
	return {
		a.yComponent * b.zComponent + a.zComponent * b.yComponent,
		a.zComponent * b.xComponent + a.xComponent * b.zComponent,
		a.xComponent * b.yComponent + a.yComponent * b.xComponent
	};
}


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

bool checkCircleIntersection(const Vector3& a, const Vector3& b, const float aR, const float bR) {
	return getDistance(a, b) <= aR + bR;
}

int randomInclusive(const int min, const int max) {
	return rand() % (max - min + 1) + min;
}