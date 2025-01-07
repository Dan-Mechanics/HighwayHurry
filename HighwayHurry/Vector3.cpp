#include "Vector3.h"
#include "math.h"
#include <iostream>
#include "Utils.h"
#include "MathUtils.h"

Vector3::Vector3() = default;

Vector3::Vector3(const float x, const float y, const float z) :
	xComponent(x), yComponent(y), zComponent(z) {
}

Vector3 Vector3::operator+(const Vector3& container) const {
	return Vector3(xComponent + container.xComponent, yComponent + container.yComponent, zComponent + container.zComponent);
}

Vector3& Vector3::operator+=(const Vector3& container) {
	add(container);

	return *this;
}

Vector3 Vector3::operator-(const Vector3& container) const {
	return Vector3(xComponent - container.xComponent, yComponent - container.yComponent, zComponent - container.zComponent);
}

Vector3& Vector3::operator-=(const Vector3& container) {
	remove(container);

	return *this;
}

Vector3 Vector3::operator*(const float scalar) const {
	return Vector3(xComponent * scalar, yComponent * scalar, zComponent * scalar);
}

Vector3& Vector3::operator*=(const float scalar) {
	multiply(scalar);

	return *this;
}

void Vector3::setAll(const float x, const float y, const float z) {
	xComponent = x;
	yComponent = y;
	zComponent = z;
}

void Vector3::logComponents() const {
	std::cout <<
		"( x : " << xComponent <<
		" | y : " << yComponent <<
		" | z : " << zComponent <<
		" )" << std::endl;
}

void Vector3::add(const Vector3 pos) {
	xComponent += pos.xComponent;
	yComponent += pos.yComponent;
	zComponent += pos.zComponent;
}

void Vector3::add(const Vector3& other, const float mult) {
	xComponent += other.xComponent * mult;
	yComponent += other.yComponent * mult;
	zComponent += other.zComponent * mult;
}

void Vector3::remove(const Vector3 other) {
	xComponent -= other.xComponent;
	yComponent -= other.yComponent;
	zComponent -= other.zComponent;
}

void Vector3::multiply(const float amount) {
	xComponent *= amount;
	yComponent *= amount;
	zComponent *= amount;
}

void Vector3::divide(const float amount) {
	if (amount == 0) {
		print("Cannot divide by zero!!");

		return; 
	}
	
	xComponent /= amount;
	yComponent /= amount;
	zComponent /= amount;
}

void Vector3::invert() {
	multiply(-1);
}

float Vector3::calculateMagnitude() {
	return powf(powf(xComponent, 2) + powf(yComponent, 2) + powf(zComponent, 2), 0.5f);
}

void Vector3::normalize()  {
	float mag = calculateMagnitude();

	// -1 magnitude is not possible,
	// and we don't have to normalize a vector with (0, 0, 0)
	if (mag <= 0) { return; }

	// mag --> 1
	// 2 --> 1
	// 2 / 2 = --> 1

	// does this need to be float ? --> no.
	multiply(1 / mag);
}

void Vector3::clampMagnitude(const float magnitude) {
	float mag = calculateMagnitude();

	// if mag 0 <= 10 so return.
	// if 0 <= 0 so return
	if (mag <= magnitude) { return; }

	// no divide by zero nonsense here.
	multiply(magnitude / mag);
}

void Vector3::round(const float grid) {
	if (grid == 0) {
		print("Cannot divide by zero!!");

		return;
	}
	
	xComponent = roundf(xComponent / grid) * grid;
	yComponent = roundf(yComponent / grid) * grid;
	zComponent = roundf(zComponent / grid) * grid;
}

float Vector3::getAngle() const {
	return toDegrees(atan2f(yComponent, xComponent));
}

void Vector3::setAngleAndLength(float angle, const const float length) {
	angle = toRadians(angle);
	setAll(cosf(angle) * length, sinf(angle) * length, 0);
}