#include "Rigidbody.h"
#include "Utils.h"

/// <summary>
/// Used for friction.
/// </summary>
const float GRAVITY = 10;

Rigidbody::Rigidbody() = default;

Rigidbody::Rigidbody(float mass, const int maxX, const int maxY, const int minX, const int minY) {
	if (mass <= 0) {
		print("if (mass <= 0) ");
		mass = 1;
	}

	this->mass = mass;

	this->minX = minX;
	this->minY = minY;
	this->maxX = maxX;
	this->maxY = maxY;
}

void Rigidbody::addVelocity(Vector3 velocity) {
	this->velocity.add(velocity);
}

void Rigidbody::addAcceleraton(Vector3 acceleration) {
	//accel.mult(time.fixedInterval);
	this->acceleration.add(acceleration);
}

void Rigidbody::addForce(Vector3 force) {
	//force.mult(1 / mass);

	this->force.add(force);

	// friction hook ???
}

void Rigidbody::resetAll() {
	velocity.setAll(0, 0, 0);
	acceleration.setAll(0, 0, 0);
	force.setAll(0, 0, 0);
}

void Rigidbody::process(const Time& time) {
	force.divide(mass);
	acceleration.add(force);

	// or use operand.
	velocity.add(acceleration, time.fixedInterval);
	
	force.setAll(0, 0, 0);
	acceleration.setAll(0, 0, 0);

	position.add(velocity, time.fixedInterval);
}

void Rigidbody::limitVelocity(const float magnitude) {
	velocity.clampMagnitude(magnitude);
}

void Rigidbody::stopInPlace() {
	velocity.setAll(0, 0, 0);
}

int Rigidbody::getMaxX() const {
	return maxX;
}

int Rigidbody::getMaxY() const {
	return maxY;
}

int Rigidbody::getMinX() const {
	return minX;
}

int Rigidbody::getMinY() const {
	return minY;
}
