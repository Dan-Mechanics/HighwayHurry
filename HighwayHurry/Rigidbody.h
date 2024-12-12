#pragma once
#include "Vector3.h"
#include "Time.h"

extern const float GRAVITY;

/// <summary>
/// Add: mass, ? friction ?, etc
/// </summary>
class Rigidbody {
public:
	Vector3 position{};
	Vector3 velocity{};

	float mass = 1;
	float staticFrictionCoefficient{};
	float dynamicFrictionCoefficient{}; // or just one
	// float drag{};

	/// <summary>
	/// What's the point in having default constructor if you don't
	/// have a default destructor. You don't need both ??
	/// </summary>
	Rigidbody();
	Rigidbody(float mass);
	// add real constructor.

	void addVelocity(const Vector3 velocity);
	void addAcceleraton(const Vector3 acceleration);
	void addForce(const Vector3 force);
	void resetAll();

	/// <summary>
	/// Move the force into accel,
	/// accel into vel,
	/// vel into pos.
	/// </summary>
	void process(const Time& const time);
	void limitVelocity(const float magnitude);
	void stopInPlace();

private:
	Vector3 acceleration{}; // have an add force thing that adds acceleration.
	Vector3 force{}; // have an add force thing that adds acceleration.
};

