#pragma once

struct Vector3 {
public: // Technically speaking this doesnt have to be here.
	float xComponent{};
	float yComponent{};

	/// <summary>
	/// I could use quicksort for the sorting order of the zComponent entity.
	/// </summary>
	float zComponent{};

	Vector3();
	Vector3(float x, float y, float z);
	//~Position();

	void setAll(float x, float y, float z);
	void logComponents();
	void add(Vector3 vec);
	void add(Vector3& vec, float mult);
	//void add(Vector3 vec, float mult);
	void remove(Vector3 vec);
	void mult(float amount);
	void divide(float amount);
	float calculateMagnitude();
	void normalize();
	void clampMagnitude(float magnitude);
	void round(float grid);
	float dotProduct(Vector3 other);
	float dotProductNormalized(Vector3 b);
	void crossProduct(Vector3 other);
	//Vector3 crossProductAlloc(Vector3 other);
	float getAngle();
	void setWithAngleAndLength(float angle, float length);
	float calculateDistanceTo(Vector3 other);
};

