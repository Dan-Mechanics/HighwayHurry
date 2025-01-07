#pragma once

struct Vector3 {
public: 
	float xComponent{};
	float yComponent{};
	float zComponent{};

	Vector3();
	Vector3(const float x, const float y, const float z);

	Vector3 operator+(const Vector3& container) const;
	Vector3& operator+=(const Vector3& container);

	Vector3 operator-(const Vector3& container) const;
	Vector3& operator-=(const Vector3& container);

	Vector3 operator*(const float scalar) const;
	Vector3& operator*=(const float scalar);

	void setAll(const float x, const float y, const float z);
	void logComponents() const;

	void add(const Vector3 vec);
	void add(const Vector3& vec, const float mult);

	void remove(const Vector3 vec);
	void multiply(const float scalar);
	void divide(const float scalar);
	void invert();

	float calculateMagnitude();
	void normalize();
	void clampMagnitude(const float magnitude);
	void round(const float grid);

	float getAngle() const;
	void setAngleAndLength(float angle, const const float length);	
};