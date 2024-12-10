#include "Rigidbody.h"
#include "Utils.h"

/// <summary>
/// Used for friction.
/// </summary>
const float GRAVITY = 10;

Rigidbody::Rigidbody() = default;

Rigidbody::Rigidbody(float mass) 
{
	if (mass <= 0) 
	{
		print("if (mass <= 0) ");
		mass = 1;
	}

	this->mass = mass;
}

void Rigidbody::addVelocity(Vector3 velocity)
{
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

void Rigidbody::process(const Time& const time) {
	force.divide(mass);
	acceleration.add(force);
	velocity.add(acceleration, time.fixedInterval);
	
	force.setAll(0, 0, 0);
	acceleration.setAll(0, 0, 0);

	position.add(velocity, time.fixedInterval);
}

void Rigidbody::limitVelocity(const float magnitude) {
	velocity.clampMagnitude(magnitude);
}
