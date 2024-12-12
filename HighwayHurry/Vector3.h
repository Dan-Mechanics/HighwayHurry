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
	Vector3(const float x, const float y, const float z);

	Vector3 operator+(const Vector3& container) const;
	Vector3& operator+=(const Vector3& container);

	Vector3 operator-(const Vector3& container) const;
	Vector3& operator-=(const Vector3& container);

	Vector3 operator*=(const float scalar) const;
	Vector3& operator*(const float scalar);

	void setAll(const float x, const float y, const float z);
	void logComponents() const;
	void add(const Vector3 vec);
	void add(const Vector3& vec, const float mult);
	void remove(const Vector3 vec);
	void multiply(const float scalar);
	void divide(const float scalar);
	float calculateMagnitude();
	void normalize();
	void clampMagnitude(const float magnitude);
	void round(const float grid);
	float dotProduct(const Vector3 other);
	float dotProductNormalized(Vector3 b);
	void crossProduct(const Vector3 other);
	float getAngle() const;
	void setWithAngleAndLength(const float angle, const float length);
	float calculateDistanceTo(Vector3 other) const;
};

