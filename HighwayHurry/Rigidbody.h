#pragma once
#include "Vector3.h"
#include "Time.h"

class Rigidbody {
public:
	Vector3 position{};
	Vector3 velocity{};

	Rigidbody();
	Rigidbody(float mass, const int maxX, const int maxY, const int minX, const int minY);

	void addVelocity(const Vector3 velocity);
	void addAcceleraton(const Vector3 acceleration);
	void addForce(const Vector3 force);
	void resetAll();

	/// <summary>
	/// Move the force into accel,
	/// accel into vel,
	/// vel into pos.
	/// </summary>
	void process(const Time& time);
	void limitVelocity(const float magnitude);
	void stopInPlace();

	int getMaxX() const;
	int getMaxY() const;

	int getMinX() const;
	int getMinY() const;

	void setMass(float mass);
	float getMass() const;

private:
	Vector3 acceleration{}; // Have an add force thing that adds acceleration.
	Vector3 force{}; // Have an add force thing that adds acceleration.

	float mass = 1;

	int minX{}, minY{};
	int maxX{}, maxY{};
};