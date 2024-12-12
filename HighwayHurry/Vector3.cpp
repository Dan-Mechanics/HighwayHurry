#include "Vector3.h"
#include "math.h"
#include <iostream>
#include "Utils.h"

Vector3::Vector3() = default;

Vector3::Vector3(const float x, const float y, const float z) :
	xComponent(x), yComponent(y), zComponent(z) {

	std::cout << "CREATED ";
	logComponents();
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

/// <summary>
/// Does this need to be reference to float ? or just float will do ?
/// </summary>
Vector3 Vector3::operator*=(const float scalar) const {
	return Vector3(xComponent * scalar, yComponent * scalar, zComponent * scalar);
}

Vector3& Vector3::operator*(const float scalar) {
	multiply(scalar);

	return *this;
}

/// <summary>
/// Alloc-free.
/// </summary>
void Vector3::setAll(const float x, const float y, const float z) {
	xComponent = x;
	yComponent = y;
	zComponent = z;
}

/// <summary>
/// Print components.
/// </summary>
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

/// <summary>
/// Multiply the components before adding them.
/// </summary>
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
	if (amount == 0) 
	{ 
		print("Cannot divide by zero!!");

		return; 
	}
	
	xComponent /= amount;
	yComponent /= amount;
	zComponent /= amount;
}

/// <summary>
/// Get length.
/// </summary>
float Vector3::calculateMagnitude() {
	return powf(powf(xComponent, 2) + powf(yComponent, 2) + powf(zComponent, 2), 0.5f);
}

/// <summary>
/// Make the length 1.
/// </summary>
void Vector3::normalize()  {
	/*clampMagnitude(1);
	return;*/
	
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

/// <summary>
/// Limit the length of the vector.
/// </summary>
void Vector3::clampMagnitude(const float magnitude) {
	float mag = calculateMagnitude();

	// if mag 0 <= 10 so return.
	// if 0 <= 0 so return
	if (mag <= magnitude) { return; }

	// no divide by zero nonsense here.
	multiply(magnitude / mag);
}

/// <summary>
/// https://discussions.unity.com/t/using-mathf-round-for-a-vector3/88858
/// </summary>
void Vector3::round(const float grid) {
	xComponent = roundf(xComponent / grid) * grid;
	yComponent = roundf(yComponent / grid) * grid;
	zComponent = roundf(zComponent / grid) * grid;
}

float Vector3::calcDotProduct(const Vector3& const other) {
	return
		xComponent * other.xComponent +
		yComponent * other.yComponent +
		zComponent * other.zComponent;
}

// todo: refernces const const, physics les, komende weken aan de gang practicum,
// implementeer formjles.
// matrixes is optimzaiton.
// fix pi and degs

float Vector3::calcNormalizedDotProduct(Vector3 b) {
	b.normalize();

	//Vector3 a = Vector3(xComponent, yComponent, zComponent);
	Vector3 a = Vector3(*this); // how could this not exist ??
	a.normalize();

	return
		a.xComponent * b.xComponent +
		a.yComponent * b.yComponent +
		a.zComponent * b.zComponent;
}

Vector3 Vector3::cross(const Vector3& const other) {
	return {
		yComponent * other.zComponent + zComponent * other.yComponent,
		zComponent * other.xComponent + xComponent * other.zComponent,
		xComponent * other.yComponent + yComponent * other.xComponent
	};
}


float Vector3::getAngle() const {
	// convert to degrees and not PI ??
	return atan2f(yComponent, xComponent);
}

/// <summary>
/// 
/// </summary>
/// <param name="angle">Degrees</param>
void Vector3::setWithAngleAndLength(const float angle, const float length) {
	// convert to degrees and not PI ??
	// TODO: convert angle to PI shit.
	// how tf am i gonna make particles.
	// just draw  abuncha sprite.
	// dit is allemaal in radians.
	// look up cross product tutorial
	//const float PI = 3.1415926535 8979323846 2643383279 5028841971 6939937510 5820974944 5923078164 0628620899 8628034825 3421170679 8214808651 3282306647 0938446095 5058223172 5359408128 4811174502 8410270193 8521105559 6446229489 5493038196 4428810975 6659334461 2847564823 3786783165 2712019091 4564856692 3460348610 4543266482;
	
	// we want to convert angle which is degrees to radians.
	
	setAll(cosf(angle) * length, sinf(angle) * length, 0);
}