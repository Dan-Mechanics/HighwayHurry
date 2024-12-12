#include "MathUtils.h"
#include "Vector3.h"
#include <SFML/Graphics.hpp>

const float PI = 3.141592653589793238463f;
const float RAD2DEG = 180 / PI;

int roundToInt(const float f) {
	//return (int)round(f);
	// idk.
	return round(f);
}

/// <summary>
/// https://stackoverflow.com/questions/40776703/converting-from-radians-to-degrees
/// </summary>
float toDegrees(const float rad) {
	//degrees = radians * (180.0 / 3.141592653589793238463)
	return rad * RAD2DEG;
}

float toRadians(const float deg) {
	
	return deg / RAD2DEG;
}

float distance(const Vector3& const a, const Vector3& const b) {
	return powf(powf(a.xComponent - b.xComponent, 2) + powf(a.yComponent - b.yComponent, 2) + powf(a.zComponent - b.zComponent, 2), 0.5f);
}

bool checkCircleTouch(const Vector3 a, const Vector3 b, const float aR, const float bR) {
	return distance(a, b) <= aR + bR;
}

/// <summary>
/// https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
/// </summary>
int randomInclusive(const int min, const int max) {
	return rand() % (max - min + 1) + min;
}