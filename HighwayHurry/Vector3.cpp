#include "Vector3.h"
#include "math.h"
#include <iostream>
#include "Utils.h"

Vector3::Vector3() = default;

Vector3::Vector3(float x, float y, float z) : xComponent(x), yComponent(y), zComponent(z)
{
	std::cout << "CREATED ";
	logComponents();
}

/*Position::~Position()
{
	std::cout << "DESTROYED ";
	log();
}*/

/// <summary>
/// Alloc-free version of creating a new Vector3.
/// </summary>
void Vector3::setAll(float x, float y, float z)
{
	xComponent = x;
	yComponent = y;
	zComponent = z;
}

/// <summary>
/// Print components.
/// </summary>
void Vector3::logComponents()
{
	std::cout <<
		"( x : " << xComponent <<
		" | y : " << yComponent <<
		" | z : " << zComponent <<
		" )" << std::endl;
}

void Vector3::add(Vector3 pos)
{
	xComponent += pos.xComponent;
	yComponent += pos.yComponent;
	zComponent += pos.zComponent;
}

/// <summary>
/// Multiply the components before adding them.
/// </summary>
void Vector3::add(Vector3& other, float mult)
{
	xComponent += other.xComponent * mult;
	yComponent += other.yComponent * mult;
	zComponent += other.zComponent * mult;
}
//void Vector3::add(Vector3 other, float mult)
//{
//	other.mult(mult);
//
//	xComponent += other.xComponent;
//	yComponent += other.yComponent;
//	zComponent += other.zComponent;
//}

void Vector3::remove(Vector3 other)
{
	xComponent -= other.xComponent;
	yComponent -= other.yComponent;
	zComponent -= other.zComponent;
}

void Vector3::mult(float amount)
{
	xComponent *= amount;
	yComponent *= amount;
	zComponent *= amount;
}

void Vector3::divide(float amount)
{
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
float Vector3::calculateMagnitude()
{
	return powf(powf(xComponent, 2) + powf(yComponent, 2) + powf(zComponent, 2), 0.5f);
}

/// <summary>
/// Make the length 1.
/// </summary>
void Vector3::normalize()
{
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
	mult(1 / mag);
}

/// <summary>
/// Limit the length of the vector.
/// </summary>
void Vector3::clampMagnitude(float magnitude)
{
	float mag = calculateMagnitude();

	// if mag 0 <= 10 so return.
	// if 0 <= 0 so return
	if (mag <= magnitude) { return; }

	// no divide by zero nonsense here.
	mult(magnitude / mag);
}

/// <summary>
/// https://discussions.unity.com/t/using-mathf-round-for-a-vector3/88858
/// </summary>
void Vector3::round(float grid)
{
	xComponent = roundf(xComponent / grid) * grid;
	yComponent = roundf(yComponent / grid) * grid;
	zComponent = roundf(zComponent / grid) * grid;
}

float Vector3::dotProduct(Vector3 other)
{
	return 
		xComponent * other.xComponent +
		yComponent * other.yComponent + 
		zComponent * other.zComponent;
}

float Vector3::dotProductNormalized(Vector3 b) 
{
	b.normalize();

	//Vector3 a = Vector3(xComponent, yComponent, zComponent);
	Vector3 a = Vector3(*this); // how could this not exist ??
	a.normalize();

	return
		a.xComponent * b.xComponent +
		a.yComponent * b.yComponent +
		a.zComponent * b.zComponent;
}

/// <summary>
/// Idk if this works --> ask rosa or something. The order of the algorithm is important.
/// </summary>
void Vector3::crossProduct(Vector3 other)
{
	setAll(
		yComponent * other.zComponent + zComponent * other.yComponent,
		zComponent * other.xComponent + xComponent * other.zComponent,
		xComponent * other.yComponent + yComponent * other.xComponent
	);
}

//Vector3 Vector3::crossProductAlloc(Vector3 other)
//{
//	return Vector3{
//		yComponent * other.zComponent + zComponent * other.yComponent,
//		zComponent * other.xComponent + xComponent * other.zComponent,
//		xComponent * other.yComponent + yComponent * other.xComponent
//	};;
//}

float Vector3::getAngle()
{
	return atan2f(yComponent, xComponent);
}

void Vector3::setWithAngleAndLength(float angle, float length)
{
	setAll(cosf(angle) * length, sinf(angle) * length, 0);
}

float Vector3::calculateDistanceTo(Vector3 other)
{
	other.remove(*this);
	return other.calculateMagnitude();
}